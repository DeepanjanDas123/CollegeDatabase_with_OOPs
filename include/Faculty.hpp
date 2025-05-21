#ifndef FACULTY_HPP
#define FACULTY_HPP

#include <string>
#include <vector>

class Faculty {
private:
    int facultyID;
    std::string name;
    bool isPermanent;
    std::vector<std::string> currentCourses;
    std::vector<std::string> pastCourses;
    std::vector<int> btechAdvisees;
    std::vector<int> dualDegreeAdvisees;
    std::vector<int> mtechAdvisees;
    std::vector<int> phdAdvisees;

public:
    Faculty(int id, const std::string& name, bool isPermanent);
    int getFacultyID() const;
    std::string getName() const;
    bool getIsPermanent() const;
    const std::vector<std::string>& getCurrentCourses() const;
    const std::vector<std::string>& getPastCourses() const;
    const std::vector<int>& getBTechAdvisees() const;
    const std::vector<int>& getDualDegreeAdvisees() const;
    const std::vector<int>& getMTechAdvisees() const;
    const std::vector<int>& getPhDAdvisees() const;
    void addCurrentCourse(const std::string& courseID);
    void moveCourseToPast(const std::string& courseID);
    bool canAcceptBTechAdvisee() const;
    bool canAcceptDualDegreeAdvisee() const;
    bool canAcceptPostgradAdvisee() const;
    void addBTechAdvisee(int studentID);
    void addDualDegreeAdvisee(int studentID);
    void addMTechAdvisee(int studentID);
    void addPhDAdvisee(int studentID);
    void removeBTechAdvisee(int studentID);
    void removeDualDegreeAdvisee(int studentID);
    void removeMTechAdvisee(int studentID);
    void removePhDAdvisee(int studentID);
    void display() const;
};

#endif