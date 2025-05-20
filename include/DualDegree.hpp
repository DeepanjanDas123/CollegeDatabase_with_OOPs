#ifndef DUALDEGREE_HPP
#define DUALDEGREE_HPP

#include "Student.hpp"

class DualDegree : public Student {
    private:
        int DDP_guide;
    
    public:
        DualDegree(int id, const std::string& n, const std::string& e, double c);
    
        void display() const override;
    
        std::string getStudentType() const override;
        void assignProjectGuide(int facultyID) override;
        int getProjectGuide() const override;
};

#endif