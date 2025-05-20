#include "UserManager.hpp"
#include <iostream>

UserManager::UserManager() : currentUser(nullptr) {}

bool UserManager::addUser(const std::string& username, int id, Role role, const std::string& password) {
    if (users.find(username) != users.end()) {
        std::cout << "Error: Username already exists.\n";
        return false;
    }
    users.emplace(username, User(username, id, role, password));
    std::cout << "User added successfully.\n";
    return true;
}

bool UserManager::login(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if (it != users.end() && it->second.validatePassword(password)) {
        currentUser = &it->second;
        std::cout << "Login successful for " << username << " as " << (currentUser->getRole() == Role::Student ? "Student" : currentUser->getRole() == Role::Faculty ? "Faculty" : "Admin") << ".\n";
        return true;
    }
    std::cout << "Error: Invalid username or password.\n";
    return false;
}

void UserManager::logout() {
    currentUser = nullptr;
    std::cout << "Logged out successfully.\n";
}

User* UserManager::getCurrentUser() const { return currentUser; }