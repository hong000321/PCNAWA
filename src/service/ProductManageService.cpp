#include "./ProductManageService.h"
#include "../models/Product.h"
#include "../manager/ProductManager.h"
#include "../repository/CsvRepository.h"
#include "../repository/IRepository.h"
#include "../ui/UI_GLOBAL.h"
#include <ctime>
#include <limits>
#include <iomanip>

ProductManageService::ProductManageService() {
    std::unique_ptr<IRepository<Product>> repo(new CsvRepository<Product>("../../data/product_dummy_data.csv"));
    m_productManager = ProductManager(std::move(repo)); // 이동 대입 연산자로 소유권 이전
    m_title = new DisplayTitle("Product Management");
    
    m_table = new DisplayTable();
    m_menu = new DisplayMenu();
    addWidget(m_title);
    addWidget(m_table);
    addWidget(m_menu);
}

void ProductManageService::start() {
    m_title->pushTitle("Product List");
    
    int depth = 0;
    while(1) {
        updateMenu(Select_Main_Page);
        updateProductList();
        display(true);
        int select = getInt("선택 : ");
        if(select >= Select_Main_Page.size()) {
            printf("invalid select!!! = %d \n", select);
            continue;
        }
        int ret = Select_Main_Page[select].action();
        if(ret == BACK) {
            break;
        }
    }
    m_title->popTitle();
    m_title->popTitle();
}

void ProductManageService::updateProductList(int page) {
    bool ret = false;
    if(page < 0)
        ret = setProductListByPage(m_currPage);
    else
        ret = setProductListByPage(page);
    if(ret) {
        std::cerr << "updateTable Failed";
    }
}

void ProductManageService::updateMenu(std::vector<SelectMenu>& page) const {
    if (m_menu) {
        m_menu->setMenu(page);
    } else {
        std::cerr << "Menu is not initialized." << std::endl;
    }
}

bool ProductManageService::setProductListByPage(int page) {
    if (m_table) {
        int max_lines = (g_max_cmd_table_lines - 2);
        int remain_size = m_productManager.getSize() - page * max_lines;
        if(remain_size >= max_lines) {
            remain_size = max_lines;
        } else if(remain_size <= 0) {
            return false;
        }
        int start = page * max_lines;
        int end = page * max_lines + remain_size;
        std::vector<std::string> productStrings = m_productManager.getProductsString(start, end);
        if (productStrings.empty()) {
            productStrings.push_back("No products found.");
        }
        std::string separator = std::string(g_max_cmd_width, '-');
        
        std::cout << "width: " << g_max_cmd_width << std::endl;
        std::cout << "lines: " << g_max_cmd_lines << std::endl;
        productStrings.insert(productStrings.begin(), separator);
        productStrings.insert(productStrings.begin(), m_productManager.getProductTitleString());
        
        m_table->setTable(productStrings);
    } else {
        std::cerr << "Table is not initialized." << std::endl;
        return false;
    }
    return true;
}

// ============================ functions of Select ============================

int ProductManageService::updateProductPage(int id) {
    Product *product = m_productManager.getById(id);
    if(product == nullptr) {
        return FAIL;
    }
    m_strMet.clear();
    m_strMet.push_back({"Product ID", std::to_string(id)});
    m_strMet.push_back({"Product Name", product->name});
    m_strMet.push_back({"Category", product->category});
    m_strMet.push_back({"Price", std::to_string(product->price)});
    m_strMet.push_back({"Stock", std::to_string(product->stock)});
    m_strMet.push_back({"Description", product->description});
    m_strMet.push_back({"Date", product->createdDate});
    return OK;
}

int ProductManageService::setProductPageById(int id) {
    m_title->pushTitle("Edit Product");
    int ret = -1;
    
    while(1) {
        ret = updateProductPage(id);
        if(ret != OK) {
            printf("fail to update product page!!! \n");
        }
        m_table->setMetrixTable(m_strMet);
        updateMenu(Select_Product_Page);
        display(true);
        int select = getInt("선택 : ");
        if(select >= Select_Product_Page.size()) {
            printf("invalid select!!! = %d \n", select);
            continue;
        }
        
        int ret = Select_Product_Page[select].action();
        if(ret == BACK) {
            break;
        }
    }
    m_title->popTitle();
    return OK;
}

int ProductManageService::prevPage() {
    return BACK;
}

int ProductManageService::selectProductById() {
    m_currId = getInt("상품 ID를 입력해주세요 : ");
    if(m_currId <= 0) {
        return FAIL;
    }
    setProductPageById(m_currId);
    return OK;
}

