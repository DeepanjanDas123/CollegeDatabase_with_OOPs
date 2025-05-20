#ifndef MTECH_HPP
#define MTECH_HPP

#include "Student.hpp"

class MTech : public Student {
    private:
        int RP_guide;
    
    public:
        MTech(int id, const std::string& n, const std::string& e, double c);
    
        void display() const override;
    
        std::string getStudentType() const override;
        void assignProjectGuide(int facultyID) override;
        int getProjectGuide() const override;
};

#endif