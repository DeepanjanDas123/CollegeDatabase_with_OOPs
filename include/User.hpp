#ifndef USER_HPP
#define USER_HPP

#include <string>

enum class Role { Student, Faculty, Admin };

class User {
private:
    std::string username;
    int id; // Matches studentID or facultyID for Student/Faculty roles
    Role role;
    std::string password; // Plaintext for simplicity; use hashing in production

public:
    User(const std::string& uname, int id, Role r, const std::string& pwd);
    std::string getUsername() const;
    int getID() const;
    Role getRole() const;
    bool validatePassword(const std::string& pwd) const;
};

#endif