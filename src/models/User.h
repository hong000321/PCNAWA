/**
 * @file User.h
 * @author Dae O Hong (hong000321@gmail.com)
 * @brief 사용자 정보를 관리하는 User 구조체 정의
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef USER_H
#define USER_H
#include <string>
#include "Model.h"

enum {
    USER,         // 일반 사용자 권한 (0)
    ADMIN,        // 관리자 권한 (1) - 상품 편집 가능
    SUPER_ADMIN   // 최고 관리자 권한 (2) - 사용자 삭제 등 모든 권한
};

struct User : public Model {
    int id;                      // 사용자 고유 식별자
    int permissionLevel;         // 권한 레벨 (0: User, 1: Admin, 2: Super Admin)
    std::string name;            // 사용자 이름
    std::string email;           // 이메일 주소
    std::string password;        // 비밀번호
    std::string registDate;      // 가입일

    // ========= 생성자 정의 =========
    User(int id = 0, int permissionLevel = 0, const std::string& name = "", 
         const std::string& email = "", const std::string& password = "", 
         const std::string& registDate = "")
        : id(id), permissionLevel(permissionLevel), name(name), 
          email(email), password(password), registDate(registDate) {}
    User(const User& other) = default;
    User(User&& other) noexcept = default;
    
    // ========= 대입 연산자 정의 =========
    User& operator=(const User& other) {
        if (this != &other) {
            id = other.id;
            permissionLevel = other.permissionLevel;
            name = other.name;
            email = other.email;
            password = other.password;
            registDate = other.registDate;
        }
        return *this;
    }

    User& operator=(User&& other) noexcept {
        if (this != &other) {
            id = other.id;
            permissionLevel = other.permissionLevel;
            name = std::move(other.name);
            email = std::move(other.email);
            password = std::move(other.password);
            registDate = std::move(other.registDate);
        }
        return *this;
    }

    // ========= 비교 연산자 정의 =========
    bool operator==(const User& other) const {
        return id == other.id;
    }

    bool operator!=(const User& other) const {
        return !(*this == other);
    }

    
    // ============== Model 가상 함수 정의 ==============
    std::string toCsv() const override{
        return std::to_string(id) + "," + 
               std::to_string(permissionLevel) + "," + 
               name + "," + 
               email + "," + 
               password + "," + 
               registDate;
    }
    
    void fromCsv(const std::string& csv) override{
        std::istringstream ss(csv);
        std::string token;
        
        std::getline(ss, token, ',');
        id = std::stoi(token);
        
        std::getline(ss, token, ',');
        permissionLevel = std::stoi(token);
        
        std::getline(ss, name, ',');
        std::getline(ss, email, ',');
        std::getline(ss, password, ',');
        std::getline(ss, registDate, ',');
    }

    std::string getMemberValueString() const override{
        std::ostringstream oss;
        oss << "|" << std::setw(4) << std::left << id
            << "|" << std::setw(17) << std::left << permissionLevel
            << "|" << std::setw(25) << std::left << name
            << "|" << std::setw(30) << std::left << email
            << "|" << std::setw(15) << std::left << password
            << "|" << std::setw(10) << std::left << registDate;
        return oss.str();
    }

    std::string getMemberNameString() const override{
        std::ostringstream oss;
        oss << "|" << std::setw(4) << std::left << "ID" 
            << "|" << std::setw(17) << std::left << "Permission Level"
            << "|" << std::setw(24) << std::left << "이름"
            << "|" << std::setw(30) << std::left << "Email"
            << "|" << std::setw(15) << std::left << "Password"
            << "|" << std::setw(10) << std::left << "Date";
        return oss.str();
    }

    // ================== public 고유 함수 정의 ==================
    /**
     * @brief 문자열로 권한 레벨 설정
     * @param level 권한 레벨 문자열 ("User", "Admin", "Super Admin")
     * @return true 성공적으로 권한 레벨 설정
     * @return false 잘못된 권한 레벨 문자열
     */
    bool setPermissionLevel(const std::string& level) {
        if (level == "User") {
            permissionLevel = USER;
        } else if (level == "Admin") {
            permissionLevel = ADMIN;
        } else if (level == "Super Admin") {
            permissionLevel = SUPER_ADMIN;
        } else {
            return false; // 잘못된 권한 레벨
        }
        return true; // 성공적으로 권한 레벨 설정
    }

    /**
     * @brief 특정 권한 레벨 이상의 권한을 가지고 있는지 확인
     * @param requiredLevel 필요한 최소 권한 레벨
     * @return true 필요한 권한을 가지고 있음
     * @return false 권한 부족
     */
    bool hasPermission(int requiredLevel) const {
        return permissionLevel >= requiredLevel;
    }

    /**
     * @brief 상품 편집 권한 확인
     * @return true ADMIN 이상의 권한을 가지고 있음
     * @return false 권한 부족
     */
    bool canEditProduct() const {
        return hasPermission(ADMIN);
    }
    
    /**
     * @brief 사용자 삭제 권한 확인
     * @return true SUPER_ADMIN 권한을 가지고 있음
     * @return false 권한 부족
     */
    bool canDeleteUser() const {
        return hasPermission(SUPER_ADMIN);
    }

};
#endif // USER_H