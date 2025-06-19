#include "OrderManager.h"
#include <iostream>

OrderManager::OrderManager(std::unique_ptr<IRepository<Order>> repo) {
    m_repo = std::move(repo);
}

OrderManager& OrderManager::operator=(OrderManager&& other) noexcept {
    if(this != &other) {
        m_repo = std::move(other.m_repo);
    }
    return *this;
}

std::vector<std::string> OrderManager::getOrdersString(int start, int end) const {
    std::vector<std::string> orderStrings;
    try {
        if(m_repo) {
            for (const auto& order : m_repo->get(start, end)) {
                std::string tmpString = order.getMemberValueString();
                orderStrings.push_back(tmpString);
            }
        }
    } catch (...) {
        orderStrings.push_back("주문 데이터를 불러올 수 없습니다.");
    }
    return orderStrings;
}

std::string OrderManager::getOrderTitleString() const {
    try {
        return Order().getMemberNameString();
    } catch (...) {
        return "주문번호|사용자ID|주문일|총액";
    }
}

Order* OrderManager::getOrderByUserId(int userId) {
    try {
        if(!m_repo) return nullptr;
        
        std::vector<Order> orders = m_repo->getAll();
        for(auto& order : orders) {
            if(order.userId == userId) {
                return m_repo->getById(order.id);
            }
        }
    } catch (...) {
        // 오류 발생 시 nullptr 반환
    }
    return nullptr;
}

std::vector<int> OrderManager::getOrdersByUserId(int userId) {
    std::vector<int> userOrders;
    try {
        if(!m_repo) return userOrders;
        
        std::vector<Order> orders = m_repo->getAll();
        for(const auto& order : orders) {
            if(order.userId == userId) {
                userOrders.push_back(order.id);
            }
        }
    } catch (...) {
        // 오류 발생 시 빈 벡터 반환
        userOrders.clear();
    }
    return userOrders;
}

double OrderManager::getTotalRevenue() const {
    double total = 0.0;
    try {
        if(!m_repo) return total;
        
        std::vector<Order> orders = m_repo->getAll();
        for(const auto& order : orders) {
            total += order.getTotalPrice();
        }
    } catch (...) {
        // 오류 발생 시 0.0 반환
        total = 0.0;
    }
    return total;
}

int OrderManager::getOrderCountByUserId(int userId) const {
    int count = 0;
    try {
        if(!m_repo) return count;
        
        std::vector<Order> orders = m_repo->getAll();
        for(const auto& order : orders) {
            if(order.userId == userId) {
                count++;
            }
        }
    } catch (...) {
        // 오류 발생 시 0 반환
        count = 0;
    }
    return count;
}