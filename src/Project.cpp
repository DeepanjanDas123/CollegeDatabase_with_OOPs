#include "Project.hpp"
#include <iostream>

Project::Project(const std::string& id, const std::string& title, const std::string& desc, ProjectType type, int facultyID, int vacancies)
    : projectID(id), title(title), description(desc), type(type), facultyID(facultyID), vacancies(vacancies) {}

std::string Project::getProjectID() const { return projectID; }
std::string Project::getTitle() const { return title; }
std::string Project::getDescription() const { return description; }
ProjectType Project::getType() const { return type; }
int Project::getFacultyID() const { return facultyID; }
int Project::getVacancies() const { return vacancies; }
void Project::setVacancies(int vac) { vacancies = vac; }

void Project::display() const {
    std::cout << "Project ID: " << projectID
              << ", Title: " << title
              << ", Type: " << (type == ProjectType::BTP ? "BTP" : type == ProjectType::DDP ? "DDP" : "RP")
              << ", Faculty ID: " << facultyID
              << ", Vacancies: " << vacancies
              << "\nDescription: " << description << "\n";
}