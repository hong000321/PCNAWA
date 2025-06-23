/**
 * @file OrderManager.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 주문 관련 비즈니스 로직을 처리하는 매니저 클래스
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "../repository/IRepository.h"
#include "../models/Order.h"
#include "BaseManager.h"
#include <memory>
#include <vector>
#include <string>

class OrderManager : public BaseManager<Order> {
public:
    OrderManager() = default;
    OrderManager(std::unique_ptr<IRepository<Order>> repo);
    
    OrderManager& operator=(OrderManager&& other) noexcept;
    
    ~OrderManager() = default;

    // 복사 절대 불가
    OrderManager(const OrderManager&) = delete;
    OrderManager& operator=(const OrderManager&) = delete;

    /**
     * @brief 주문 목록을 cmd 출력에 맞춰 표 형태의 string 배열로 반환
     * @param start : 시작 인덱스 (기본값: 0)
     * @param end : 끝 인덱스 (기본값: 10)
     * @return std::vector<std::string> 
     */
    std::vector<std::string> getOrdersString(int start = 0, int end = 10) const;
    
    /**
     * @brief 주문 테이블의 타이틀들을 cmd 출력에 맞춰 표 형태의 string으로 반환
     * @return std::string 
     */
    std::string getOrderTitleString() const;
    
    /**
     * @brief 사용자 ID로 주문을 검색하는 메서드
     * @param userId : 검색할 사용자 ID
     * @return Order* 
     */
    Order* getOrderByUserId(int userId);
    
    /**
     * @brief 사용자 ID로 모든 주문 ID들을 반환하는 메서드
     * @param userId : 검색할 사용자 ID
     * @return std::vector<int> 
     */
    std::vector<int> getOrdersByUserId(int userId);
    
    /**
     * @brief 전체 주문의 총 매출을 계산하는 메서드
     * @return double 
     */
    double getTotalRevenue() const;
    
    /**
     * @brief 특정 사용자의 주문 개수를 반환하는 메서드
     * @param userId : 검색할 사용자 ID
     * @return int 
     */
    int getOrderCountByUserId(int userId) const;
};

#endif // ORDERMANAGER_H