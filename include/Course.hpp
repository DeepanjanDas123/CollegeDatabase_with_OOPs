#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>
#include "Utilities.hpp"

class Course {
    private:
        std::string courseID;
        std::string name;
        int credits;
        AllocationType allocationType;
        int capacity; // Maximum number of students
    
    public:
        Course(const std::string& id, const std::string& n, int c, AllocationType alloc, int cap);
    
        std::string getCourseID() const;
        std::string getName() const;
        int getCredits() const;
        AllocationType getAllocationType() const;
        int getCapacity() const;
    
        void setName(const std::string& n);
        void setCredits(int c);
        void setAllocationType(AllocationType alloc);
        void setCapacity(int cap);
    
        void display() const;
};

#endif