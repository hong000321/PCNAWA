#ifndef ORDER_H
#define ORDER_H
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Product.h"
#include "Model.h"

struct OrderItem {
    int pid;
    int quantity;
    double unitPrice;  // 구매 당시 가격
    OrderItem(int id = 0, int quantity = 0, double unitPrice = 0.0)
        : pid(id), quantity(quantity), unitPrice(unitPrice) {}
};

struct Order : public Model {
    int id;
    int userId;
    std::vector<OrderItem> items;
    std::string orderDate;

    // ============== 생성자 정의 ==============
    Order(int id, int userId, const std::string& date = "")
    : id(id), userId(userId), orderDate(date) {}

    Order(const Order& other) = default;
    Order(Order&& other) noexcept = default;
    
    // ============== 대입 연산자 정의 ==============
    // 복사 대입 연산자
    Order& operator=(const Order& other) {
        if (this != &other) {
            id = other.id;
            userId = other.userId;
            items = other.items;
            orderDate = other.orderDate;
        }
        return *this;
    }

    // 이동 대입 연산자
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
        return id == other.id && userId == other.userId && items == other.items && orderDate == other.orderDate;
    }
    bool operator!=(const Order& other) const {
        return !(*this == other);
    }
    // ============== 멤버 함수 정의 ==============
    double getTotalPrice() const{
        double totalPrice = 0;
        for(const OrderItem& item : items){
            totalPrice += item.unitPrice * item.quantity;
        }
        return totalPrice;
    }


    const std::vector<OrderItem>& getItems() const {
        return items;
    }

    void clearItems() {
        items.clear();
    }

    void addItem(const OrderItem& item) {
        for (auto& existing : items) {
            if (existing.pid == item.pid) {
                existing.quantity += item.quantity;
                return;
            }
        }
        items.push_back(item);
    }

    void addItem(int productId, double price, int quantity) {
        OrderItem newItem(productId, quantity, price);
        items.push_back(newItem);
    }

    void removeItem(int productId) {
        for(auto it = items.begin(); it != items.end(); ++it) {
            if(it->pid == productId) {
                items.erase(it);
                break;
            }
        }
    }

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


    // CSV 형식으로 변환하는 메서드
    std::string toCsv() const {
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

    // CSV 형식으로부터 객체를 초기화하는 메서드
    void fromCsv(const std::string& line) {
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


    
    // getString 메서드
    std::string getMemberValueString() const override{
        // std::ostringstream를 사용하여 멤버 변수들을 문자열로 변환
        // 각 멤버 변수는 '|'로 구분되어 출력됩니다.
        std::ostringstream oss;
        oss << "|" << std::setw(4) << std::left << id
            << "|" << std::setw(17) << std::left << userId
            << "|" << std::setw(25) << std::left << orderDate;
        return oss.str();
    }

    std::string getMemberNameString() const override{
        // 멤버 변수의 이름을 '|'로 구분하여 문자열로 반환
        // 각 멤버 변수의 이름은 '|'로 구분되어 출력됩니다.
        std::ostringstream oss;
        oss << "|" << std::setw(4) << std::left << "ID" 
            << "|" << std::setw(17) << std::left << "User ID"
            << "|" << std::setw(25) << std::left << "Order Date";
        return oss.str();
    }
};
#endif
