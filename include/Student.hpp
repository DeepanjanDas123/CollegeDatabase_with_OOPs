#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string> 

class Student {
    protected:
        int studentID;
        std::string name;
        std::string email;
        double cgpa;
        int totalCredits;
        int projectGuide;
        std::string assignedProject;
    
    public:
        Student(int id, const std::string& n, const std::string& e, double c, int tc = 0)
            : studentID(id), name(n), email(e), cgpa(c), totalCredits(tc) {}
    
        virtual int getStudentID() const { return studentID; }
        virtual std::string getName() const { return name; }
        virtual std::string getEmail() const { return email; }
        virtual double getCGPA() const { return cgpa; }
        virtual int getTotalCredits() const { return totalCredits; }
        std::string getAssignedProject() const { return assignedProject; }

        virtual void setName(const std::string& n) { name = n; }
        virtual void setEmail(const std::string& e) { email = e; }
        virtual void setCGPA(double c) { cgpa = c; }
        virtual void setTotalCredits(int tc) { totalCredits = tc; }
        void assignProject(std::string project) { assignedProject = project; }
    
        virtual void display() const = 0;
        virtual std::string getStudentType() const = 0;
        virtual void assignProjectGuide(int facultyID) = 0;
        virtual int getProjectGuide() const = 0;
        virtual ~Student() = default;
};

#endif