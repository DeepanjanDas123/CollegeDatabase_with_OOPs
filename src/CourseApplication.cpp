#include "CourseApplication.hpp"
#include <iostream>


CourseApplication::CourseApplication(int sID, const std::string& cID, int pri, int order)
    : studentID(sID), courseID(cID), priority(pri), applicationOrder(order) {}

int CourseApplication::getStudentID() const { return studentID; }
std::string CourseApplication::getCourseID() const { return courseID; }
int CourseApplication::getPriority() const { return priority; }
int CourseApplication::getApplicationOrder() const { return applicationOrder; }

void CourseApplication::display() const {
    std::cout << "Student ID: " << studentID
                << ", Course ID: " << courseID
                << ", Priority: " << priority
                << ", Application Order: " << applicationOrder << std::endl;
}