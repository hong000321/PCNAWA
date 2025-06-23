#include "./ShopService.h"
#include "../models/Order.h"
#include "../models/Product.h"
#include "../repository/CsvRepository.h"
#include "../view/UI_GLOBAL.h"
#include <ctime>
#include <iomanip>

ShopService::ShopService(ProductManager* productManager) {
    m_productManager = productManager;
    
    // OrderManager 초기화
    std::unique_ptr<IRepository<Order>> repo(new CsvRepository<Order>("../../data/order_dummy_data.csv"));
    m_orderManager = OrderManager(std::move(repo));
    
    // UI 컴포넌트 초기화
    m_title = new DisplayTitle("Shopping Mall");
    m_table = new DisplayTable();
    m_menu = new DisplayMenu();
    
    // 위젯 추가
    addWidget(m_title);
    addWidget(m_table);
    addWidget(m_menu);
    
    // 장바구니 초기화
    m_cart = Order(0, m_currentUserId);
}

void ShopService::start() {
    m_title->pushTitle("쇼핑몰에 오신 것을 환영합니다!");
    
    while(true) {
        updateMenu(Select_Main_Page);
        updateProductList();
        display(true);
        
        int select = getInt("선택 : ");
        if(select >= Select_Main_Page.size()) {
            printf("잘못된 선택입니다!!! = %d \n", select);
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

void ShopService::updateProductList(int page) {
    bool ret = false;
    if(page < 0)
        ret = setProductListByPage(m_currPage);
    else
        ret = setProductListByPage(page);
    if(ret) {
        std::cerr << "updateProductList Failed" << std::endl;
    }
}

void ShopService::updateMenu(std::vector<SelectMenu>& page) const {
    if (m_menu) {
        m_menu->setMenu(page);
    } else {
        std::cerr << "Menu is not initialized." << std::endl;
    }
}

bool ShopService::setProductListByPage(int page) {
    if (m_table && m_productManager) {
        int max_lines = (g_max_cmd_table_lines - 2);
        int remain_size = m_productManager->getSize() - page * max_lines;
        if(remain_size >= max_lines) {
            remain_size = max_lines;
        } else if(remain_size <= 0) {
            return false;
        }
        
        int start = page * max_lines;
        int end = page * max_lines + remain_size;
        std::vector<std::string> productStrings = m_productManager->getProductsString(start, end);
        
        if (productStrings.empty()) {
            productStrings.push_back("상품이 없습니다.");
        }
        
        std::string separator = std::string(g_max_cmd_width, '-');
        productStrings.insert(productStrings.begin(), separator);
        productStrings.insert(productStrings.begin(), m_productManager->getProductTitleString());
        
        m_table->setTable(productStrings);
    } else {
        std::cerr << "Table or ProductManager is not initialized." << std::endl;
        return false;
    }
    return true;
}

// ============================ 고객 기능들 ============================

int ShopService::prevPage() {
    return BACK;
}

int ShopService::addToCart() {
    if(!m_productManager) {
        printf("상품 관리자가 초기화되지 않았습니다.\n");
        return FAIL;
    }
    
    int productId = getInt("장바구니에 담을 상품 ID : ");
    Product* product = m_productManager->getById(productId);
    
    if(product == nullptr) {
        printf("상품을 찾을 수 없습니다.\n");
        return FAIL;
    }
    
    if(product->stock <= 0) {
        printf("죄송합니다. 해당 상품은 품절입니다.\n");
        return FAIL;
    }
    
    displayProductDetails(*product);
    
    int quantity = getInt("수량을 입력하세요 : ");
    if(quantity <= 0) {
        printf("수량은 1개 이상이어야 합니다.\n");
        return FAIL;
    }
    
    if(quantity > product->stock) {
        printf("재고가 부족합니다. (현재 재고: %d개)\n", product->stock);
        return FAIL;
    }
    
    m_cart.addItem(productId, product->price, quantity);
    printf("\n%s %d개가 장바구니에 담겼습니다!\n", product->name.c_str(), quantity);
    
    getString("계속하려면 Enter를 누르세요...");
    return OK;
}

int ShopService::viewCart() {
    printf("\n=== 장바구니 ===\n");
    
    if(m_cart.getItems().empty()) {
        printf("장바구니가 비어있습니다.\n");
        getString("계속하려면 Enter를 누르세요...");
        return OK;
    }
    
    m_title->pushTitle("장바구니");
    
    while(true) {
        updateCartList();
        updateMenu(Select_Cart_Page);
        display(true);
        
        int select = getInt("선택 : ");
        if(select >= Select_Cart_Page.size()) {
            printf("잘못된 선택입니다!!! = %d \n", select);
            continue;
        }
        
        int ret = Select_Cart_Page[select].action();
        if(ret == BACK) {
            break;
        }
    }
    m_title->popTitle();
    
    return OK;
}

int ShopService::removeFromCart() {
    if(m_cart.getItems().empty()) {
        printf("장바구니가 비어있습니다.\n");
        return OK;
    }
    
    displayCart();
    
    int productId = getInt("제거할 상품 ID : ");
    m_cart.removeItem(productId);
    printf("상품이 장바구니에서 제거되었습니다.\n");
    
    return OK;
}

int ShopService::checkout() {
    if(m_cart.getItems().empty()) {
        printf("장바구니가 비어있습니다.\n");
        return FAIL;
    }
    
    printf("\n=== 주문 확인 ===\n");
    displayCart();
    printf("총 결제 금액: ₩%.2f\n\n", m_cart.getTotalPrice());
    
    printf("주문하시겠습니까? (y/n): ");
    std::string confirm = getString("");
    if(confirm != "y" && confirm != "Y") {
        printf("주문이 취소되었습니다.\n");
        return OK;
    }
    
    // 재고 확인
    for(const auto& item : m_cart.getItems()) {
        Product* product = m_productManager->getById(item.pid);
        if(product == nullptr || product->stock < item.quantity) {
            printf("죄송합니다. %s의 재고가 부족합니다.\n", 
                   product ? product->name.c_str() : "Unknown Product");
            return FAIL;
        }
    }
    
    // 새 주문 생성
    Order newOrder = m_cart;
    newOrder.id = m_orderManager.getLastId() + 1;
    newOrder.userId = m_currentUserId;
    
    std::time_t t = std::time(nullptr);
    std::tm now = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&now, "%Y-%m-%d");
    newOrder.orderDate = ss.str();
    
    if(m_orderManager.add(newOrder)) {
        printf("\n주문이 완료되었습니다!\n");
        printf("주문번호: %d\n", newOrder.id);
        printf("결제금액: ₩%.2f\n", newOrder.getTotalPrice());
        
        // 재고 차감
        for(const auto& item : newOrder.getItems()) {
            m_productManager->adjustStock(item.pid, -item.quantity);
        }
        
        // 장바구니 비우기
        m_cart.clearItems();
        
        printf("주문해 주셔서 감사합니다!\n");
    } else {
        printf("주문 처리 중 오류가 발생했습니다.\n");
    }
    
    getString("계속하려면 Enter를 누르세요...");
    return OK;
}

int ShopService::viewMyOrders() {
    printf("\n=== 내 주문 내역 ===\n");
    std::vector<int> myOrders = m_orderManager.getOrdersByUserId(m_currentUserId);
    
    if(myOrders.empty()) {
        printf("주문 내역이 없습니다.\n");
        getString("계속하려면 Enter를 누르세요...");
        return OK;
    }
    
    for(int orderId : myOrders) {
        Order* order = m_orderManager.getById(orderId);
        if(order != nullptr) {
            printf("주문번호: %d | 주문일: %s | 총액: ₩%.2f\n", 
                   order->id, order->orderDate.c_str(), order->getTotalPrice());
            
            printf("   주문 상품:\n");
            for(const auto& item : order->getItems()) {
                Product* product = m_productManager->getById(item.pid);
                printf("   - %s x%d (₩%.2f)\n", 
                       product ? product->name.c_str() : "Unknown Product",
                       item.quantity, item.unitPrice * item.quantity);
            }
            printf("   ────────────────────\n");
        }
    }
    
    getString("계속하려면 Enter를 누르세요...");
    return OK;
}

int ShopService::searchProduct() {
    printf("\n=== 상품 검색 ===\n");
    std::string keyword = getString("검색할 상품명을 입력하세요 : ");
    
    if(!m_productManager) {
        printf("상품 관리자가 초기화되지 않았습니다.\n");
        return FAIL;
    }
    
    std::vector<Product> products = m_productManager->getAll();
    bool found = false;
    
    printf("\n검색 결과:\n");
    for(const auto& product : products) {
        if(product.name.find(keyword) != std::string::npos || 
           product.category.find(keyword) != std::string::npos) {
            printf("[ID:%d] %s - ₩%.2f (재고: %d개)\n", 
                   product.id, product.name.c_str(), 
                   product.price, product.stock);
            printf("    카테고리: %s\n", product.category.c_str());
            printf("    설명: %s\n\n", product.description.c_str());
            found = true;
        }
    }
    
    if(!found) {
        printf("'%s'에 대한 검색 결과가 없습니다.\n", keyword.c_str());
    }
    
    getString("계속하려면 Enter를 누르세요...");
    return OK;
}

int ShopService::nextProductTablePage() {
    updateProductList(++m_currPage);
    return OK;
}

int ShopService::prevProductTablePage() {
    if(m_currPage == 0)
        m_currPage = 1;
    updateProductList(--m_currPage);
    return OK;
}

int ShopService::viewOrderDetails() {
    // 이 함수는 현재 구현에서 직접 호출되지 않음
    return OK;
}

// ============================ 장바구니 관리 함수들 ============================

void ShopService::updateCartList() {
    bool ret = setCartListByPage();
    if(ret) {
        std::cerr << "updateCartList Failed" << std::endl;
    }
}

bool ShopService::setCartListByPage() {
    if (m_table) {
        std::vector<std::string> cartStrings;
        
        if(m_cart.getItems().empty()) {
            cartStrings.push_back("장바구니가 비어있습니다.");
        } else {
            // 장바구니 항목들을 문자열로 변환
            const auto& items = m_cart.getItems();
            double total = 0.0;
            
            for(const auto& item : items) {
                Product* product = m_productManager->getById(item.pid);
                double subtotal = item.unitPrice * item.quantity;
                total += subtotal;
                
                std::ostringstream oss;
                oss << "|" << std::setw(4) << std::left << item.pid
                    << "|" << std::setw(30) << std::left << (product ? product->name : "Unknown Product")
                    << "|" << std::setw(8) << std::left << item.quantity
                    << "|" << std::setw(12) << std::left << std::fixed << std::setprecision(2) << item.unitPrice
                    << "|" << std::setw(12) << std::left << std::fixed << std::setprecision(2) << subtotal;
                
                cartStrings.push_back(oss.str());
            }
            
            // 총액 추가
            std::string separator = std::string(g_max_cmd_width, '=');
            cartStrings.push_back(separator);
            
            std::ostringstream totalOss;
            totalOss << "총 금액: ₩" << std::fixed << std::setprecision(2) << total;
            cartStrings.push_back(totalOss.str());
        }
        
        // 헤더와 구분선 추가
        std::string separator = std::string(g_max_cmd_width, '-');
        std::ostringstream headerOss;
        headerOss << "|" << std::setw(4) << std::left << "ID"
                  << "|" << std::setw(30) << std::left << "상품명"
                  << "|" << std::setw(8) << std::left << "수량"
                  << "|" << std::setw(12) << std::left << "단가"
                  << "|" << std::setw(12) << std::left << "소계";
        
        cartStrings.insert(cartStrings.begin(), separator);
        cartStrings.insert(cartStrings.begin(), headerOss.str());
        
        m_table->setTable(cartStrings);
    } else {
        std::cerr << "Table is not initialized." << std::endl;
        return false;
    }
    return true;
}

// ============================ 헬퍼 함수들 ============================

void ShopService::displayCart() {
    const auto& items = m_cart.getItems();
    double total = 0.0;
    
    for(const auto& item : items) {
        Product* product = m_productManager->getById(item.pid);
        double subtotal = item.unitPrice * item.quantity;
        total += subtotal;
        
        printf("%s\n", product ? product->name.c_str() : "Unknown Product");
        printf("   수량: %d개 | 단가: ₩%.2f | 소계: ₩%.2f\n\n", 
               item.quantity, item.unitPrice, subtotal);
    }
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("총 금액: ₩%.2f\n", total);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

void ShopService::displayProductDetails(const Product& product) {
    printf("\n상품 정보\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("상품명: %s\n", product.name.c_str());
    printf("가격: ₩%.2f\n", product.price);
    printf("카테고리: %s\n", product.category.c_str());
    printf("재고: %d개\n", product.stock);
    printf("설명: %s\n", product.description.c_str());
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}