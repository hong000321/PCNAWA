/**
 * @file ProductManageService.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 상품 관리 비즈니스 로직과 UI를 처리하는 서비스 클래스
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef PRODUCTMANAGESERVICE_H
#define PRODUCTMANAGESERVICE_H

#include "../manager/ProductManager.h"
#include "../view/DisplayTitle.h"
#include "../view/DisplayMenu.h"
#include "../view/DisplayTable.h"
#include "../view/DisplayWidget.h"

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

    // 메인 페이지 선택 함수들
    /**
     * @brief 이전 페이지로 이동하는 메서드
     * @return int 상태 코드
     */
    int prevPage();
    
    /**
     * @brief ID로 상품을 선택하는 메서드
     * @return int 상태 코드
     */
    int selectProductById();
    
    /**
     * @brief 이름으로 상품을 선택하는 메서드
     * @return int 상태 코드
     */
    int selectProductByName();
    
    /**
     * @brief 카테고리로 상품을 선택하는 메서드
     * @return int 상태 코드
     */
    int selectProductByCategory();
    
    /**
     * @brief 새 상품을 추가하는 메서드
     * @return int 상태 코드
     */
    int addProduct();
    
    /**
     * @brief 상품을 삭제하는 메서드
     * @return int 상태 코드
     */
    int delProduct();
    
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
     * @brief 재고 부족 상품을 표시하는 메서드
     * @return int 상태 코드
     */
    int showLowStockProducts();
    
    /**
     * @brief 재고 총 가치를 표시하는 메서드
     * @return int 상태 코드
     */
    int showInventoryValue();

    // 상품 상세 페이지 함수들
    /**
     * @brief 상품 페이지를 업데이트하는 메서드
     * @param id : 상품 ID
     * @return int 상태 코드
     */
    int updateProductPage(int id);
    
    /**
     * @brief ID로 상품 페이지를 설정하는 메서드
     * @param id : 상품 ID
     * @return int 상태 코드
     */
    int setProductPageById(int id);
    
    /**
     * @brief 상품 정보를 수정하는 메서드
     * @return int 상태 코드
     */
    int modifyProduct();
    
    /**
     * @brief 재고를 조정하는 메서드
     * @return int 상태 코드
     */
    int adjustStock();
    
    /**
     * @brief 상품 상세정보를 보는 메서드
     * @return int 상태 코드
     */
    int viewProductDetails();

    // 검색 함수들
    /**
     * @brief 가격 범위로 검색하는 메서드
     * @return int 상태 코드
     */
    int searchByPriceRange();
    
    /**
     * @brief 카테고리로 검색하는 메서드
     * @return int 상태 코드
     */
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
        {"재고 수정",         [this]() -> int { return adjustStock(); }},
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

    /**
     * @brief ProductManager 참조를 반환하는 메서드
     * @return ProductManager& ProductManager 참조
     */
    ProductManager& getProductManager() { return m_productManager; }
    
    /**
     * @brief ProductManager 상수 참조를 반환하는 메서드
     * @return const ProductManager& ProductManager 상수 참조
     */
    const ProductManager& getProductManager() const { return m_productManager; }
    
    /**
     * @brief 서비스를 시작하는 메서드
     */
    void start();
    
    /**
     * @brief 메뉴를 업데이트하는 메서드
     * @param page : 메뉴 페이지 벡터 참조
     */
    void updateMenu(std::vector<SelectMenu>& page) const;
};

#endif // PRODUCTMANAGESERVICE_H