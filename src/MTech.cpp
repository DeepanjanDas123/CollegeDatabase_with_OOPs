#include "MTech.hpp"
#include <iostream>

MTech::MTech(int id, const std::string& n, const std::string& e, double c)
    : Student(id, n, e, c), RP_guide(-1) {}

void MTech::display() const {
    std::cout << "MTech Student ID: " << studentID
                << ", Name: " << name
                << ", Email: " << email
                << ", CGPA: " << cgpa
                << ", Research Project Guide: " << (RP_guide == -1 ? "None" : std::to_string(RP_guide))
                << std::endl;
}

std::string MTech::getStudentType() const { return "MTech"; }
void MTech::assignProjectGuide(int facultyID) { RP_guide = facultyID; }
int MTech::getProjectGuide() const { return RP_guide; }