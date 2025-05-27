#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

typedef struct Product{
    int id;
    std::string name;
    std::string date;
    double price;
}Product;


#endif // PRODUCT_H