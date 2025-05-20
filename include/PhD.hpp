#ifndef PHD_HPP
#define PHD_HPP

#include "Student.hpp"

class PhD : public Student {
    private:
        int RP_guide;
    
    public:
        PhD(int id, const std::string& n, const std::string& e, double c);
    
        void display() const override;
    
        std::string getStudentType() const override;
        void assignProjectGuide(int facultyID) override;
        int getProjectGuide() const override;
};

#endif