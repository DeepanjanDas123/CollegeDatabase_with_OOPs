#include "Course.hpp"
#include <iostream>

Course::Course(const std::string& id, const std::string& n, int c, AllocationType alloc, int cap)
    : courseID(id), name(n), credits(c), allocationType(alloc), capacity(cap) {}

std::string Course::getCourseID() const { return courseID; }
std::string Course::getName() const { return name; }
int Course::getCredits() const { return credits; }
AllocationType Course::getAllocationType() const { return allocationType; }
int Course::getCapacity() const { return capacity; }

void Course::setName(const std::string& n) { name = n; }
void Course::setCredits(int c) { credits = c; }
void Course::setAllocationType(AllocationType alloc) { allocationType = alloc; }
void Course::setCapacity(int cap) { capacity = cap; }

void Course::display() const {
    std::string allocStr;
    switch (allocationType) {
        case AllocationType::CGPA: allocStr = "CGPA"; break;
        case AllocationType::FCFS: allocStr = "FCFS"; break;
        case AllocationType::Random: allocStr = "Random"; break;
        case AllocationType::RandomStratified: allocStr = "RandomStratified"; break;
    }
    std::cout << "Course ID: " << courseID
                << ", Name: " << name
                << ", Credits: " << credits
                << ", Allocation: " << allocStr
                << ", Capacity: " << capacity << std::endl;
}