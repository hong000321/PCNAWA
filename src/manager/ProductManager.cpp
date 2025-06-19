#include "ProductManager.h"
#include <cstdio>

ProductManager::ProductManager(std::unique_ptr<IRepository<Product>> repo) {
    m_repo = std::move(repo);
}

ProductManager& ProductManager::operator=(ProductManager&& other) noexcept {
    if(this != &other) {
        m_repo = std::move(other.m_repo);
    }
    return *this;
}

std::vector<std::string> ProductManager::getProductsString(int start, int end) const {
    std::vector<std::string> productStrings;
    for (const auto& product : m_repo->get(start, end)) {
        std::string tmpString = product.getMemberValueString();
        productStrings.push_back(tmpString);
    }
    return productStrings;
}

std::string ProductManager::getProductTitleString() const {
    return Product().getMemberNameString();
}

Product* ProductManager::getProductByName(const std::string& name) {
    std::vector<Product> products = m_repo->getAll();
    int id = -1;
    for(auto product : products) {
        if(product.name == name) {
            id = product.id;
            break;
        }
    }
    if(id <= 0) {
        return nullptr;
    }
    return m_repo->getById(id);
}

std::vector<int> ProductManager::getProductsByCategory(const std::string& category) {
    std::vector<int> categoryProducts;
    std::vector<Product> products = m_repo->getAll();
    for(auto& product : products) {
        if(product.category == category) {
            categoryProducts.push_back(product.id);
        }
    }
    return categoryProducts;
}

std::vector<int> ProductManager::getProductsInPriceRange(double minPrice, double maxPrice) {
    std::vector<int> rangeProductIds;
    std::vector<Product> products = m_repo->getAll();
    
    for(const auto& product : products) {
        if(product.price >= minPrice && product.price <= maxPrice) {
            rangeProductIds.push_back(product.id);  // ID만 반환 (안전)
        }
    }
    return rangeProductIds;
}

std::vector<int> ProductManager::getLowStockProducts(int threshold) {
    std::vector<int> lowStockProducts;
    std::vector<Product> products = m_repo->getAll();
    int cnt = 0;
    for(auto& product : products) {
        if(product.stock <= threshold) {
            lowStockProducts.push_back(product.id);
            
            printf("id = %d    | cnt = %d\n", product.id, cnt);
            
            cnt++;
        }
    }
    printf("cnt = %d\n", cnt);
    return lowStockProducts;
}

bool ProductManager::adjustStock(int productId, int delta) {
    Product* product = getById(productId);
    if(product == nullptr) {
        return false;
    }
    if(!product->adjustStock(delta)) {
        return false;
    }
    return update(*product);
}

double ProductManager::getTotalInventoryValue() {
    double total = 0.0;
    std::vector<Product> products = m_repo->getAll();
    for(const auto& product : products) {
        total += product.price * product.stock;
    }
    return total;
}