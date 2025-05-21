#include "CollegeDatabase.hpp"
#include <iostream>

void studentMenu(CollegeDatabase& db, int studentID) {
    std::cout << "\nStudent Menu:\n";
    std::cout << "1. View My Info\n";
    std::cout << "2. View All Faculties\n";
    std::cout << "3. Apply for Course\n";
    std::cout << "4. View My Courses\n";
    std::cout << "5. Logout\n";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1:
            db.displayStudentInfo(studentID);
            break;
        case 2:
            db.displayFaculties();
            break;
        case 3: {
            std::string courseID;
            int priority;
            std::cout << "Enter Course ID: ";
            std::cin >> courseID;
            std::cout << "Enter Priority (lower number = higher priority): ";
            std::cin >> priority;
            db.applyForCourse(studentID, courseID, priority);
            break;
        }
        case 4:
            db.displayStudentCourses(studentID);
            break;
        case 5:
            db.logout();
            break;
        default:
            std::cout << "Invalid choice.\n";
    }
}

void facultyMenu(CollegeDatabase& db, int facultyID) {
    std::cout << "\nFaculty Menu:\n";
    std::cout << "1. View All Students\n";
    std::cout << "2. View All Courses\n";
    std::cout << "3. View All Enrollments\n";
    std::cout << "4. View All Applications\n";
    std::cout << "5. Assign Course to Self\n";
    std::cout << "6. Move Course to Past\n";
    std::cout << "7. Update Grade\n";
    std::cout << "8. Assign Project Advisee\n";
    std::cout << "9. View All Faculties\n";
    std::cout << "10. Logout\n";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1:
            db.displayStudents();
            break;
        case 2:
            db.displayCourses();
            break;
        case 3:
            db.displayEnrollments();
            break;
        case 4:
            db.displayApplications();
            break;
        case 5: {
            std::string courseID;
            std::cout << "Enter Course ID: ";
            std::cin >> courseID;
            db.assignCourseToFaculty(facultyID, courseID);
            break;
        }
        case 6: {
            std::string courseID;
            std::cout << "Enter Course ID: ";
            std::cin >> courseID;
            db.moveCourseToPast(facultyID, courseID);
            break;
        }
        case 7: {
            int studentID;
            std::string courseID, grade;
            std::cout << "Enter Student ID: ";
            std::cin >> studentID;
            std::cout << "Enter Course ID: ";
            std::cin >> courseID;
            std::cout << "Enter Grade (S, A, B, C, D, E, P, F): ";
            std::cin >> grade;
            db.updateGrade(studentID, courseID, grade);
            break;
        }
        case 8: {
            int studentID;
            std::cout << "Enter Student ID: ";
            std::cin >> studentID;
            db.applyForProject(studentID, facultyID);
            break;
        }
        case 9:
            db.displayFaculties();
            break;
        case 10:
            db.logout();
            break;
        default:
            std::cout << "Invalid choice.\n";
    }
}

