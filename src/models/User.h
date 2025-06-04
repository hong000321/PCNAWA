#ifndef USER_H
#define USER_H
#include <string>
#include "Model.h"


struct User : public Model {
    int id;
    int permissionLevel; // 0: User   1: Admin   2: Super Admin
    std::string name;
    std::string email;
    std::string password;
    std::string date;

    // ========= 생성자 정의 =========    
    User(int id = 0, int permissionLevel = 0, const std::string& name = "", 
         const std::string& email = "", const std::string& password = "", 
         const std::string& date = "")
        : id(id), permissionLevel(permissionLevel), name(name), 
          email(email), password(password), date(date) {}


    User(const User& other) = default; // 복사 생성자
    User(User&& other) noexcept = default; // 이동 생성자
    
    // ========= 대입 연산자 정의 =========
    // 복사 대입 연산자
    User& operator=(const User& other) {
        if (this != &other) {
            id = other.id;
            permissionLevel = other.permissionLevel;
            name = other.name;
            email = other.email;
            password = other.password;
            date = other.date;
        }
        return *this;
    }

    // 이동 대입 연산자
    User& operator=(User&& other) noexcept {
        if (this != &other) {
            id = other.id;
            permissionLevel = other.permissionLevel;
            name = std::move(other.name);
            email = std::move(other.email);
            password = std::move(other.password);
            date = std::move(other.date);
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
    // ========= 멤버 함수 정의 =========
    // Getter와 Setter 메서드 정의
    int getId() const {
        return id;
    }

    int getPermissionLevel() const {
        return permissionLevel;
    }

    std::string getName() const {
        return name;
    }

    std::string getEmail() const {
        return email;
    }

    std::string getPassword() const {
        return password;
    }

    std::string getDate() const {
        return date;
    }

    void setId(int newId) {
        id = newId;
    }

    bool setPermissionLevel(const std::string& level) {
        if (level == "User") {
            permissionLevel = 0;
        } else if (level == "Admin") {
            permissionLevel = 1;
        } else if (level == "Super Admin") {
            permissionLevel = 2;
        } else {
            return false; // 잘못된 권한 레벨
        }
        return true; // 성공적으로 권한 레벨 설정
    }

    bool setPermissionLevel(int newPermissionLevel) {
        if (newPermissionLevel < 0 || newPermissionLevel > 2) {
            return false; // 잘못된 권한 레벨
        }
        permissionLevel = newPermissionLevel;
        return true; // 성공적으로 권한 레벨 설정
    }

    void setName(const std::string& newName) {
        name = newName;
    }

    void setEmail(const std::string& newEmail) {
        email = newEmail;
    }

    void setPassword(const std::string& newPassword) {
        password = newPassword;
    }

    void setDate(const std::string& newDate) {
        date = newDate;
    }
    // CSV 형식으로 변환하는 메서드
    std::string toCsv() const {
        return std::to_string(id) + "," + 
               std::to_string(permissionLevel) + "," + 
               name + "," + 
               email + "," + 
               password + "," + 
               date;
    }
    // CSV 형식으로부터 객체를 초기화하는 메서드
    void fromCsv(const std::string& csv) {
        std::istringstream ss(csv);
        std::string token;
        
        std::getline(ss, token, ',');
        id = std::stoi(token);
        // std::cout << "ID: " << id << std::endl; // 디버깅용 출력
        
        std::getline(ss, token, ',');
        permissionLevel = std::stoi(token);
        
        std::getline(ss, name, ',');
        std::getline(ss, email, ',');
        std::getline(ss, password, ',');
        std::getline(ss, date, ',');
    }
    // getString 메서드
    std::string getMemberValueString() const override{
        // std::ostringstream를 사용하여 멤버 변수들을 문자열로 변환
        // 각 멤버 변수는 '|'로 구분되어 출력됩니다.
        std::ostringstream oss;
        oss << "|" << std::setw(4) << std::left << id
            << "|" << std::setw(17) << std::left << permissionLevel
            << "|" << std::setw(25) << std::left << name
            << "|" << std::setw(30) << std::left << email
            << "|" << std::setw(15) << std::left << password
            << "|" << std::setw(10) << std::left << date;
        return oss.str();
    }

    std::string getMemberNameString() const override{
        // 멤버 변수의 이름을 '|'로 구분하여 문자열로 반환
        // 각 멤버 변수의 이름은 '|'로 구분되어 출력됩니다.
        std::ostringstream oss;
        oss << "|" << std::setw(4) << std::left << "ID" 
            << "|" << std::setw(17) << std::left << "Permission Level"
            << "|" << std::setw(25) << std::left << "Name"
            << "|" << std::setw(30) << std::left << "Email"
            << "|" << std::setw(15) << std::left << "Password"
            << "|" << std::setw(10) << std::left << "Date";
        return oss.str();
    }
};
#endif // USER_H