#ifndef PROJECT_APPLICATION_HPP
#define PROJECT_APPLICATION_HPP

#include <string>

class ProjectApplication {
private:
    int studentID;
    std::string projectID;
    int applicationOrder;

public:
    ProjectApplication(int studentID, const std::string& projectID, int order);
    int getStudentID() const;
    std::string getProjectID() const;
    int getApplicationOrder() const;
    void display() const;
};

#endif