#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <sstream>
#include <iomanip>
#include "Model.h"

struct Product : public Model {
    int id;
    std::string name;
    std::string category;
    double price;
    int stock;
    std::string description;
    std::string date;

    // ========= 생성자 정의 =========    
    Product(int id = 0, const std::string& name = "", const std::string& category = "", 
            double price = 0.0, int stock = 0, const std::string& description = "", 
            const std::string& date = "")
        : id(id), name(name), category(category), price(price), 
          stock(stock), description(description), date(date) {}

    Product(const Product& other) = default; // 복사 생성자
    Product(Product&& other) noexcept = default; // 이동 생성자
    
    // ========= 대입 연산자 정의 =========
    // 복사 대입 연산자
    Product& operator=(const Product& other) {
        if (this != &other) {
            id = other.id;
            name = other.name;
            category = other.category;
            price = other.price;
            stock = other.stock;
            description = other.description;
            date = other.date;
        }
        return *this;
    }

    // 이동 대입 연산자
    Product& operator=(Product&& other) noexcept {
        if (this != &other) {
            id = other.id;
            name = std::move(other.name);
            category = std::move(other.category);
            price = other.price;
            stock = other.stock;
            description = std::move(other.description);
            date = std::move(other.date);
        }
        return *this;
    }

    // ========= 비교 연산자 정의 =========
    bool operator==(const Product& other) const {
        return id == other.id;
    }

    bool operator!=(const Product& other) const {
        return !(*this == other);
    }

    // CSV 형식으로 변환하는 메서드
    std::string toCsv() const {
        return std::to_string(id) + "," + 
               name + "," + 
               category + "," + 
               std::to_string(price) + "," + 
               std::to_string(stock) + "," + 
               description + "," + 
               date;
    }

    // CSV 형식으로부터 객체를 초기화하는 메서드
    void fromCsv(const std::string& csv) {
        std::istringstream ss(csv);
        std::string token;
        
        std::getline(ss, token, ',');
        id = std::stoi(token);
        
        std::getline(ss, name, ',');
        std::getline(ss, category, ',');
        
        std::getline(ss, token, ',');
        price = std::stod(token);
        
        std::getline(ss, token, ',');
        stock = std::stoi(token);
        
        std::getline(ss, description, ',');
        std::getline(ss, date, ',');
    }



    std::string getMemberValueString() const override {
        std::ostringstream oss;
        
        // 각 필드를 적절한 폭으로 패딩
        std::string idStr = std::to_string(id);
        std::string priceStr = std::to_string(price);
        // 가격을 소수점 2자리로 포맷
        std::ostringstream priceStream;
        priceStream << std::fixed << std::setprecision(2) << price;
        priceStr = priceStream.str();
        
        std::string stockStr = std::to_string(stock);
        
        oss << "|" << padString(idStr, 4, false)
            << "|" << padString(name, 30, false)
            << "|" << padString(category, 15, false)
            << "|" << padString(priceStr, 13, true)
            << "|" << padString(stockStr, 8, true)
            << "|" << padString(description, 60, false)
            << "|" << padString(date, 12, false);
        
        return oss.str();
    }

    std::string getMemberNameString() const override {
        std::ostringstream oss;
        
        oss << "|" << padString("ID", 4, false)
            << "|" << padString("상품명", 30, false)
            << "|" << padString("카테고리", 15, false)
            << "|" << padString("가격", 13, false)
            << "|" << padString("재고", 8, false)
            << "|" << padString("설명", 60, false)
            << "|" << padString("등록일", 12, false);
        
        return oss.str();
    }


    // 재고 관리 메서드
    bool updateStock(int quantity) {
        if (stock + quantity < 0) {
            return false; // 재고 부족
        }
        stock += quantity;
        return true;
    }

    bool isInStock() const {
        return stock > 0;
    }


private:
    // 한글 문자 개수를 계산하는 헬퍼 함수
    size_t getDisplayWidth(const std::string& str) const {
        size_t width = 0;
        for (size_t i = 0; i < str.length(); ) {
            unsigned char c = str[i];
            if (c < 0x80) {
                // ASCII 문자 (1바이트)
                width += 1;
                i += 1;
            } else if ((c & 0xE0) == 0xC0) {
                // 2바이트 UTF-8 문자
                width += 2;
                i += 2;
            } else if ((c & 0xF0) == 0xE0) {
                // 3바이트 UTF-8 문자 (한글 포함)
                width += 2;
                i += 3;
            } else if ((c & 0xF8) == 0xF0) {
                // 4바이트 UTF-8 문자
                width += 2;
                i += 4;
            } else {
                // 잘못된 UTF-8, 1바이트로 처리
                width += 1;
                i += 1;
            }
        }
        return width;
    }
        // 문자열을 지정된 폭으로 패딩하는 함수
    std::string padString(const std::string& str, size_t targetWidth, bool rightAlign = false) const {
        size_t currentWidth = getDisplayWidth(str);
        if (currentWidth >= targetWidth) {
            return str;
        }
        
        size_t padding = targetWidth - currentWidth;
        if (rightAlign) {
            return std::string(padding, ' ') + str;
        } else {
            return str + std::string(padding, ' ');
        }
    }
};

#endif // PRODUCT_H