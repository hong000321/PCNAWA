/**
 * @file ShopService.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 고객용 쇼핑 기능을 제공하는 서비스 클래스
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef SHOPSERVICE_H
#define SHOPSERVICE_H

#include "../manager/ProductManager.h"
#include "../manager/OrderManager.h"
#include "../view/DisplayTitle.h"
#include "../view/DisplayMenu.h"
#include "../view/DisplayTable.h"
#include "../view/DisplayWidget.h"

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

    /**
     * @brief 상품 목록을 업데이트하는 메서드
     * @param page : 페이지 번호 (기본값: -1)
     */
    void updateProductList(int page = -1);
    
    /**
     * @brief 페이지별 상품 목록을 설정하는 메서드
     * @param page : 페이지 번호
     * @return bool 성공 여부
     */
    bool setProductListByPage(int page);

    // 고객 기능들
    /**
     * @brief 이전 페이지로 이동하는 메서드
     * @return int 상태 코드
     */
    int prevPage();
    
    /**
     * @brief 장바구니에 상품을 추가하는 메서드
     * @return int 상태 코드
     */
    int addToCart();
    
    /**
     * @brief 장바구니를 보는 메서드
     * @return int 상태 코드
     */
    int viewCart();
    
    /**
     * @brief 장바구니에서 상품을 제거하는 메서드
     * @return int 상태 코드
     */
    int removeFromCart();
    
    /**
     * @brief 주문을 완료하는 메서드
     * @return int 상태 코드
     */
    int checkout();
    
    /**
     * @brief 내 주문 내역을 보는 메서드
     * @return int 상태 코드
     */
    int viewMyOrders();
    
    /**
     * @brief 상품을 검색하는 메서드
     * @return int 상태 코드
     */
    int searchProduct();
    
    /**
     * @brief 상품 테이블 다음 페이지로 이동하는 메서드
     * @return int 상태 코드
     */
    int nextProductTablePage();
    
    /**
     * @brief 상품 테이블 이전 페이지로 이동하는 메서드
     * @return int 상태 코드
     */
    int prevProductTablePage();

    /**
     * @brief 주문 상세 정보를 보는 메서드
     * @return int 상태 코드
     */
    int viewOrderDetails();

    // 장바구니 관리 함수들
    /**
     * @brief 장바구니 목록을 업데이트하는 메서드
     */
    void updateCartList();
    
    /**
     * @brief 페이지별 장바구니 목록을 설정하는 메서드
     * @return bool 성공 여부
     */
    bool setCartListByPage();

    // 헬퍼 함수들
    /**
     * @brief 장바구니를 화면에 표시하는 메서드
     */
    void displayCart();
    
    /**
     * @brief 상품 상세정보를 화면에 표시하는 메서드
     * @param product : 표시할 상품 정보
     */
    void displayProductDetails(const Product& product);
    
    std::vector<SelectMenu> Select_Main_Page = {
        {"뒤로가기",         [this]() -> int { return prevPage(); }},
        {"장바구니에 담기",  [this]() -> int { return addToCart(); }},
        {"장바구니 보기",    [this]() -> int { return viewCart(); }},
        {"내 주문 내역",     [this]() -> int { return viewMyOrders(); }},
        {"이전 페이지",      [this]() -> int { return prevProductTablePage(); }},
        {"다음 페이지",      [this]() -> int { return nextProductTablePage(); }}
    };
    
    std::vector<SelectMenu> Select_Cart_Page = {
        {"뒤로가기",         [this]() -> int { return prevPage(); }},
        {"상품 제거",        [this]() -> int { return removeFromCart(); }},
        {"주문하기",         [this]() -> int { return checkout(); }}
    };

public:
    /**
     * @brief ShopService 생성자
     * @param productManager : ProductManager 포인터 (기본값: nullptr)
     */
    ShopService(ProductManager* productManager = nullptr);
    ~ShopService() = default;

    // 복사 및 대입 연산자 삭제
    ShopService(const ShopService&) = delete;
    ShopService& operator=(const ShopService&) = delete;

    /**
     * @brief 서비스를 시작하는 메서드
     */
    void start();
    
    /**
     * @brief 메뉴를 업데이트하는 메서드
     * @param page : 메뉴 페이지 벡터 참조
     */
    void updateMenu(std::vector<SelectMenu>& page) const;
    
    /**
     * @brief 현재 사용자 ID를 설정하는 메서드
     * @param userId : 설정할 사용자 ID
     */
    void setCurrentUserId(int userId) { m_currentUserId = userId; }
    
    /**
     * @brief 현재 사용자 ID를 반환하는 메서드
     * @return int 현재 사용자 ID
     */
    int getCurrentUserId() const { return m_currentUserId; }
};
#endif