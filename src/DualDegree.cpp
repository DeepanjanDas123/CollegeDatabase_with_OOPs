#include "DualDegree.hpp"
#include <iostream>

DualDegree::DualDegree(int id, const std::string& n, const std::string& e, double c)
    : Student(id, n, e, c), DDP_guide(-1) {}

void DualDegree::display() const {
    std::cout << "DualDegree Student ID: " << studentID
                << ", Name: " << name
                << ", Email: " << email
                << ", CGPA: " << cgpa
                << ", DDP Guide: " << (DDP_guide == -1 ? "None" : std::to_string(DDP_guide))
                << std::endl;
}

std::string DualDegree::getStudentType() const { return "DualDegree"; }

void DualDegree::assignProjectGuide(int facultyID) { DDP_guide = facultyID; }
int DualDegree::getProjectGuide() const { return DDP_guide; }