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

    // 멤버 함수 선언
    std::vector<std::string> getProductsString(int start = 0, int end = 10) const;
    std::string getProductTitleString() const;
    Product* getProductByName(const std::string& name);
    std::vector<int> getProductsByCategory(const std::string& category);
    std::vector<int> getProductsInPriceRange(double minPrice, double maxPrice);
    std::vector<int> getLowStockProducts(int threshold = 5);
    bool adjustStock(int productId, int delta);
    double getTotalInventoryValue();
};

#endif // PRODUCTMANAGER_H