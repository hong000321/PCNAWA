#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "../repository/CsvRepository.h"
#include "../models/User.h"
#include "BaseManager.h"
#include <memory>
#include <vector>
#include <string>

class UserManager : public BaseManager<User> {
public:
    UserManager() = default;
    UserManager(std::unique_ptr<IRepository<User>> repo);
    
    UserManager& operator=(UserManager&& other) noexcept;
    
    ~UserManager() = default;

    // 복사 절대 불가
    UserManager(const UserManager&) = delete;
    UserManager& operator=(const UserManager&) = delete;

    // 멤버 함수 선언
    std::vector<std::string> getUsersString(int start = 0, int end = 10) const;
    std::string getUserTitleString() const;
    User* getUserByName(const std::string& name);
};

#endif // USERMANAGER_H