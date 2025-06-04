#ifndef USERSEARCHSERVICE_H
#define USERSEARCHSERVICE_H

#include <string>
#include <vector>
#include "../models/User.h"

class UserSearchService {
public:
    UserSearchService();
    ~UserSearchService();

    // Search for users by name
    std::vector<User> searchUsersByName(const std::string& name);

    // Search for users by email
    std::vector<User> searchUsersByEmail(const std::string& email);

    // Search for users by role
    std::vector<User> searchUsersByRole(const std::string& role);

private:
    std::vector<User> users;
};

#endif // USERSEARCHSERVICE_H