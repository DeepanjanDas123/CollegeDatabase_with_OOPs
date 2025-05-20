#include "User.hpp"

User::User(const std::string& uname, int id, Role r, const std::string& pwd)
    : username(uname), id(id), role(r), password(pwd) {}

std::string User::getUsername() const { return username; }
int User::getID() const { return id; }
Role User::getRole() const { return role; }
bool User::validatePassword(const std::string& pwd) const { return password == pwd; }