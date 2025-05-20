#include "Enrolment.hpp"
#include <iostream>


Enrollment::Enrollment(int sID, const std::string& cID, const std::string& g)
    : studentID(sID), courseID(cID), grade(g) {}

int Enrollment::getStudentID() const { return studentID; }
std::string Enrollment::getCourseID() const { return courseID; }
std::string Enrollment::getGrade() const { return grade; }

void Enrollment::setGrade(const std::string& g) { grade = g; }

void Enrollment::display() const {
    std::cout << "Student ID: " << studentID
                << ", Course ID: " << courseID
                << ", Grade: " << grade << std::endl;
}