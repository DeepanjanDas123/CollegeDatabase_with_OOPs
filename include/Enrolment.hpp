#ifndef ENROLMENT_HPP
#define ENROLMENT_HPP

#include <string>

class Enrollment {
    private:
        int studentID;
        std::string courseID;
        std::string grade;
    
    public:
        Enrollment(int sID, const std::string& cID, const std::string& g = "N/A");
    
        int getStudentID() const;
        std::string getCourseID() const;
        std::string getGrade() const;
    
        void setGrade(const std::string& g);
    
        void display() const;
};

#endif