int ProductManageService::selectProductByName() {
    std::string name = getString("상품명을 입력해주세요 : ");
    Product *product = m_productManager.getProductByName(name);
    if(product == nullptr) {
        printf("상품을 찾을 수 없습니다.\n");
        return FAIL;
    }
    setProductPageById(product->id);
    return OK;
}

int ProductManageService::selectProductByCategory() {
    std::string category = getString("카테고리를 입력해주세요 : ");
    std::vector<int> products = m_productManager.getProductsByCategory(category);
    if(products.empty()) {
        printf("해당 카테고리의 상품이 없습니다.\n");
        return FAIL;
    }
    
    // 카테고리별 상품 목록 표시
    printf("\n=== %s 카테고리 상품 목록 ===\n", category.c_str());
    int cnt = 0;
    for(auto id : products) {
        
        Product *tmp = m_productManager.getById(id);
        printf("%d. [ID:%d] %s - ₩%.2f (재고: %d)\n", 
                cnt,tmp->id, tmp->name.c_str(), 
                tmp->price, tmp->stock);
        cnt ++;
    }
    
    int select = getInt("선택할 상품 번호 : ") - 1;
    if(select >= 0 && select < products.size()) {
        setProductPageById(products[select]);
    }
    return OK;
}

int ProductManageService::addProduct() {
    Product product;
    product.id = m_productManager.getLastId() + 1;
    product.name = getString("상품명을 입력해주세요 : ");
    product.category = getString("카테고리를 입력해주세요 : ");
    product.price = getDouble("가격을 입력해주세요 : ");
    product.stock = getInt("재고를 입력해주세요 : ");
    product.description = getString("상품 설명을 입력해주세요 : ");
    
    std::time_t t = std::time(nullptr);
    std::tm now = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&now, "%Y-%m-%d");
    product.createdDate = ss.str();

    if(m_productManager.add(product)) {
        printf("상품이 성공적으로 추가되었습니다.\n");
    } else {
        printf("상품 추가에 실패했습니다.\n");
    }
    return OK;
}

int ProductManageService::delProduct() {
    int id = getInt("삭제할 상품 ID를 입력해주세요 : ");
    if(m_productManager.removeById(id)) {
        printf("상품이 성공적으로 삭제되었습니다.\n");
    } else {
        printf("상품 삭제에 실패했습니다.\n");
    }
    return OK;
}

int ProductManageService::nextProductTablePage() {
    updateProductList(++m_currPage);
    return OK;
}

int ProductManageService::prevProductTablePage() {
    if(m_currPage == 0)
        m_currPage = 1;
    updateProductList(--m_currPage);
    return OK;
}

int ProductManageService::showLowStockProducts() {
    int threshold = getInt("재고 임계값을 입력해주세요 (기본값: 5) : ");
    if(threshold <= 0) threshold = 5;
    
    std::vector<int> lowStockProducts = m_productManager.getLowStockProducts(threshold);
    if(lowStockProducts.empty()) {
        printf("재고가 부족한 상품이 없습니다.\n");
        return OK;
    }
    
    printf("\n=== 재고 부족 상품 목록 (재고 %d개 이하) ===\n", threshold);
    for(const auto& id : lowStockProducts) {
        Product *tmp = m_productManager.getById(id);
        printf("[ID:%3d] %40s - 재고: %3d개 (카테고리: %4s)\n", 
               tmp->id, tmp->name.c_str(), tmp->stock, tmp->category.c_str());
    }
    printf("계속하려면 Enter를 누르세요...\n");
    getchar();
    getchar();
    return OK;
}

int ProductManageService::showInventoryValue() {
    double totalValue = m_productManager.getTotalInventoryValue();
    printf("\n=== 전체 재고 가치 ===\n");
    printf("총 재고 가치: ₩%.2f\n", totalValue);
    printf("총 상품 수: %d개\n", m_productManager.getSize());
    getString("계속하려면 Enter를 누르세요...");
    return OK;
}

