#ifndef COLLEGE_DATABASE_HPP
#define COLLEGE_DATABASE_HPP

#include <vector>
#include <string>
#include "Student.hpp"
#include "Course.hpp"
#include "Enrolment.hpp"
#include "CourseApplication.hpp"
#include "Faculty.hpp"
#include "UserManager.hpp"

class CollegeDatabase {
private:
    std::vector<Student*> students;
    std::vector<Course> courses;
    std::vector<Enrollment> enrollments;
    std::vector<Faculty> faculties;
    std::vector<CourseApplication> applications;
    int applicationCounter;
    UserManager userManager;

    std::vector<Student*>::iterator findStudent(int id);
    std::vector<Course>::iterator findCourse(const std::string& id);
    std::vector<Enrollment>::iterator findEnrollment(int studentID, const std::string& courseID);
    std::vector<CourseApplication>::iterator findApplication(int studentID, const std::string& courseID);
    std::vector<Faculty>::iterator findFaculty(int id);

    std::vector<Student*>::const_iterator findStudent(int id) const;
    std::vector<Course>::const_iterator findCourse(const std::string& id) const;
    std::vector<Faculty>::const_iterator findFaculty(int id) const;

    bool hasPermission(Role role, const std::string& action, int userID, const std::string& courseID = "") const;

public:
    CollegeDatabase();
    ~CollegeDatabase();

    User* getCurrentUser() const; // Added to access userManager.getCurrentUser()

    bool login(const std::string& username, const std::string& password);
    void logout();
    bool addUser(const std::string& username, int id, Role role, const std::string& password);

    void addStudent(const std::string& type, int id, const std::string& name, const std::string& email, double cgpa);
    void updateStudent(int id, const std::string& name, const std::string& email, double cgpa);
    void deleteStudent(int id);
    void displayStudents() const;
    void displayStudentInfo(int studentID) const;

    void addCourse(const std::string& id, const std::string& name, int credits, AllocationType alloc, int capacity);
    void updateCourse(const std::string& id, const std::string& name, int credits, AllocationType alloc, int capacity);
    void deleteCourse(const std::string& id);
    void displayCourses() const;

    void applyForCourse(int studentID, const std::string& courseID, int priority);
    void displayApplications() const;
    void allocateCourses();

    void enrollStudent(int studentID, const std::string& courseID);
    void updateGrade(int studentID, const std::string& courseID, const std::string& grade);
    void deleteEnrollment(int studentID, const std::string& courseID);
    void displayEnrollments() const;
    void displayStudentCourses(int studentID) const;

    void addFaculty(int id, const std::string& name, bool isPermanent);
    void assignCourseToFaculty(int facultyID, const std::string& courseID);
    void moveCourseToPast(int facultyID, const std::string& courseID);
    void applyForProject(int studentID, int facultyID);
    void displayFaculties() const;
};

#endif // COLLEGE_DATABASE_HPP