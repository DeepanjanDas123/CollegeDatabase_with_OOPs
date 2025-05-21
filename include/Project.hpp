#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <string>

enum class ProjectType { BTP, DDP, RP };

class Project {
private:
    std::string projectID;
    std::string title;
    std::string description;
    ProjectType type;
    int facultyID;
    int vacancies;

public:
    Project(const std::string& id, const std::string& title, const std::string& desc, ProjectType type, int facultyID, int vacancies);
    std::string getProjectID() const;
    std::string getTitle() const;
    std::string getDescription() const;
    ProjectType getType() const;
    int getFacultyID() const;
    int getVacancies() const;
    void setVacancies(int vac);
    void display() const;
};

#endif