int ProductManageService::searchByPriceRange() {
    double minPrice = getDouble("최소 가격을 입력해주세요 : ");
    double maxPrice = getDouble("최대 가격을 입력해주세요 : ");
    
    if(minPrice > maxPrice) {
        printf("최소 가격이 최대 가격보다 클 수 없습니다.\n");
        return FAIL;
    }
    
    // ID 리스트로 받기
    std::vector<int> productIds = m_productManager.getProductsInPriceRange(minPrice, maxPrice);
    if(productIds.empty()) {
        printf("해당 가격대의 상품이 없습니다.\n");
        return FAIL;
    }
    
    printf("\n=== ₩%.2f ~ ₩%.2f 가격대 상품 목록 ===\n", minPrice, maxPrice);
    
    // ID로 실제 Product 객체 조회해서 출력
    for(size_t i = 0; i < productIds.size(); ++i) {
        Product* product = m_productManager.getById(productIds[i]);
        if(product != nullptr) {
            printf("%zu. [ID:%d] %s - ₩%.2f (재고: %d)\n", 
                   i+1, product->id, product->name.c_str(), 
                   product->price, product->stock);
        }
    }
    
    int select = getInt("선택할 상품 번호 (0: 뒤로가기) : ");
    if(select > 0 && select <= static_cast<int>(productIds.size())) {
        setProductPageById(productIds[select-1]);  // ID로 접근
    }
    return OK;
}

// product page select functions
int ProductManageService::modifyProduct() {
    Product *origProduct = m_productManager.getById(m_currId);
    if(origProduct == nullptr) {
        return FAIL;
    }
    
    Product product;
    std::string tmpStr;
    product.id = origProduct->id;
    
    tmpStr = "상품명을 입력해주세요(" + origProduct->name + ") -> ";
    product.name = getString(tmpStr);
    
    tmpStr = "카테고리를 입력해주세요(" + origProduct->category + ") -> ";
    product.category = getString(tmpStr);
    
    tmpStr = "가격을 입력해주세요(" + std::to_string(origProduct->price) + ") -> ";
    product.price = getDouble(tmpStr);
    
    tmpStr = "재고를 입력해주세요(" + std::to_string(origProduct->stock) + ") -> ";
    product.stock = getInt(tmpStr);
    
    tmpStr = "상품 설명을 입력해주세요(" + origProduct->description + ") -> ";
    product.description = getString(tmpStr);
    
    std::time_t t = std::time(nullptr);
    std::tm now = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&now, "%Y-%m-%d");
    product.createdDate = ss.str();
    
    if(m_productManager.update(product)) {
        printf("상품이 성공적으로 수정되었습니다.\n");
    } else {
        printf("상품 수정에 실패했습니다.\n");
    }
    return OK;
}

int ProductManageService::adjustStock() {
    Product *product = m_productManager.getById(m_currId);
    if(product == nullptr) {
        return FAIL;
    }
    
    printf("현재 재고: %d개\n", product->stock);
    int quantity = getInt("재고 변경량을 입력해주세요 (음수: 감소, 양수: 증가) : ");
    
    if(m_productManager.adjustStock(m_currId, quantity)) {
        printf("재고가 성공적으로 업데이트되었습니다.\n");
        printf("새로운 재고: %d개\n", product->stock + quantity);
    } else {
        printf("재고 업데이트에 실패했습니다. (재고 부족 가능성)\n");
    }
    return OK;
}

int ProductManageService::viewProductDetails() {
    Product *product = m_productManager.getById(m_currId);
    if(product == nullptr) {
        return FAIL;
    }
    
    printf("\n=== 상품 상세 정보 ===\n");
    printf("상품 ID: %d\n", product->id);
    printf("상품명: %s\n", product->name.c_str());
    printf("카테고리: %s\n", product->category.c_str());
    printf("가격: ₩%.2f\n", product->price);
    printf("재고: %d개\n", product->stock);
    printf("설명: %s\n", product->description.c_str());
    printf("등록일: %s\n", product->createdDate.c_str());
    printf("=======================\n");
    
    getString("계속하려면 Enter를 누르세요...");
    return OK;
}

int ProductManageService::searchByCategory() {
    std::string category = getString("검색할 카테고리를 입력해주세요 : ");
    std::vector<int> products = m_productManager.getProductsByCategory(category);
    
    if(products.empty()) {
        printf("해당 카테고리의 상품이 없습니다.\n");
        return FAIL;
    }
    
    printf("\n=== %s 카테고리 상품 목록 ===\n", category.c_str());
    int cnt = 0;
    for(auto id : products) {
        Product *tmp = m_productManager.getById(id);
        printf("%d. [ID:%d] %s - ₩%.2f (재고: %d)\n", 
                cnt+1,tmp->id, tmp->name.c_str(), 
                tmp->price, tmp->stock);
        cnt ++;
    }
    
    int select = getInt("선택할 상품 번호 (0: 뒤로가기) : ");
    if(select > 0 && select <= products.size()) {
        setProductPageById(products[select-1]);
    }
    return OK;
}