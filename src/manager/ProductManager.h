/**
 * @file ProductManager.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 상품 관련 비즈니스 로직을 처리하는 매니저 클래스
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include "../repository/CsvRepository.h"
#include "../models/Product.h"
#include "BaseManager.h"
#include <memory>
#include <vector>
#include <string>

class ProductManager : public BaseManager<Product> {
public:
    ProductManager() = default;
    ProductManager(std::unique_ptr<IRepository<Product>> repo);
    
    ProductManager& operator=(ProductManager&& other) noexcept;
    
    ~ProductManager() = default;

    // 복사 절대 불가
    ProductManager(const ProductManager&) = delete;
    ProductManager& operator=(const ProductManager&) = delete;

    /**
     * @brief 상품 목록을 cmd 출력에 맞춰 표 형태의 string 배열로 반환
     * @param start : 시작 인덱스 (기본값: 0)
     * @param end : 끝 인덱스 (기본값: 10)
     * @return std::vector<std::string> 
     */
    std::vector<std::string> getProductsString(int start = 0, int end = 10) const;
    
    /**
     * @brief 상품 테이블의 타이틀들을 cmd 출력에 맞춰 표 형태의 string으로 반환
     * @return std::string 
     */
    std::string getProductTitleString() const;
    
    /**
     * @brief 이름으로 상품을 검색하는 메서드
     * @param name : 검색할 상품 이름
     * @return Product* 
     */
    Product* getProductByName(const std::string& name);
    
    /**
     * @brief 카테고리별 상품 ID들을 반환하는 메서드
     * @param category : 검색할 카테고리명
     * @return std::vector<int> 
     */
    std::vector<int> getProductsByCategory(const std::string& category);
    
    /**
     * @brief 가격 범위 내 상품 ID들을 반환하는 메서드
     * @param minPrice : 최소 가격
     * @param maxPrice : 최대 가격
     * @return std::vector<int> 
     */
    std::vector<int> getProductsInPriceRange(double minPrice, double maxPrice);
    
    /**
     * @brief 재고가 부족한 상품 ID들을 반환하는 메서드
     * @param threshold : 재고 임계값 (기본값: 5)
     * @return std::vector<int> 
     */
    std::vector<int> getLowStockProducts(int threshold = 5);
    
    /**
     * @brief 상품의 재고를 조정하는 메서드
     * @param productId : 상품 ID
     * @param delta : 재고 증감량
     * @return bool 성공 여부
     */
    bool adjustStock(int productId, int delta);
    
    /**
     * @brief 전체 재고의 총 가치를 계산하는 메서드
     * @return double 
     */
    double getTotalInventoryValue();
};

#endif // PRODUCTMANAGER_H