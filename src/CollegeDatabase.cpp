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

CollegeDatabase::CollegeDatabase() : applicationCounter(0) {}

CollegeDatabase::~CollegeDatabase() {
    for (Student* student : students) delete student;
}

void CollegeDatabase::addStudent(const std::string& type, int id, const std::string& name, const std::string& email, double cgpa) {
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
    if (students.empty()) { std::cout << "No students in the database.\n"; return; }
    for (const auto* student : students) student->display();
}

void CollegeDatabase::addCourse(const std::string& id, const std::string& name, int credits, AllocationType alloc, int capacity) {
    if (findCourse(id) == courses.end()) {
        courses.emplace_back(id, name, credits, alloc, capacity);
        std::cout << "Course added successfully.\n";
    } else {
        std::cout << "Error: Course ID already exists.\n";
    }
}

void CollegeDatabase::updateCourse(const std::string& id, const std::string& name, int credits, AllocationType alloc, int capacity) {
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
    if (courses.empty()) { std::cout << "No courses in the database.\n"; return; }
    for (const auto& course : courses) course.display();
}

void CollegeDatabase::applyForCourse(int studentID, const std::string& courseID, int priority) {
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
    if (applications.empty()) { std::cout << "No applications in the database.\n"; return; }
    for (const auto& app : applications) app.display();
}

void CollegeDatabase::allocateCourses() {
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
    auto it = findEnrollment(studentID, courseID);
    if (it != enrollments.end()) {
        it->setGrade(grade);
        std::cout << "Grade updated successfully.\n";
    } else {
        std::cout << "Error: Enrollment not found.\n";
    }
}

void CollegeDatabase::deleteEnrollment(int studentID, const std::string& courseID) {
    auto it = findEnrollment(studentID, courseID);
    if (it != enrollments.end()) {
        enrollments.erase(it);
        std::cout << "Enrollment deleted successfully.\n";
    } else {
        std::cout << "Error: Enrollment not found.\n";
    }
}

void CollegeDatabase::displayEnrollments() const {
    if (enrollments.empty()) { std::cout << "No enrollments in the database.\n"; return; }
    for (const auto& enrollment : enrollments) enrollment.display();
}

void CollegeDatabase::displayStudentCourses(int studentID) const {
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
    if (findFaculty(id) == faculties.end()) {
        faculties.emplace_back(id, name, isPermanent);
        std::cout << "Faculty added successfully.\n";
    } else {
        std::cout << "Error: Faculty ID already exists.\n";
    }
}

void CollegeDatabase::assignCourseToFaculty(int facultyID, const std::string& courseID) {
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

void CollegeDatabase::applyForProject(int studentID, int facultyID) {
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
    if (faculties.empty()) { std::cout << "No faculties in the database.\n"; return; }
    for (const auto& faculty : faculties) faculty.display();
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