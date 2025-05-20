#include "Faculty.hpp"
#include <bits/stdc++.h>

Faculty::Faculty(int id, const std::string& n, bool perm)
    : facultyID(id), name(n), isPermanent(perm) {}

int Faculty::getFacultyID() const { return facultyID; }
std::string Faculty::getName() const { return name; }
bool Faculty::getIsPermanent() const { return isPermanent; }
const std::vector<std::string>& Faculty::getPastCourses() const { return pastCourses; }
const std::vector<std::string>& Faculty::getCurrentCourses() const { return currentCourses; }
const std::vector<int>& Faculty::getBTechAdvisees() const { return btechAdvisees; }
const std::vector<int>& Faculty::getDualDegreeAdvisees() const { return dualDegreeAdvisees; }
const std::vector<int>& Faculty::getMTechAdvisees() const { return mtechAdvisees; }
const std::vector<int>& Faculty::getPhDAdvisees() const { return phdAdvisees; }

void Faculty::addCurrentCourse(const std::string& courseID) {
    if (std::find(currentCourses.begin(), currentCourses.end(), courseID) == currentCourses.end()) {
        currentCourses.push_back(courseID);
    }
}

void Faculty::moveCourseToPast(const std::string& courseID) {
    auto it = std::find(currentCourses.begin(), currentCourses.end(), courseID);
    if (it != currentCourses.end()) {
        pastCourses.push_back(*it);
        currentCourses.erase(it);
    }
}

bool Faculty::canAcceptBTechAdvisee() const { return isPermanent && btechAdvisees.size() < 2; }
bool Faculty::canAcceptDualDegreeAdvisee() const { return isPermanent && dualDegreeAdvisees.size() < 2; }
bool Faculty::canAcceptPostgradAdvisee() const { return isPermanent && (mtechAdvisees.size() + phdAdvisees.size()) < 5; }

void Faculty::addBTechAdvisee(int studentID) { btechAdvisees.push_back(studentID); }
void Faculty::addDualDegreeAdvisee(int studentID) { dualDegreeAdvisees.push_back(studentID); }
void Faculty::addMTechAdvisee(int studentID) { mtechAdvisees.push_back(studentID); }
void Faculty::addPhDAdvisee(int studentID) { phdAdvisees.push_back(studentID); }

void Faculty::removeBTechAdvisee(int studentID) {
    btechAdvisees.erase(std::remove(btechAdvisees.begin(), btechAdvisees.end(), studentID), btechAdvisees.end());
}
void Faculty::removeDualDegreeAdvisee(int studentID) {
    dualDegreeAdvisees.erase(std::remove(dualDegreeAdvisees.begin(), dualDegreeAdvisees.end(), studentID), dualDegreeAdvisees.end());
}
void Faculty::removeMTechAdvisee(int studentID) {
    mtechAdvisees.erase(std::remove(mtechAdvisees.begin(), mtechAdvisees.end(), studentID), mtechAdvisees.end());
}
void Faculty::removePhDAdvisee(int studentID) {
    phdAdvisees.erase(std::remove(phdAdvisees.begin(), phdAdvisees.end(), studentID), phdAdvisees.end());
}

void Faculty::display() const {
    std::cout << "Faculty ID: " << facultyID
                << ", Name: " << name
                << ", Status: " << (isPermanent ? "Permanent" : "Adjunct")
                << "\nCurrent Courses: ";
    for (const auto& course : currentCourses) std::cout << course << " ";
    std::cout << "\nPast Courses: ";
    for (const auto& course : pastCourses) std::cout << course << " ";
    std::cout << "\nBTech Advisees: ";
    for (const auto& id : btechAdvisees) std::cout << id << " ";
    std::cout << "\nDualDegree Advisees: ";
    for (const auto& id : dualDegreeAdvisees) std::cout << id << " ";
    std::cout << "\nMTech Advisees: ";
    for (const auto& id : mtechAdvisees) std::cout << id << " ";
    std::cout << "\nPhD Advisees: ";
    for (const auto& id : phdAdvisees) std::cout << id << " ";
    std::cout << std::endl;
}