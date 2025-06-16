#ifndef PRODUCTMANAGESERVICE_H
#define PRODUCTMANAGESERVICE_H

#include "../manager/ProductManager.h"
#include "../ui/DisplayTitle.h"
#include "../ui/DisplayMenu.h"
#include "../ui/DisplayTable.h"
#include "../ui/DisplayWidget.h"

#include <map>
#include <vector>

#define PRODUCT_CSV_PATH "./product.csv"

class ProductManageService : public DisplayWidget {
    // ProductManageService는 DisplayWidget을 상속받아 상품 관리 UI를 구현합니다.
    // 상품 목록을 표시하고, 상품 검색, 수정, 추가, 제거, 재고 관리 등의 기능을 제공합니다.
    // DisplayWidget을 통해 콘솔 기반의 사용자 인터페이스를 제공합니다.
private:
    ProductManager m_productManager;
    DisplayTitle* m_title = nullptr;
    DisplayTable* m_table = nullptr;
    DisplayMenu* m_menu = nullptr;
    
    int m_currPage = 0;
    int m_currId = 0;
    std::vector<std::vector<std::string>> m_strMet;

    void updateProductList(int page = -1);

    bool setProductListByPage(int page);

    // select functions for main page
    int prevPage();
    int selectProductById();
    int selectProductByName();
    int selectProductByCategory();
    int addProduct();
    int delProduct();
    int nextProductTablePage();
    int prevProductTablePage();
    int showLowStockProducts();
    int showInventoryValue();

    // product detail page functions
    int updateProductPage(int id);
    int setProductPageById(int id);
    int modifyProduct();
    int updateStock();
    int viewProductDetails();

    // search functions
    int searchByPriceRange();
    int searchByCategory();

    std::vector<SelectMenu> Select_Main_Page = {
        {"뒤로가기",           [this]() -> int { return prevPage(); }},
        {"상품 선택(이름)",    [this]() -> int { return selectProductByName(); }},
        {"상품 선택(ID)",      [this]() -> int { return selectProductById(); }},
        {"카테고리별 검색",    [this]() -> int { return selectProductByCategory(); }},
        {"상품 추가",          [this]() -> int { return addProduct(); }},
        {"상품 제거",          [this]() -> int { return delProduct(); }},
        {"재고 부족 상품",     [this]() -> int { return showLowStockProducts(); }},
        {"재고 총 가치",       [this]() -> int { return showInventoryValue(); }},
        // {"가격대별 검색",      [this]() -> int { return searchByPriceRange(); }},
        {"이전 페이지",        [this]() -> int { return prevProductTablePage(); }},
        {"다음 페이지",        [this]() -> int { return nextProductTablePage(); }}
    };
    
    std::vector<SelectMenu> Select_Product_Page = {
        {"뒤로가기",          [this]() -> int { return prevPage(); }},
        {"상품 수정",         [this]() -> int { return modifyProduct(); }},
        {"재고 수정",         [this]() -> int { return updateStock(); }},
        {"상품 상세보기",     [this]() -> int { return viewProductDetails(); }}
    };

    std::vector<SelectMenu> Select_Search_Page = {
        {"뒤로가기",          [this]() -> int { return prevPage(); }},
        {"카테고리별 검색",   [this]() -> int { return searchByCategory(); }},
        {"가격대별 검색",     [this]() -> int { return searchByPriceRange(); }}
    };

    std::vector<SelectMenu> Select_Null_Page = {};

public:
    ProductManageService();
    ~ProductManageService() = default;

    void start();
    void updateMenu(std::vector<SelectMenu>& page) const;
};

#endif // PRODUCTMANAGESERVICE_H