void adminMenu(CollegeDatabase& db) {
    std::cout << "\nAdmin Menu:\n";
    std::cout << "1. Add User\n";
    std::cout << "2. Add Student\n";
    std::cout << "3. Update Student\n";
    std::cout << "4. Delete Student\n";
    std::cout << "5. View All Students\n";
    std::cout << "6. Add Course\n";
    std::cout << "7. Update Course\n";
    std::cout << "8. Delete Course\n";
    std::cout << "9. View All Courses\n";
    std::cout << "10. Allocate Courses\n";
    std::cout << "11. Enroll Student\n";
    std::cout << "12. Update Grade\n";
    std::cout << "13. Delete Enrollment\n";
    std::cout << "14. View All Enrollments\n";
    std::cout << "15. View All Applications\n";
    std::cout << "16. Add Faculty\n";
    std::cout << "17. Assign Course to Faculty\n";
    std::cout << "18. Assign Project Advisee\n";
    std::cout << "19. View All Faculties\n";
    std::cout << "20. Logout\n";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1: {
            std::string username, password, roleStr;
            int id;
            std::cout << "Enter Username: ";
            std::cin >> username;
            std::cout << "Enter ID: ";
            std::cin >> id;
            std::cout << "Enter Role (Student/Faculty/Admin): ";
            std::cin >> roleStr;
            std::cout << "Enter Password: ";
            std::cin >> password;
            Role role = (roleStr == "Student" ? Role::Student : roleStr == "Faculty" ? Role::Faculty : Role::Admin);
            db.addUser(username, id, role, password);
            break;
        }
        case 2: {
            std::string type, name, email;
            int id;
            double cgpa;
            std::cout << "Enter Student Type (BTech/DualDegree/MTech/PhD): ";
            std::cin >> type;
            std::cout << "Enter ID: ";
            std::cin >> id;
            std::cout << "Enter Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter Email: ";
            std::cin >> email;
            std::cout << "Enter CGPA: ";
            std::cin >> cgpa;
            db.addStudent(type, id, name, email, cgpa);
            break;
        }
        case 3: {
            int id;
            std::string name, email;
            double cgpa;
            std::cout << "Enter Student ID: ";
            std::cin >> id;
            std::cout << "Enter Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter Email: ";
            std::cin >> email;
            std::cout << "Enter CGPA: ";
            std::cin >> cgpa;
            db.updateStudent(id, name, email, cgpa);
            break;
        }
        case 4: {
            int id;
            std::cout << "Enter Student ID: ";
            std::cin >> id;
            db.deleteStudent(id);
            break;
        }
        case 5:
            db.displayStudents();
            break;
        case 6: {
            std::string id, name, allocStr;
            int credits, capacity;
            std::cout << "Enter Course ID: ";
            std::cin >> id;
            std::cout << "Enter Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter Credits: ";
            std::cin >> credits;
            std::cout << "Enter Allocation Type (CGPA/FCFS/Random/RandomStratified): ";
            std::cin >> allocStr;
            std::cout << "Enter Capacity: ";
            std::cin >> capacity;
            AllocationType alloc = (allocStr == "CGPA" ? AllocationType::CGPA :
                                   allocStr == "FCFS" ? AllocationType::FCFS :
                                   allocStr == "Random" ? AllocationType::Random : AllocationType::RandomStratified);
            db.addCourse(id, name, credits, alloc, capacity);
            break;
        }
        case 7: {
            std::string id, name, allocStr;
            int credits, capacity;
            std::cout << "Enter Course ID: ";
            std::cin >> id;
            std::cout << "Enter Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter Credits: ";
            std::cin >> credits;
            std::cout << "Enter Allocation Type (CGPA/FCFS/Random/RandomStratified): ";
            std::cin >> allocStr;
            std::cout << "Enter Capacity: ";
            std::cin >> capacity;
            AllocationType alloc = (allocStr == "CGPA" ? AllocationType::CGPA :
                                   allocStr == "FCFS" ? AllocationType::FCFS :
                                   allocStr == "Random" ? AllocationType::Random : AllocationType::RandomStratified);
            db.updateCourse(id, name, credits, alloc, capacity);
            break;
        }
        case 8: {
            std::string id;
            std::cout << "Enter Course ID: ";
            std::cin >> id;
            db.deleteCourse(id);
            break;
        }
        case 9:
            db.displayCourses();
            break;
        case 10:
            db.allocateCourses();
            break;
        case 11: {
            int studentID;
            std::string courseID;
            std::cout << "Enter Student ID: ";
            std::cin >> studentID;
            std::cout << "Enter Course ID: ";
            std::cin >> courseID;
            db.enrollStudent(studentID, courseID);
            break;
        }
        case 12: {
            int studentID;
            std::string courseID, grade;
            std::cout << "Enter Student ID: ";
            std::cin >> studentID;
            std::cout << "Enter Course ID: ";
            std::cin >> courseID;
            std::cout << "Enter Grade (S, A, B, C, D, E, P, F): ";
            std::cin >> grade;
            db.updateGrade(studentID, courseID, grade);
            break;
        }
        case 13: {
            int studentID;
            std::string courseID;
            std::cout << "Enter Student ID: ";
            std::cin >> studentID;
            std::cout << "Enter Course ID: ";
            std::cin >> courseID;
            db.deleteEnrollment(studentID, courseID);
            break;
        }
        case 14:
            db.displayEnrollments();
            break;
        case 15:
            db.displayApplications();
            break;
        case 16: {
            int id;
            std::string name;
            bool isPermanent;
            std::cout << "Enter Faculty ID: ";
            std::cin >> id;
            std::cout << "Enter Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Is Permanent? (1 for yes, 0 for no): ";
            std::cin >> isPermanent;
            db.addFaculty(id, name, isPermanent);
            break;
        }
        case 17: {
            int facultyID;
            std::string courseID;
            std::cout << "Enter Faculty ID: ";
            std::cin >> facultyID;
            std::cout << "Enter Course ID: ";
            std::cin >> courseID;
            db.assignCourseToFaculty(facultyID, courseID);
            break;
        }
        case 18: {
            int studentID, facultyID;
            std::cout << "Enter Student ID: ";
            std::cin >> studentID;
            std::cout << "Enter Faculty ID: ";
            std::cin >> facultyID;
            db.applyForProject(studentID, facultyID);
            break;
        }
        case 19:
            db.displayFaculties();
            break;
        case 20:
            db.logout();
            break;
        default:
            std::cout << "Invalid choice.\n";
    }
}

