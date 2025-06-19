#include "UserManager.h"

UserManager::UserManager(std::unique_ptr<IRepository<User>> repo) {
    m_repo = std::move(repo);
}

UserManager& UserManager::operator=(UserManager&& other) noexcept {
    if(this != &other) {
        m_repo = std::move(other.m_repo);
    }
    return *this;
}

std::vector<std::string> UserManager::getUsersString(int start, int end) const {
    std::vector<std::string> userStrings;
    for (const auto& user : m_repo->get(start, end)) {
        std::string tmpString = user.getMemberValueString();
        // std::cout << tmpString << "h_Debug" << std::endl; // 디버깅용 출력
        userStrings.push_back(tmpString);
    }
    return userStrings;
}

std::string UserManager::getUserTitleString() const {
    return User().getMemberNameString();
}

User* UserManager::getUserByName(const std::string& name) {
    std::vector<User> users = m_repo->getAll();
    int id = -1;
    for(auto user : users) {
        if(user.name == name) {
            id = user.id;
            break;
        }
    }
    if(id <= 0) {
        return nullptr;
    }
    return m_repo->getById(id);
}