#include "CollegeDatabase.hpp"
#include "BTech.hpp"
#include "DualDegree.hpp"
#include "MTech.hpp"
#include "PhD.hpp"
#include <algorithm>
#include <random>
#include <map>
#include <queue>
#include <iostream>

CollegeDatabase::CollegeDatabase() : applicationCounter(0), projectApplicationCounter(0) {}

CollegeDatabase::~CollegeDatabase() {
    for (Student* student : students) delete student;
}

User* CollegeDatabase::getCurrentUser() const {
    return userManager.getCurrentUser();
}

bool CollegeDatabase::hasPermission(Role role, const std::string& action, int userID, const std::string& courseID, const std::string& projectID) const {
    if (!userManager.getCurrentUser()) {
        std::cout << "Error: No user logged in.\n";
        return false;
    }

    if (role == Role::Student) {
        if (action == "displayStudentInfo" && userID == userManager.getCurrentUser()->getID()) return true;
        if (action == "displayFaculties" || action == "displayProjects") return true;
        if (action == "applyForCourse" && userID == userManager.getCurrentUser()->getID()) return true;
        if (action == "applyForProject" && userID == userManager.getCurrentUser()->getID()) return true;
        if (action == "displayStudentCourses" && userID == userManager.getCurrentUser()->getID()) return true;
        return false;
    } else if (role == Role::Faculty) {
        if (action == "displayStudents" || action == "displayFaculties" || action == "displayCourses" ||
            action == "displayEnrollments" || action == "displayApplications" || action == "displayProjects" ||
            action == "displayProjectApplications") return true;
        if (action == "assignCourseToFaculty" && userID == userManager.getCurrentUser()->getID()) return true;
        if (action == "moveCourseToPast" && userID == userManager.getCurrentUser()->getID()) return true;
        if (action == "applyForProject" && userID == userManager.getCurrentUser()->getID()) return true;
        if (action == "addProject" && userID == userManager.getCurrentUser()->getID()) return true;
        if (action == "updateGrade") {
            auto facultyIt = findFaculty(userManager.getCurrentUser()->getID());
            if (facultyIt != faculties.end()) {
                auto it = std::find(facultyIt->getCurrentCourses().begin(), facultyIt->getCurrentCourses().end(), courseID);
                return it != facultyIt->getCurrentCourses().end();
            }
            return false;
        }
        return false;
    } else if (role == Role::Admin) {
        return true; // Admins have access to all actions
    }
    return false;
}

bool CollegeDatabase::login(const std::string& username, const std::string& password) {
    return userManager.login(username, password);
}

void CollegeDatabase::logout() {
    userManager.logout();
}

bool CollegeDatabase::addUser(const std::string& username, int id, Role role, const std::string& password) {
    return userManager.addUser(username, id, role, password);
}

void CollegeDatabase::addStudent(const std::string& type, int id, const std::string& name, const std::string& email, double cgpa) {
    if (!hasPermission(Role::Admin, "addStudent", id)) return;
    if (findStudent(id) == students.end()) {
        if (type == "BTech") students.push_back(new BTech(id, name, email, cgpa));
        else if (type == "DualDegree") students.push_back(new DualDegree(id, name, email, cgpa));
        else if (type == "MTech") students.push_back(new MTech(id, name, email, cgpa));
        else if (type == "PhD") students.push_back(new PhD(id, name, email, cgpa));
        else { std::cout << "Error: Invalid student type.\n"; return; }
        std::cout << "Student added successfully.\n";
    } else {
        std::cout << "Error: Student ID already exists.\n";
    }
}

void CollegeDatabase::updateStudent(int id, const std::string& name, const std::string& email, double cgpa) {
    if (!hasPermission(Role::Admin, "updateStudent", id)) return;
    auto it = findStudent(id);
    if (it != students.end()) {
        (*it)->setName(name);
        (*it)->setEmail(email);
        (*it)->setCGPA(cgpa);
        std::cout << "Student updated successfully.\n";
    } else {
        std::cout << "Error: Student not found.\n";
    }
}

