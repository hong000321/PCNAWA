#ifndef USERMANAGER_H
#define USERMANAGER_H
#include "../repository/CsvRepository.h"
#include "../models/User.h"
#include <memory>

class UserManager{
private:
    std::unique_ptr<IRepository<User>> m_userRepo;

public:
    UserManager() = default;
    UserManager(std::unique_ptr<IRepository<User>> repo){
        m_userRepo = std::move(repo);
    };

    UserManager& operator=(UserManager&& other) noexcept {
        if(this != &other) {
            m_userRepo = std::move(other.m_userRepo);
        }
        return *this;
    }

    ~UserManager() = default;

    // 복사 절대 불가
    UserManager(const UserManager&) = delete;
    UserManager& operator=(const UserManager&) = delete;


    bool addUser(const User& user){
        return m_userRepo->insert(user);
    }

    bool deleteUser(int id) {
        return m_userRepo->removeById(id);
    }

    bool updateUser(const User& user) {
        return m_userRepo->update(user);
    }

    std::vector<User> getAllUsers() const {
        return m_userRepo->getAll();
    }


    std::vector<std::string> getUsersString(int start = 0, int end = 10) const {
        std::vector<std::string> userStrings;
        for (const auto& user : m_userRepo->get(start, end)) {
            std::string tmpString = user.getMemberValueString();
            // std::cout << tmpString << "h_Debug" << std::endl; // 디버깅용 출력
            userStrings.push_back(tmpString);
        }
        return userStrings;
    }

    std::string getUserTitleString() const {
        return User().getMemberNameString();
    }

    bool removeAllUsers() {
        return m_userRepo->removeAll();
    }

    User* getUserById(int id) {
        return m_userRepo->getById(id);
    }

    User* getUserByName(std::string name) {
        std::vector<User> users = m_userRepo->getAll();
        int id = -1;
        for(auto user : users){
            if(user.name==name){
                id = user.id;
                break;
            }
        }
        if(id <= 0){
            return NULL;
        }
        return m_userRepo->getById(id);
        
    }

    int getNumOfUser(){
        return m_userRepo->getSize();
    }

    int getLastId(){
        return m_userRepo->lastId();
    }
};
#endif // USERMANAGER_H