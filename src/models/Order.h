/**
 * @file Order.h
 * @author Dae O Hong (hong000321@gmail.com)
 * @brief 주문 정보를 관리하는 Order 및 OrderItem 구조체 정의
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ORDER_H
#define ORDER_H
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Product.h"
#include "Model.h"

/**
 * @brief 주문 항목 정보를 저장하는 구조체
 */
struct OrderItem {
    int pid;           // 상품 ID
    int quantity;      // 주문 수량
    double unitPrice;  // 구매 당시 가격
    
    OrderItem(int id = 0, int quantity = 0, double unitPrice = 0.0)
        : pid(id), quantity(quantity), unitPrice(unitPrice) {}
};

struct Order : public Model {
    int id;                           // 주문 고유 식별자
    int userId;                       // 주문한 사용자 ID
    std::vector<OrderItem> items;     // 주문 항목들의 벡터
    std::string orderDate;            // 주문 날짜

    // ============== 생성자 정의 ==============
    Order(int id = 0, int userId = 0, const std::string& date = "")
        : id(id), userId(userId), orderDate(date) {}
    Order(const Order& other) = default;
    Order(Order&& other) noexcept = default;
    
    // ============== 대입 연산자 정의 ==============
    Order& operator=(const Order& other) {
        if (this != &other) {
            id = other.id;
            userId = other.userId;
            items = other.items;
            orderDate = other.orderDate;
        }
        return *this;
    }

    Order& operator=(Order&& other) noexcept {
        if (this != &other) {
            id = other.id;
            userId = other.userId;
            items = std::move(other.items);
            orderDate = std::move(other.orderDate);
        }
        return *this;
    }
    
    // ============== 비교 연산자 정의 ==============
    bool operator==(const Order& other) const {
        return id == other.id;
    }

    bool operator!=(const Order& other) const {
        return !(*this == other);
    }
    
    // ============== Model 가상 함수 정의 ==============
    std::string toCsv() const override{
        std::stringstream ss;
        ss << id << "," << userId << ",";

        for (size_t i = 0; i < items.size(); ++i) {
            ss << items[i].pid << ":" << items[i].quantity << ":" << items[i].unitPrice;
            if (i != items.size() - 1)
                ss << "|";
        }

        ss << "," << orderDate;
        return ss.str();
    }

    void fromCsv(const std::string& line) override{
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');
        id = std::stoi(token);

        std::getline(ss, token, ',');
        userId = std::stoi(token);

        std::getline(ss, token, ',');
        items.clear();
        std::stringstream itemStream(token);
        std::string itemToken;
        while (std::getline(itemStream, itemToken, '|')) {
            std::stringstream fieldStream(itemToken);
            std::string field;
            int pid, quantity;
            double price;

            std::getline(fieldStream, field, ':');
            pid = std::stoi(field);
            std::getline(fieldStream, field, ':');
            quantity = std::stoi(field);
            std::getline(fieldStream, field, ':');
            price = std::stod(field);

            items.emplace_back(pid, quantity, price);
        }

        std::getline(ss, token, ',');
        orderDate = token;
    }

    std::string getMemberValueString() const override{
        std::ostringstream oss;
        oss << "|" << std::setw(4) << std::left << id
            << "|" << std::setw(17) << std::left << userId
            << "|" << std::setw(25) << std::left << orderDate;
        return oss.str();
    }

    std::string getMemberNameString() const override{
        std::ostringstream oss;
        oss << "|" << std::setw(4) << std::left << "ID" 
            << "|" << std::setw(17) << std::left << "User ID"
            << "|" << std::setw(25) << std::left << "Order Date";
        return oss.str();
    }

    // ================== public 고유 함수 정의 ==================
    /**
     * @brief 주문의 총 금액 계산
     * @return double 모든 주문 항목의 총합 (단가 × 수량의 합)
     */
    double getTotalPrice() const{
        double totalPrice = 0;
        for(const OrderItem& item : items){
            totalPrice += item.unitPrice * item.quantity;
        }
        return totalPrice;
    }

    /**
     * @brief 주문 항목 벡터의 const 참조 반환
     * @return const std::vector<OrderItem>& 주문 항목들의 벡터
     */
    const std::vector<OrderItem>& getItems() const {
        return items;
    }

    /**
     * @brief 모든 주문 항목 삭제
     */
    void clearItems() {
        items.clear();
    }

    /**
     * @brief 주문 항목 추가 (같은 상품이 있으면 수량 합산)
     * @param item 추가할 주문 항목
     */
    void addItem(const OrderItem& item) {
        for (auto& existing : items) {
            if (existing.pid == item.pid) {
                existing.quantity += item.quantity;
                return;
            }
        }
        items.push_back(item);
    }

    /**
     * @brief 주문 항목 추가 (매개변수로 직접 생성)
     * @param productId 상품 ID
     * @param price 단가
     * @param quantity 수량
     */
    void addItem(int productId, double price, int quantity) {
        OrderItem newItem(productId, quantity, price);
        items.push_back(newItem);
    }

    /**
     * @brief 특정 상품의 주문 항목 제거
     * @param productId 제거할 상품 ID
     */
    void removeItem(int productId) {
        for(auto it = items.begin(); it != items.end(); ++it) {
            if(it->pid == productId) {
                items.erase(it);
                break;
            }
        }
    }

    /**
     * @brief 주문 항목 업데이트 (없으면 추가)
     * @param productId 상품 ID
     * @param price 단가
     * @param quantity 수량
     */
    void updateItem(int productId, double price, int quantity) {
        for(auto& item : items) {
            if(item.pid == productId) {
                item.unitPrice = price;
                item.quantity = quantity;
                return;
            }
        }
        addItem(productId, price, quantity);
    }

    /**
     * @brief Product 객체를 이용한 주문 항목 업데이트
     * @param product 상품 객체
     * @param quantity 수량
     */
    void updateItem(const Product& product, int quantity) {
        for(auto& item : items) {
            if(item.pid == product.id) {
                item.unitPrice = product.price;
                item.quantity = quantity;
                return;
            }
        }
        // If item not found, add a new one
        addItem(product.id, product.price, quantity);
    }

};

#endif // ORDER_H