void CollegeDatabase::deleteStudent(int id) {
    if (!hasPermission(Role::Admin, "deleteStudent", id)) return;
    auto it = findStudent(id);
    if (it != students.end()) {
        enrollments.erase(
            std::remove_if(enrollments.begin(), enrollments.end(),
                [id](const Enrollment& e) { return e.getStudentID() == id; }),
            enrollments.end());
        applications.erase(
            std::remove_if(applications.begin(), applications.end(),
                [id](const CourseApplication& a) { return a.getStudentID() == id; }),
            applications.end());
        projectApplications.erase(
            std::remove_if(projectApplications.begin(), projectApplications.end(),
                [id](const ProjectApplication& a) { return a.getStudentID() == id; }),
            projectApplications.end());
        for (auto& faculty : faculties) {
            faculty.removeBTechAdvisee(id);
            faculty.removeDualDegreeAdvisee(id);
            faculty.removeMTechAdvisee(id);
            faculty.removePhDAdvisee(id);
        }
        delete *it;
        students.erase(it);
        std::cout << "Student deleted successfully.\n";
    } else {
        std::cout << "Error: Student not found.\n";
    }
}

void CollegeDatabase::displayStudents() const {
    if (!hasPermission(Role::Faculty, "displayStudents", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    if (students.empty()) { std::cout << "No students in the database.\n"; return; }
    for (const auto* student : students) student->display();
}

void CollegeDatabase::displayStudentInfo(int studentID) const {
    if (!hasPermission(Role::Student, "displayStudentInfo", studentID)) return;
    auto it = findStudent(studentID);
    if (it != students.end()) {
        (*it)->display();
    } else {
        std::cout << "Error: Student not found.\n";
    }
}

void CollegeDatabase::addCourse(const std::string& id, const std::string& name, int credits, AllocationType alloc, int capacity) {
    if (!hasPermission(Role::Admin, "addCourse", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    if (findCourse(id) == courses.end()) {
        courses.emplace_back(id, name, credits, alloc, capacity);
        std::cout << "Course added successfully.\n";
    } else {
        std::cout << "Error: Course ID already exists.\n";
    }
}

void CollegeDatabase::updateCourse(const std::string& id, const std::string& name, int credits, AllocationType alloc, int capacity) {
    if (!hasPermission(Role::Admin, "updateCourse", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    auto it = findCourse(id);
    if (it != courses.end()) {
        it->setName(name);
        it->setCredits(credits);
        it->setAllocationType(alloc);
        it->setCapacity(capacity);
        std::cout << "Course updated successfully.\n";
    } else {
        std::cout << "Error: Course not found.\n";
    }
}

void CollegeDatabase::deleteCourse(const std::string& id) {
    if (!hasPermission(Role::Admin, "deleteCourse", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    auto it = findCourse(id);
    if (it != courses.end()) {
        for (auto& faculty : faculties) faculty.moveCourseToPast(id);
        enrollments.erase(
            std::remove_if(enrollments.begin(), enrollments.end(),
                [id](const Enrollment& e) { return e.getCourseID() == id; }),
            enrollments.end());
        applications.erase(
            std::remove_if(applications.begin(), applications.end(),
                [id](const CourseApplication& a) { return a.getCourseID() == id; }),
            applications.end());
        courses.erase(it);
        std::cout << "Course deleted successfully.\n";
    } else {
        std::cout << "Error: Course not found.\n";
    }
}

void CollegeDatabase::displayCourses() const {
    if (!hasPermission(Role::Faculty, "displayCourses", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    if (courses.empty()) { std::cout << "No courses in the database.\n"; return; }
    for (const auto& course : courses) course.display();
}

void CollegeDatabase::applyForCourse(int studentID, const std::string& courseID, int priority) {
    if (!hasPermission(Role::Student, "applyForCourse", studentID)) return;
    if (findStudent(studentID) == students.end()) {
        std::cout << "Error: Student not found.\n";
        return;
    }
    if (findCourse(courseID) == courses.end()) {
        std::cout << "Error: Course not found.\n";
        return;
    }
    if (findApplication(studentID, courseID) != applications.end()) {
        std::cout << "Error: Student already applied to this course.\n";
        return;
    }
    applications.emplace_back(studentID, courseID, priority, applicationCounter++);
    std::cout << "Course application submitted successfully.\n";
}

void CollegeDatabase::displayApplications() const {
    if (!hasPermission(Role::Faculty, "displayApplications", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    if (applications.empty()) { std::cout << "No applications in the database.\n"; return; }
    for (const auto& app : applications) app.display();
}

void CollegeDatabase::allocateCourses() {
    if (!hasPermission(Role::Admin, "allocateCourses", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    enrollments.clear();
    std::map<std::string, std::vector<int>> coursePreferences;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (const auto& course : courses) {
        std::vector<CourseApplication> courseApps;
        for (const auto& app : applications) {
            if (app.getCourseID() == course.getCourseID()) {
                courseApps.push_back(app);
            }
        }

        std::vector<int> studentPrefs;
        if (course.getAllocationType() == AllocationType::CGPA) {
            std::sort(courseApps.begin(), courseApps.end(),
                [&](const CourseApplication& a, const CourseApplication& b) {
                    auto s1 = findStudent(a.getStudentID());
                    auto s2 = findStudent(b.getStudentID());
                    return (*s1)->getCGPA() > (*s2)->getCGPA();
                });
            for (const auto& app : courseApps) studentPrefs.push_back(app.getStudentID());
        } else if (course.getAllocationType() == AllocationType::FCFS) {
            std::sort(courseApps.begin(), courseApps.end(),
                [](const CourseApplication& a, const CourseApplication& b) {
                    return a.getApplicationOrder() < b.getApplicationOrder();
                });
            for (const auto& app : courseApps) studentPrefs.push_back(app.getStudentID());
        } else if (course.getAllocationType() == AllocationType::Random) {
            for (const auto& app : courseApps) studentPrefs.push_back(app.getStudentID());
            std::shuffle(studentPrefs.begin(), studentPrefs.end(), gen);
        } else if (course.getAllocationType() == AllocationType::RandomStratified) {
            std::map<std::string, std::vector<CourseApplication>> stratified;
            for (const auto& app : courseApps) {
                auto s = findStudent(app.getStudentID());
                stratified[(*s)->getStudentType()].push_back(app);
            }
            for (auto& [type, apps] : stratified) {
                std::vector<int> typePrefs;
                for (const auto& app : apps) typePrefs.push_back(app.getStudentID());
                std::shuffle(typePrefs.begin(), typePrefs.end(), gen);
                studentPrefs.insert(studentPrefs.end(), typePrefs.begin(), typePrefs.end());
            }
        }
        coursePreferences[course.getCourseID()] = studentPrefs;
    }

    std::map<int, std::vector<std::string>> studentPreferences;
    for (const auto& student : students) {
        std::vector<CourseApplication> studentApps;
        for (const auto& app : applications) {
            if (app.getStudentID() == student->getStudentID()) {
                studentApps.push_back(app);
            }
        }
        std::sort(studentApps.begin(), studentApps.end(),
            [](const CourseApplication& a, const CourseApplication& b) {
                return a.getPriority() < b.getPriority();
            });
        std::vector<std::string> coursePrefs;
        for (const auto& app : studentApps) {
            coursePrefs.push_back(app.getCourseID());
        }
        studentPreferences[student->getStudentID()] = coursePrefs;
    }

    std::map<int, std::string> studentToCourse;
    std::map<std::string, std::vector<int>> courseToStudents;
    std::map<int, size_t> studentNextProposal;
    std::queue<int> freeStudents;

    for (const auto& student : students) {
        if (!studentPreferences[student->getStudentID()].empty()) {
            freeStudents.push(student->getStudentID());
            studentNextProposal[student->getStudentID()] = 0;
        }
    }

    while (!freeStudents.empty()) {
        int s = freeStudents.front();
        freeStudents.pop();
        auto& prefList = studentPreferences[s];
        size_t& next = studentNextProposal[s];

        if (next >= prefList.size()) continue;

        std::string c = prefList[next];
        next++;

        auto courseIt = findCourse(c);
        int capacity = courseIt->getCapacity();
        auto& coursePrefs = coursePreferences[c];
        auto& currentStudents = courseToStudents[c];

        if (static_cast<int>(currentStudents.size()) < capacity) {
            studentToCourse[s] = c;
            currentStudents.push_back(s);
        } else {
            int lowestRank = -1;
            int lowestRankStudent = -1;
            for (int currentS : currentStudents) {
                auto it = std::find(coursePrefs.begin(), coursePrefs.end(), currentS);
                int rank = (it != coursePrefs.end()) ? (it - coursePrefs.begin()) : coursePrefs.size();
                if (lowestRank == -1 || rank > lowestRank) {
                    lowestRank = rank;
                    lowestRankStudent = currentS;
                }
            }
            auto sIt = std::find(coursePrefs.begin(), coursePrefs.end(), s);
            int sRank = (sIt != coursePrefs.end()) ? (sIt - coursePrefs.begin()) : coursePrefs.size();
            if (sRank < lowestRank) {
                studentToCourse.erase(lowestRankStudent);
                currentStudents.erase(
                    std::find(currentStudents.begin(), currentStudents.end(), lowestRankStudent));
                studentToCourse[s] = c;
                currentStudents.push_back(s);
                freeStudents.push(lowestRankStudent);
            } else {
                freeStudents.push(s);
            }
        }
    }

    for (const auto& [s, c] : studentToCourse) {
        enrollments.emplace_back(s, c);
    }

    std::cout << "Courses allocated successfully.\n";
}

void CollegeDatabase::enrollStudent(int studentID, const std::string& courseID) {
    if (!hasPermission(Role::Admin, "enrollStudent", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    if (findStudent(studentID) == students.end()) {
        std::cout << "Error: Student not found.\n";
        return;
    }
    if (findCourse(courseID) == courses.end()) {
        std::cout << "Error: Course not found.\n";
        return;
    }
    if (findEnrollment(studentID, courseID) == enrollments.end()) {
        enrollments.emplace_back(studentID, courseID);
        std::cout << "Student enrolled successfully.\n";
    } else {
        std::cout << "Error: Student already enrolled in this course.\n";
    }
}

void CollegeDatabase::updateGrade(int studentID, const std::string& courseID, const std::string& grade) {
    User* currentUser = userManager.getCurrentUser();
    if (currentUser->getRole() != Role::Admin && !hasPermission(Role::Faculty, "updateGrade", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1, courseID)) return;
    auto enrollmentIt = findEnrollment(studentID, courseID);
    if (enrollmentIt == enrollments.end()) {
        std::cout << "Error: Enrollment not found.\n";
        return;
    }
    auto studentIt = findStudent(studentID);
    auto courseIt = findCourse(courseID);
    if (studentIt == students.end() || courseIt == courses.end()) {
        std::cout << "Error: Student or course not found.\n";
        return;
    }

    // Convert grade to numerical value
    std::map<std::string, int> gradeMap = {
        {"S", 10}, {"A", 9}, {"B", 8}, {"C", 7},
        {"D", 6}, {"E", 5}, {"P", 4}, {"F", 0}
    };
    auto gradeIt = gradeMap.find(grade);
    if (gradeIt == gradeMap.end()) {
        std::cout << "Error: Invalid grade.\n";
        return;
    }
    int gradeValue = gradeIt->second;
    int courseCredits = courseIt->getCredits();

    // Update CGPA and totalCredits
    Student* student = *studentIt;
    double currentCGPA = student->getCGPA();
    int currentTotalCredits = student->getTotalCredits();

    // Check if this is a new grade (no previous grade set)
    bool isNewGrade = enrollmentIt->getGrade().empty() || enrollmentIt->getGrade() == "N/A";
    if (isNewGrade) {
        // Calculate new CGPA
        if (currentTotalCredits >= 0) {
            double temp = currentTotalCredits * currentCGPA;
            temp += courseCredits * gradeValue;
            currentTotalCredits += courseCredits;
            double newCGPA = temp / currentTotalCredits;
            student->setCGPA(newCGPA);
            student->setTotalCredits(currentTotalCredits);
        }
    }
    else{
        int past_grade_value = gradeMap[enrollmentIt->getGrade()];
        double temp = currentTotalCredits * currentCGPA;
        temp -= courseCredits * past_grade_value;
        temp += courseCredits * gradeValue;
        double newCGPA = temp / currentTotalCredits;
        student->setCGPA(newCGPA);
    }

    // Update the enrollment grade
    enrollmentIt->setGrade(grade);
    std::cout << "Grade updated successfully. New CGPA: " << student->getCGPA() << ", Total Credits: " << student->getTotalCredits() << "\n";
}

void CollegeDatabase::deleteEnrollment(int studentID, const std::string& courseID) {
    if (!hasPermission(Role::Admin, "deleteEnrollment", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    auto it = findEnrollment(studentID, courseID);
    if (it != enrollments.end()) {
        enrollments.erase(it);
        std::cout << "Enrollment deleted successfully.\n";
    } else {
        std::cout << "Error: Enrollment not found.\n";
    }
}

void CollegeDatabase::displayEnrollments() const {
    if (!hasPermission(Role::Faculty, "displayEnrollments", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    if (enrollments.empty()) { std::cout << "No enrollments in the database.\n"; return; }
    for (const auto& enrollment : enrollments) enrollment.display();
}

void CollegeDatabase::displayStudentCourses(int studentID) const {
    if (!hasPermission(Role::Student, "displayStudentCourses", studentID)) return;
    auto studentIt = findStudent(studentID);
    if (studentIt == students.end()) {
        std::cout << "Error: Student not found.\n";
        return;
    }
    std::cout << "Courses for " << (*studentIt)->getName() << " (ID: " << studentID << "):\n";
    bool hasCourses = false;
    for (const auto& enrollment : enrollments) {
        if (enrollment.getStudentID() == studentID) {
            auto courseIt = findCourse(enrollment.getCourseID());
            if (courseIt != courses.end()) {
                std::cout << "Course: " << courseIt->getName()
                          << " (ID: " << courseIt->getCourseID()
                          << "), Credits: " << courseIt->getCredits()
                          << ", Grade: " << enrollment.getGrade() << std::endl;
                hasCourses = true;
            }
        }
    }
    if (!hasCourses) std::cout << "No courses enrolled.\n";
}

void CollegeDatabase::addFaculty(int id, const std::string& name, bool isPermanent) {
    if (!hasPermission(Role::Admin, "addFaculty", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    if (findFaculty(id) == faculties.end()) {
        faculties.emplace_back(id, name, isPermanent);
        std::cout << "Faculty added successfully.\n";
    } else {
        std::cout << "Error: Faculty ID already exists.\n";
    }
}

void CollegeDatabase::assignCourseToFaculty(int facultyID, const std::string& courseID) {
    User* currentUser = userManager.getCurrentUser();
    if (currentUser->getRole() != Role::Admin && !hasPermission(Role::Faculty, "assignCourseToFaculty", facultyID)) return;
    auto facultyIt = findFaculty(facultyID);
    auto courseIt = findCourse(courseID);
    if (facultyIt == faculties.end()) {
        std::cout << "Error: Faculty not found.\n";
        return;
    }
    if (courseIt == courses.end()) {
        std::cout << "Error: Course not found.\n";
        return;
    }
    facultyIt->addCurrentCourse(courseID);
    std::cout << "Course assigned to faculty successfully.\n";
}

void CollegeDatabase::moveCourseToPast(int facultyID, const std::string& courseID) {
    if (!hasPermission(Role::Faculty, "moveCourseToPast", facultyID)) return;
    auto facultyIt = findFaculty(facultyID);
    auto courseIt = findCourse(courseID);
    if (facultyIt == faculties.end()) {
        std::cout << "Error: Faculty not found.\n";
        return;
    }
    if (courseIt == courses.end()) {
        std::cout << "Error: Course not found.\n";
        return;
    }
    facultyIt->moveCourseToPast(courseID);
    std::cout << "Course moved to past successfully.\n";
}

void CollegeDatabase::applyForProject(int studentID, int facultyID) {
    if (!hasPermission(Role::Faculty, "applyForProject", facultyID)) return;
    auto studentIt = findStudent(studentID);
    if (studentIt == students.end()) {
        std::cout << "Error: Student not found.\n";
        return;
    }
    auto facultyIt = findFaculty(facultyID);
    if (facultyIt == faculties.end()) {
        std::cout << "Error: Faculty not found.\n";
        return;
    }
    if (!facultyIt->getIsPermanent()) {
        std::cout << "Error: Only permanent faculty can be project guides.\n";
        return;
    }
    if ((*studentIt)->getProjectGuide() != -1) {
        std::cout << "Error: Student already has a project guide.\n";
        return;
    }

    std::string studentType = (*studentIt)->getStudentType();
    bool canAssign = false;
    if (studentType == "BTech") canAssign = facultyIt->canAcceptBTechAdvisee();
    else if (studentType == "DualDegree") canAssign = facultyIt->canAcceptDualDegreeAdvisee();
    else if (studentType == "MTech" || studentType == "PhD") canAssign = facultyIt->canAcceptPostgradAdvisee();

    if (!canAssign) {
        std::cout << "Error: Faculty has reached advisee limit for this student type.\n";
        return;
    }

    (*studentIt)->assignProjectGuide(facultyID);
    if (studentType == "BTech") facultyIt->addBTechAdvisee(studentID);
    else if (studentType == "DualDegree") facultyIt->addDualDegreeAdvisee(studentID);
    else if (studentType == "MTech") facultyIt->addMTechAdvisee(studentID);
    else if (studentType == "PhD") facultyIt->addPhDAdvisee(studentID);
    std::cout << "Project guide assigned successfully.\n";
}

void CollegeDatabase::displayFaculties() const {
    if (!hasPermission(Role::Student, "displayFaculties", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    if (faculties.empty()) { std::cout << "No faculties in the database.\n"; return; }
    for (const auto& faculty : faculties) faculty.display();
}

void CollegeDatabase::addProject(const std::string& id, const std::string& title, const std::string& description, ProjectType type, int facultyID, int vacancies) {
    User* currentUser = userManager.getCurrentUser();
    if (currentUser->getRole() != Role::Admin && !hasPermission(Role::Faculty, "addProject", facultyID)) return;
    if (findProject(id) != projects.end()) {
        std::cout << "Error: Project ID already exists.\n";
        return;
    }
    auto facultyIt = findFaculty(facultyID);
    if (facultyIt == faculties.end()) {
        std::cout << "Error: Faculty not found.\n";
        return;
    }
    if (!facultyIt->getIsPermanent()) {
        std::cout << "Error: Only permanent faculty can propose projects.\n";
        return;
    }
    projects.emplace_back(id, title, description, type, facultyID, vacancies);
    std::cout << "Project added successfully.\n";
}

void CollegeDatabase::deleteProject(const std::string& id) {
    if (!hasPermission(Role::Admin, "deleteProject", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    auto it = findProject(id);
    if (it != projects.end()) {
        projectApplications.erase(
            std::remove_if(projectApplications.begin(), projectApplications.end(),
                [id](const ProjectApplication& a) { return a.getProjectID() == id; }),
            projectApplications.end());
        for (auto& student : students) {
            if (student->getAssignedProject() == id) {
                student->assignProject("");
            }
        }
        projects.erase(it);
        std::cout << "Project deleted successfully.\n";
    } else {
        std::cout << "Error: Project not found.\n";
    }
}

void CollegeDatabase::displayProjects() const {
    if (!hasPermission(Role::Student, "displayProjects", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    if (projects.empty()) { std::cout << "No projects in the database.\n"; return; }
    for (const auto& project : projects) project.display();
}

void CollegeDatabase::applyForProject(int studentID, const std::string& projectID) {
    if (!hasPermission(Role::Student, "applyForProject", studentID)) return;
    auto studentIt = findStudent(studentID);
    if (studentIt == students.end()) {
        std::cout << "Error: Student not found.\n";
        return;
    }
    auto projectIt = findProject(projectID);
    if (projectIt == projects.end()) {
        std::cout << "Error: Project not found.\n";
        return;
    }
    if (findProjectApplication(studentID, projectID) != projectApplications.end()) {
        std::cout << "Error: Student already applied to this project.\n";
        return;
    }
    if (projectIt->getVacancies() <= 0) {
        std::cout << "Error: No vacancies available for this project.\n";
        return;
    }
    std::string studentType = (*studentIt)->getStudentType();
    ProjectType projectType = projectIt->getType();
    if ((studentType == "BTech" && projectType != ProjectType::BTP) ||
        (studentType == "DualDegree" && projectType != ProjectType::DDP) ||
        ((studentType == "MTech" || studentType == "PhD") && projectType != ProjectType::RP)) {
        std::cout << "Error: Student type not eligible for this project type.\n";
        return;
    }
    if ((*studentIt)->getAssignedProject() != "") {
        std::cout << "Error: Student already assigned to a project.\n";
        return;
    }
    projectApplications.emplace_back(studentID, projectID, projectApplicationCounter++);
    std::cout << "Project application submitted successfully.\n";
}

void CollegeDatabase::displayProjectApplications() const {
    if (!hasPermission(Role::Faculty, "displayProjectApplications", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    if (projectApplications.empty()) { std::cout << "No project applications in the database.\n"; return; }
    for (const auto& app : projectApplications) app.display();
}

void CollegeDatabase::assignProjects() {
    if (!hasPermission(Role::Admin, "assignProjects", userManager.getCurrentUser() ? userManager.getCurrentUser()->getID() : -1)) return;
    
    // Clear existing project assignments
    for (auto& student : students) {
        student->assignProject("");
    }

    for (auto& project : projects) {
        project.setVacancies(project.getVacancies()); // Reset vacancies if needed
        std::vector<ProjectApplication> projectApps;
        for (const auto& app : projectApplications) {
            if (app.getProjectID() == project.getProjectID()) {
                projectApps.push_back(app);
            }
        }

        // Sort applications by CGPA
        std::sort(projectApps.begin(), projectApps.end(),
            [&](const ProjectApplication& a, const ProjectApplication& b) {
                auto s1 = findStudent(a.getStudentID());
                auto s2 = findStudent(b.getStudentID());
                return (*s1)->getCGPA() > (*s2)->getCGPA();
            });

        int vacancies = project.getVacancies();
        for (const auto& app : projectApps) {
            if (vacancies <= 0) break;
            auto studentIt = findStudent(app.getStudentID());
            if (studentIt != students.end() && (*studentIt)->getAssignedProject() == "") {
                (*studentIt)->assignProject(project.getProjectID());
                auto facultyIt = findFaculty(project.getFacultyID());
                if (facultyIt != faculties.end()) {
                    std::string studentType = (*studentIt)->getStudentType();
                    if (studentType == "BTech") facultyIt->addBTechAdvisee(app.getStudentID());
                    else if (studentType == "DualDegree") facultyIt->addDualDegreeAdvisee(app.getStudentID());
                    else if (studentType == "MTech") facultyIt->addMTechAdvisee(app.getStudentID());
                    else if (studentType == "PhD") facultyIt->addPhDAdvisee(app.getStudentID());
                }
                vacancies--;
            }
        }
        project.setVacancies(vacancies);
    }

    // Clear project applications after assignment
    projectApplications.clear();
    projectApplicationCounter = 0;
    std::cout << "Projects assigned successfully.\n";
}

std::vector<Student*>::iterator CollegeDatabase::findStudent(int id) {
    return std::find_if(students.begin(), students.end(),
        [id](const Student* s) { return s->getStudentID() == id; });
}

std::vector<Course>::iterator CollegeDatabase::findCourse(const std::string& id) {
    return std::find_if(courses.begin(), courses.end(),
        [id](const Course& c) { return c.getCourseID() == id; });
}

std::vector<Enrollment>::iterator CollegeDatabase::findEnrollment(int studentID, const std::string& courseID) {
    return std::find_if(enrollments.begin(), enrollments.end(),
        [studentID, courseID](const Enrollment& e) {
            return e.getStudentID() == studentID && e.getCourseID() == courseID;
        });
}

std::vector<CourseApplication>::iterator CollegeDatabase::findApplication(int studentID, const std::string& courseID) {
    return std::find_if(applications.begin(), applications.end(),
        [studentID, courseID](const CourseApplication& a) {
            return a.getStudentID() == studentID && a.getCourseID() == courseID;
        });
}

std::vector<Faculty>::iterator CollegeDatabase::findFaculty(int id) {
    return std::find_if(faculties.begin(), faculties.end(),
        [id](const Faculty& f) { return f.getFacultyID() == id; });
}

std::vector<Project>::iterator CollegeDatabase::findProject(const std::string& id) {
    return std::find_if(projects.begin(), projects.end(),
        [id](const Project& p) { return p.getProjectID() == id; });
}

std::vector<ProjectApplication>::iterator CollegeDatabase::findProjectApplication(int studentID, const std::string& projectID) {
    return std::find_if(projectApplications.begin(), projectApplications.end(),
        [studentID, projectID](const ProjectApplication& a) {
            return a.getStudentID() == studentID && a.getProjectID() == projectID;
        });
}

std::vector<Student*>::const_iterator CollegeDatabase::findStudent(int id) const {
    return std::find_if(students.begin(), students.end(),
        [id](const Student* s) { return s->getStudentID() == id; });
}

std::vector<Course>::const_iterator CollegeDatabase::findCourse(const std::string& id) const {
    return std::find_if(courses.begin(), courses.end(),
        [id](const Course& c) { return c.getCourseID() == id; });
}

std::vector<Faculty>::const_iterator CollegeDatabase::findFaculty(int id) const {
    return std::find_if(faculties.begin(), faculties.end(),
        [id](const Faculty& f) { return f.getFacultyID() == id; });
}

std::vector<Project>::const_iterator CollegeDatabase::findProject(const std::string& id) const {
    return std::find_if(projects.begin(), projects.end(),
        [id](const Project& p) { return p.getProjectID() == id; });
}