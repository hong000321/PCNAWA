/**
 * @file Product.h
 * @author Dae O Hong (hong000321@gmail.com)
 * @brief 상품 정보를 관리하는 Product 구조체 정의
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <sstream>
#include <iomanip>
#include "Model.h"

struct Product : public Model {
    int id;                      // 상품 고유 식별자
    std::string name;            // 상품명
    std::string category;        // 상품 카테고리
    double price;                // 상품 가격
    int stock;                   // 재고 수량
    std::string description;     // 상품 설명
    std::string createdDate;     // 상품 등록일

    Product(int id = 0, const std::string& name = "", const std::string& category = "", 
            double price = 0.0, int stock = 0, const std::string& description = "", 
            const std::string& createdDate = "")
        : id(id), name(name), category(category), price(price), 
          stock(stock), description(description), createdDate(createdDate) {}

    // ============== 생성자 정의 ==============
    Product(const Product& other) = default;
    Product(Product&& other) noexcept = default;
    
    // ============== 대입 연산자 정의 ==============
    Product& operator=(const Product& other) {
        if (this != &other) {
            id = other.id;
            name = other.name;
            category = other.category;
            price = other.price;
            stock = other.stock;
            description = other.description;
            createdDate = other.createdDate;
        }
        return *this;
    }

    Product& operator=(Product&& other) noexcept {
        if (this != &other) {
            id = other.id;
            name = std::move(other.name);
            category = std::move(other.category);
            price = other.price;
            stock = other.stock;
            description = std::move(other.description);
            createdDate = std::move(other.createdDate);
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

    // ============== Model 가상 함수 정의 ==============
    std::string toCsv() const override{
        return std::to_string(id) + "," + 
               name + "," + 
               category + "," + 
               std::to_string(price) + "," + 
               std::to_string(stock) + "," + 
               description + "," + 
               createdDate;
    }

    void fromCsv(const std::string& csv) override{
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
        std::getline(ss, createdDate, ',');
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
            << "|" << padString(createdDate, 12, false);
        
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

    // ================== public 고유 함수 정의 ==================
    /**
     * @brief 재고 수량 조정
     * @param delta 변경할 재고량 (음수면 감소, 양수면 증가)
     * @return true 재고 조정 성공
     * @return false 재고 부족으로 조정 실패
     */
    bool adjustStock(int delta) {
        if (stock + delta < 0) {
            return false; // 재고 부족
        }
        stock += delta;
        return true;
    }

    /**
     * @brief 재고 보유 여부 확인
     * @return true 재고가 1개 이상 있음
     * @return false 재고가 없음
     */
    bool isInStock() const {
        return stock > 0;
    }

private:
    // ================== private 고유 함수 정의 ==================
    /**
     * @brief UTF-8 문자열의 실제 출력 폭 계산
     * @param str 계산할 문자열
     * @return size_t 출력 시 차지하는 문자 폭
     * 
     * 한글은 2칸, 영문/숫자는 1칸으로 계산합니다.
     * 터미널에서의 실제 출력 폭을 정확히 계산하기 위해 사용됩니다.
     */
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

    /**
     * @brief 문자열을 지정된 폭으로 패딩
     * @param str 패딩할 문자열
     * @param targetWidth 목표 폭
     * @param rightAlign 우측 정렬 여부 (기본값: false, 좌측 정렬)
     * @return std::string 패딩된 문자열
     */
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