#ifndef ORDER_H
#define ORDER_H
#include <vector>
#include <string>
#include "Product.h"

typedef struct OrderItem {
    int id;
    int quantity;
    double unitPrice;
    
    void updateItem(int productId, double price, int quantity){
        this->id = productId;
        this->unitPrice = price;
        this->quantity = quantity;
    }
}OrderItem;

typedef struct Order {
    int id;
    int userId;
    std::vector<OrderItem> items;
    std::string orderDate;
    
    double getTotalPrice(){
        double totalPrice = 0;
        for(OrderItem item : this->items){
            totalPrice += item.unitPrice * item.quantity;
        }
        return totalPrice;
    }
}Order;
#endif