int main() {
    CollegeDatabase db;

    // Add users
    db.addUser("admin", 0, Role::Admin, "admin123");
    db.addUser("john", 1, Role::Student, "john123");
    db.addUser("jane", 2, Role::Student, "jane123");
    db.addUser("alice", 3, Role::Student, "alice123");
    db.addUser("bob", 4, Role::Student, "bob123");
    db.addUser("smith", 101, Role::Faculty, "smith123");
    db.addUser("jones", 102, Role::Faculty, "jones123");

    // Add initial data
    db.login("admin", "admin123");
    db.addFaculty(101, "Dr. Smith", true);
    db.addFaculty(102, "Dr. Jones", false);
    db.addStudent("BTech", 1, "John Doe", "john@university.com", 8.5);
    db.addStudent("DualDegree", 2, "Jane Smith", "jane@university.com", 9.0);
    db.addStudent("MTech", 3, "Alice Brown", "alice@university.com", 8.8);
    db.addStudent("PhD", 4, "Bob Wilson", "bob@university.com", 9.2);
    db.addCourse("CS101", "Introduction to Programming", 3, AllocationType::CGPA, 1);
    db.addCourse("MATH201", "Calculus I", 4, AllocationType::FCFS, 1);
    db.addCourse("PHYS301", "Physics I", 3, AllocationType::Random, 2);
    db.addCourse("CHEM401", "Chemistry I", 3, AllocationType::RandomStratified, 2);

    db.enrollStudent(1, "CS101");
    db.enrollStudent(2, "CS101");
    db.enrollStudent(3, "MATH201");
    db.enrollStudent(4, "PHYS301");
    db.assignCourseToFaculty(101, "CS101");
    db.assignCourseToFaculty(101, "MATH201");
    db.logout();

    while (true) {
        std::cout << "\nLogin Menu:\n";
        std::cout << "1. Login\n";
        std::cout << "2. Exit\n";
        int choice;
        std::cin >> choice;
        if (choice == 2) break;

        if (choice == 1) {
            std::string username, password;
            std::cout << "Enter Username: ";
            std::cin >> username;
            std::cout << "Enter Password: ";
            std::cin >> password;
            if (db.login(username, password)) {
                User* user = db.getCurrentUser();
                while (user) {
                    if (user->getRole() == Role::Student) {
                        studentMenu(db, user->getID());
                    } else if (user->getRole() == Role::Faculty) {
                        facultyMenu(db, user->getID());
                    } else if (user->getRole() == Role::Admin) {
                        adminMenu(db);
                    }
                    user = db.getCurrentUser();
                }
            }
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}