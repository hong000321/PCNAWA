#ifndef SHOPSERVICE_H
#define SHOPSERVICE_H

#include "../manager/ProductManager.h"
#include "../manager/OrderManager.h"
#include "../ui/DisplayTitle.h"
#include "../ui/DisplayMenu.h"
#include "../ui/DisplayTable.h"
#include "../ui/DisplayWidget.h"

#include <vector>

class ShopService : public DisplayWidget {
    // ShopService는 고객용 쇼핑 기능을 제공합니다.
private:
    OrderManager m_orderManager;
    ProductManager* m_productManager = nullptr;
    
    DisplayTitle* m_title = nullptr;
    DisplayTable* m_table = nullptr;
    DisplayMenu* m_menu = nullptr;
    
    int m_currPage = 0;
    int m_currentUserId = 1;  // 현재 로그인한 고객 ID
    std::vector<std::vector<std::string>> m_strMet;
    
    // 장바구니
    Order m_cart;

    void updateProductList(int page = -1);
    bool setProductListByPage(int page);

    // 고객 기능들
    int prevPage();
    int addToCart();
    int viewCart();
    int removeFromCart();
    int checkout();
    int viewMyOrders();
    int searchProduct();
    int nextProductTablePage();
    int prevProductTablePage();

    // 주문 상세 보기
    int viewOrderDetails();

    // 장바구니 관리 함수들
    void updateCartList();
    bool setCartListByPage();

    // 헬퍼 함수들
    void displayCart();
    void displayProductDetails(const Product& product);
    
    std::vector<SelectMenu> Select_Main_Page = {
        {"뒤로가기",         [this]() -> int { return prevPage(); }},
        {"장바구니에 담기",  [this]() -> int { return addToCart(); }},
        {"장바구니 보기",    [this]() -> int { return viewCart(); }},
        {"내 주문 내역",     [this]() -> int { return viewMyOrders(); }},
        // {"상품 검색",        [this]() -> int { return searchProduct(); }},
        {"이전 페이지",      [this]() -> int { return prevProductTablePage(); }},
        {"다음 페이지",      [this]() -> int { return nextProductTablePage(); }}
    };
    
    std::vector<SelectMenu> Select_Cart_Page = {
        {"뒤로가기",         [this]() -> int { return prevPage(); }},
        {"상품 제거",        [this]() -> int { return removeFromCart(); }},
        {"주문하기",         [this]() -> int { return checkout(); }}
    };

public:
    ShopService(ProductManager* productManager = nullptr);
    ~ShopService() = default;

    // 복사 및 대입 연산자 삭제
    ShopService(const ShopService&) = delete;
    ShopService& operator=(const ShopService&) = delete;

    void start();
    void updateMenu(std::vector<SelectMenu>& page) const;
    
    // 고객 ID 설정
    void setCurrentUserId(int userId) { m_currentUserId = userId; }
    int getCurrentUserId() const { return m_currentUserId; }
};

#endif // SHOPSERVICE_H