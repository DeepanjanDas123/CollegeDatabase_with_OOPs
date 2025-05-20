#include "CollegeDatabase.hpp"
#include <iostream>

int main() {
    CollegeDatabase db;

    db.addFaculty(101, "Dr. Smith", true);
    db.addFaculty(102, "Dr. Jones", false);

    db.addStudent("BTech", 1, "John Doe", "john@university.com", 8.5);
    db.addStudent("DualDegree", 2, "Jane Smith", "jane@university.com", 9.0);
    db.addStudent("MTech", 3, "Alice Brown", "alice@university.com", 8.8);
    db.addStudent("PhD", 4, "Bob Wilson", "bob@university.com", 9.2);

    db.addCourse("CS101", "Introduction to Programming", 3, AllocationType::CGPA, 2);
    db.addCourse("MATH201", "Calculus I", 4, AllocationType::FCFS, 2);
    db.addCourse("PHYS301", "Physics I", 3, AllocationType::Random, 2);
    db.addCourse("CHEM401", "Chemistry I", 3, AllocationType::RandomStratified, 2);

    db.applyForCourse(1, "CS101", 1);
    db.applyForCourse(1, "MATH201", 2);
    db.applyForCourse(1, "PHYS301", 3);
    db.applyForCourse(2, "CS101", 2);
    db.applyForCourse(2, "MATH201", 1);
    db.applyForCourse(2, "CHEM401", 3);
    db.applyForCourse(3, "CS101", 1);
    db.applyForCourse(3, "PHYS301", 2);
    db.applyForCourse(4, "MATH201", 1);
    db.applyForCourse(4, "CHEM401", 2);

    db.assignCourseToFaculty(101, "CS101");
    db.assignCourseToFaculty(101, "MATH201");
    db.assignCourseToFaculty(102, "PHYS301");
    db.assignCourseToFaculty(102, "CHEM401");

    db.allocateCourses();

    db.applyForProject(1, 101);
    db.applyForProject(2, 101);
    db.applyForProject(3, 101);
    db.applyForProject(4, 101);

    std::cout << "\nAll Students:\n";
    db.displayStudents();
    std::cout << "\nAll Courses:\n";
    db.displayCourses();
    std::cout << "\nAll Applications:\n";
    db.displayApplications();
    std::cout << "\nAll Enrollments:\n";
    db.displayEnrollments();
    std::cout << "\nAll Faculties:\n";
    db.displayFaculties();
    std::cout << "\nStudent Courses for ID 1:\n";
    db.displayStudentCourses(1);

    return 0;
}