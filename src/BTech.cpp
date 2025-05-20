#include "BTech.hpp"
#include <iostream>

BTech::BTech(int id, const std::string&n, const std::string& e, double c)
    : Student(id, n, e, c), BTP_guide(-1) {}

void BTech::display() const{
    std::cout << "BTech Student ID: " << studentID
                  << ", Name: " << name
                  << ", Email: " << email
                  << ", CGPA: " << cgpa
                  << ", BTP Guide: " << (BTP_guide == -1 ? "None" : std::to_string(BTP_guide))
                  << std::endl;
}

std::string BTech::getStudentType() const { return "BTech"; }

void BTech::assignProjectGuide(int facultyID) { BTP_guide = facultyID; }
int BTech::getProjectGuide() const { return BTP_guide; }