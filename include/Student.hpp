#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string> 

class Student {
    protected:
        int studentID;
        std::string name;
        std::string email;
        double cgpa;
    
    public:
        Student(int id, const std::string& n, const std::string& e, double c)
            : studentID(id), name(n), email(e), cgpa(c) {}
    
        virtual int getStudentID() const { return studentID; }
        virtual std::string getName() const { return name; }
        virtual std::string getEmail() const { return email; }
        virtual double getCGPA() const { return cgpa; }
    
        virtual void setName(const std::string& n) { name = n; }
        virtual void setEmail(const std::string& e) { email = e; }
        virtual void setCGPA(double c) { cgpa = c; }
    
        virtual void display() const = 0;
        virtual std::string getStudentType() const = 0;
        virtual void assignProjectGuide(int facultyID) = 0;
        virtual int getProjectGuide() const = 0;
        virtual ~Student() = default;
};

#endif