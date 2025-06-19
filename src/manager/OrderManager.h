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

    // 멤버 함수 선언
    std::vector<std::string> getOrdersString(int start = 0, int end = 10) const;
    std::string getOrderTitleString() const;
    Order* getOrderByUserId(int userId);
    std::vector<int> getOrdersByUserId(int userId);
    double getTotalRevenue() const;
    int getOrderCountByUserId(int userId) const;
};

#endif // ORDERMANAGER_H