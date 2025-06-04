#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <sstream>
#include <iostream>

struct Product{
    int id;
    std::string name;
    std::string date;
    double price;

    // =========== 생성자 정의 ===========
    Product(int id = 0, const std::string& name = "", 
            const std::string& date = "", double price = 0.0)
        : id(id), name(name), date(date), price(price) {}
    Product(const Product& other) = default;
    Product(Product&& other) noexcept = default;

    // =========== 대입 연산자 정의 ===========
    // 복사 대입 연산자
    Product& operator=(const Product& other) {
        if (this != &other) {
            id = other.id;
            name = other.name;
            date = other.date;
            price = other.price;
        }
        return *this;
    }

    // 이동 대입 연산자
    Product& operator=(Product&& other) noexcept {
        if (this != &other) {
            id = other.id;
            name = other.name;
            date = other.date;
            price = other.price;
        }
        return *this;
    }

    // =========== 비교 연산자 정의 ===========    
    bool operator==(const Product& other) const {
        return id == other.id;
    }
    bool operator!=(const Product& other) const {
        return !(*this == other);
    }


    // =========== 멤버 함수 정의 ===========
    // Getter와 Setter 메서드 정의
    int getId() const {
        return id;
    }
    std::string getName() const {
        return name;
    }
    std::string getDate() const {
        return date;
    }
    double getPrice() const {
        return price;
    }
    void setId(int newId) {
        id = newId;
    }
    void setName(const std::string& newName) {
        name = newName;
    }
    void setDate(const std::string& newDate) {
        date = newDate;
    }
    void setPrice(double newPrice) {
        price = newPrice;
    }

    // CSV 형식으로 변환하는 메서드
    std::string toCsv() const {
        return std::to_string(id) + "," + name + "," + date + "," + std::to_string(price);
    }

    // CSV 형식으로부터 객체를 초기화하는 메서드
    void fromCsv(const std::string& csv) {
        std::istringstream ss(csv);
        std::string token;

        std::getline(ss, token, ',');
        id = std::stoi(token);

        std::getline(ss, name, ',');

        std::getline(ss, date, ',');

        std::getline(ss, token, ',');
        price = std::stod(token);
    }
};


#endif // PRODUCT_H