#include "PhD.hpp"
#include <iostream>

PhD::PhD(int id, const std::string& n, const std::string& e, double c)
    : Student(id, n, e, c), RP_guide(-1) {}

void PhD::display() const {
    std::cout << "PhD Student ID: " << studentID
                << ", Name: " << name
                << ", Email: " << email
                << ", CGPA: " << cgpa
                << ", Total Credits: " << totalCredits
                << ", Research Project Guide: " << (RP_guide == -1 ? "None" : std::to_string(RP_guide))
                << std::endl;
}

std::string PhD::getStudentType() const { return "PhD"; }
void PhD::assignProjectGuide(int facultyID) { RP_guide = facultyID; }
int PhD::getProjectGuide() const { return RP_guide; }