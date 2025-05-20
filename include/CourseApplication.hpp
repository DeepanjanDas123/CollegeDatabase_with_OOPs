#ifndef COURSEAPPLICATION_HPP
#define COURSEAPPLICATION_HPP

#include <string>

class CourseApplication {
    private:
        int studentID;
        std::string courseID;
        int priority; // Lower number means higher priority (1 is highest)
        int applicationOrder; // For FCFS
    
    public:
        CourseApplication(int sID, const std::string& cID, int pri, int order);
    
        int getStudentID() const;
        std::string getCourseID() const;
        int getPriority() const;
        int getApplicationOrder() const;
    
        void display() const;
};

#endif