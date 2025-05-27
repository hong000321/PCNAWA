#ifndef USER_H
#define USER_H
#include <string>

typedef struct User{
    int id;
    std::string name;
    std::string email;
    std::string password;
    std::string date;
}User;


#endif // USER_H