#ifndef BTECH_HPP
#define BTECH_HPP

#include "Student.hpp"

class BTech : public Student {
    private:
        int BTP_guide;
    
    public:
        BTech(int id, const std::string& n, const std::string& e, double c);
    
        void display() const override;
    
        std::string getStudentType() const override;
        void assignProjectGuide(int facultyID) override;
        int getProjectGuide() const override;
};

#endif