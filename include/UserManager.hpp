#ifndef USER_MANAGER_HPP
#define USER_MANAGER_HPP

#include "User.hpp"
#include <map>
#include <string>

class UserManager {
private:
    std::map<std::string, User> users;
    User* currentUser;

public:
    UserManager();
    bool addUser(const std::string& username, int id, Role role, const std::string& password);
    bool login(const std::string& username, const std::string& password);
    void logout();
    User* getCurrentUser() const;
};

#endif