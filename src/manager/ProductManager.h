#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include "../repository/CsvRepository.h"
#include "../models/Product.h"
#include <memory>
#include <vector>
#include <string>

class ProductManager {
private:
    std::unique_ptr<IRepository<Product>> m_productRepo;

public:
    ProductManager() = default;
    ProductManager(std::unique_ptr<IRepository<Product>> repo) {
        m_productRepo = std::move(repo);
    }

    ProductManager& operator=(ProductManager&& other) noexcept {
        if(this != &other) {
            m_productRepo = std::move(other.m_productRepo);
        }
        return *this;
    }

    ~ProductManager() = default;

    // 복사 절대 불가
    ProductManager(const ProductManager&) = delete;
    ProductManager& operator=(const ProductManager&) = delete;

    bool addProduct(const Product& product) {
        return m_productRepo->insert(product);
    }

    bool deleteProduct(int id) {
        return m_productRepo->removeById(id);
    }

    bool updateProduct(const Product& product) {
        return m_productRepo->update(product);
    }

    std::vector<Product> getAllProducts() const {
        return m_productRepo->getAll();
    }

    std::vector<std::string> getProductsString(int start = 0, int end = 10) const {
        std::vector<std::string> productStrings;
        for (const auto& product : m_productRepo->get(start, end)) {
            std::string tmpString = product.getMemberValueString();
            productStrings.push_back(tmpString);
        }
        return productStrings;
    }

    std::string getProductTitleString() const {
        return Product().getMemberNameString();
    }

    bool removeAllProducts() {
        return m_productRepo->removeAll();
    }

    Product* getProductById(int id) {
        return m_productRepo->getById(id);
    }

    Product* getProductByName(const std::string& name) {
        std::vector<Product> products = m_productRepo->getAll();
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
        return m_productRepo->getById(id);
    }

    std::vector<int> getProductsByCategory(const std::string& category) {
        std::vector<int> categoryProducts;
        std::vector<Product> products = m_productRepo->getAll();
        for(auto& product : products) {
            if(product.category == category) {
                categoryProducts.push_back(product.id);
            }
        }
        return categoryProducts;
    }

    std::vector<Product*> getProductsInPriceRange(double minPrice, double maxPrice) {
        std::vector<Product*> rangeProducts;
        std::vector<Product> products = m_productRepo->getAll();
        for(auto& product : products) {
            if(product.price >= minPrice && product.price <= maxPrice) {
                rangeProducts.push_back(&product);
            }
        }
        return rangeProducts;
    }

    std::vector<int> getLowStockProducts(int threshold = 5) {
        std::vector<int> lowStockProducts;
        std::vector<Product> products = m_productRepo->getAll();
        int cnt=0;
        for(auto& product : products) {
            if(product.stock <= threshold) {
                lowStockProducts.push_back(product.id);
                
                printf("id = %d    | cnt = %d\n",product.id,cnt);

                cnt++;
            }
        }
        printf("cnt = %d\n",cnt);
        return lowStockProducts;
    }

    bool updateStock(int productId, int quantity) {
        Product* product = getProductById(productId);
        if(product == nullptr) {
            return false;
        }
        if(!product->updateStock(quantity)) {
            return false;
        }
        return updateProduct(*product);
    }

    int getNumOfProducts() {
        return m_productRepo->getSize();
    }

    int getLastId() {
        return m_productRepo->lastId();
    }

    double getTotalInventoryValue() {
        double total = 0.0;
        std::vector<Product> products = m_productRepo->getAll();
        for(const auto& product : products) {
            total += product.price * product.stock;
        }
        return total;
    }
};

#endif // PRODUCTMANAGER_H