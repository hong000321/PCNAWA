#ifndef USERMANAGER_H
#define USERMANAGER_H
#include "repository/CsvUserRepo.h"
#include "repository/IRepository.h"
#include "struct/User.h"
#include <memory>

class UserManager{
private:
    std::unique_ptr<IRepository<User>> userRepo;

public:
    explicit UserManager(std::unique_ptr<IRepository<User>> repo)
        : userRepo(std::move(repo)) {};
    ~UserManager();

    bool registerUser(const User& user){
        return userRepo->insert(user);
    }

    std::vector<User> getAllUsers() const {
        return userRepo->getAll();
    }
};
#endif // USERMANAGER_H