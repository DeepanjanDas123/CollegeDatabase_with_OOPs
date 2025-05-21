#include "ProjectApplication.hpp"
#include <iostream>

ProjectApplication::ProjectApplication(int studentID, const std::string& projectID, int order)
    : studentID(studentID), projectID(projectID), applicationOrder(order) {}

int ProjectApplication::getStudentID() const { return studentID; }
std::string ProjectApplication::getProjectID() const { return projectID; }
int ProjectApplication::getApplicationOrder() const { return applicationOrder; }

void ProjectApplication::display() const {
    std::cout << "Student ID: " << studentID
              << ", Project ID: " << projectID
              << ", Application Order: " << applicationOrder << "\n";
}