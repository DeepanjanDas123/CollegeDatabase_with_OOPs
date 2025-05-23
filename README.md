# College Database Management System

## Overview

The College Database Management System is a robust C++ application designed to streamline academic record management for a college. It supports three user roles—Admin, Faculty, and Student—enabling functionalities like student and course management, enrollment, grade updates, project assignments, and user authentication. Built with a modular object-oriented design, the system uses inheritance for student types (BTech, DualDegree, MTech, PhD) and manages data through a central `CollegeDatabase` class. It allocates courses based on their allocation type, following the Gale Shapley algorithm to match students with their best courses possible, such that there exists no unstable matchings. Check out Gale Shapley algorithm here -> https://en.wikipedia.org/wiki/Gale%E2%80%93Shapley_algorithm

Key features include:

- **User Authentication**: Secure login for Admin, Faculty, and Student roles.
- **Student Management**: Add, update, delete, and view student records.
- **Course Management**: Create, modify, and allocate courses based on CGPA or random allocation.
- **Enrollment and Grading**: Enroll students, update grades, and automatically calculate CGPA and total credits.
- **Faculty and Project Management**: Assign courses/projects to faculty and students.
- **Debug Logging**: Detailed logs for troubleshooting, especially in `updateGrade`.

This project showcases advanced C++ programming, object-oriented design, and practical application in academic administration.

## Prerequisites

- **Operating System**: Windows, Linux, or macOS
- **Compiler**: C++17 compatible (e.g., GCC, Clang, MSVC)
- **CMake**: Version 3.10 or higher
- **Git**: For cloning the repository

## Installation

1. **Clone the Repository**:

   ```bash
   git clone <repository_url>
   cd CollegeDatabase_with_OOPs
   ```
2. **Create Build Directory**:

   ```bash
   mkdir build
   cd build
   ```
3. **Build the Project**:

   ```bash
   cmake ..
   cmake --build .
   ```

   The executable (`college_database` or `college_database.exe`) will be in `build` or `build/Debug`.

## Directory Structure

```
college-database/
├── include/
│   ├── CollegeDatabase.hpp
│   ├── Course.hpp
│   ├── CourseApplication.hpp
│   ├── Enrollment.hpp
│   ├── Faculty.hpp
│   ├── Project.hpp
│   ├── ProjectApplication.hpp
│   ├── Student.hpp
│   ├── UserManager.hpp
├── src/
│   ├── CollegeDatabase.cpp
│   ├── Course.cpp
│   ├── CourseApplication.cpp
│   ├── Enrollment.cpp
│   ├── Faculty.cpp
│   ├── Project.cpp
│   ├── ProjectApplication.cpp
│   ├── Student.cpp
│   ├── UserManager.cpp
├── main.cpp
├── CMakeLists.txt
├── README.md
├── CollegeDatabaseDoc.tex
```

## Usage

1. **Run the Application**:

   ```bash
   ./college_database  # Linux/macOS
   .\Debug\college_database.exe  # Windows
   ```
2. **Login**:
   - **Admin**: `admin/admin123`
   - **Faculty**: `smith/smith123` (ID 101), `jones/jones123` (ID 102)
   - **Students**: `john/john123` (ID 1), `jane/jane123` (ID 2), `alice/alice123` (ID 3), `bob/bob123` (ID 4)
3. **Navigate Menus**:
   - The login menu offers options to log in or exit.
   - After login, role-specific menus provide access to functionalities (e.g., Admin: add students, update grades; Faculty: assign courses; Student: view courses).

### Initial Data

- **Users**: Admin, 2 faculty, 4 students.
- **Students**: John (BTech), Jane (DualDegree), Alice (MTech), Bob (PhD).
- **Courses**: CS101 (3 credits), MATH201 (4 credits), PHYS301 (3 credits), CHEM401 (3 credits).
- **Enrollments**: John/Jane in CS101, Alice in MATH201, Bob in PHYS301.
- **Faculty**: Dr. Smith (permanent), Dr. Jones (non-permanent).
- **Projects**: BTP001, DDP001, RP001 (by Dr. Smith).

## Key Functionalities

- **Admin**:
  - Manage users, students, courses, enrollments, faculty, and projects.
  - Update grades, automatically recalculating CGPA and total credits.
  - Allocate courses/projects based on applications.
- **Faculty**:
  - View all data, assign courses/projects, update grades for assigned courses.
- **Student**:
  - View personal info, enrolled courses, and apply for courses/projects.
- **Grade Update**:
  - Updates `totalCredits` and CGPA using: `temp = totalCredits * CGPA; temp += course.credits * grade; totalCredits += course.credits; CGPA = temp / totalCredits`.
  - Grade values: S=10, A=9, B=8, C=7, D=6, E=5, P=4, F=0.

## Testing

1. **Grade Update**:
   - Log in as `admin`, select option 12, set grade for student ID 1, course CS101, grade A.
   - Expected: CGPA=10, totalCredits=3 (if new grade).
   - Verify as `john` (option 4: view courses, option 1: view info).
2. **Custom Data**:
   - Modify `main.cpp` to add new students/courses:

     ```cpp
     db.login("admin", "admin123");
     db.addStudent("BTech", 100, "Test Student", "test@university.com", 8.0);
     db.addCourse("CS999", "New Course", 4, AllocationType::CGPA, 10);
     db.enrollStudent(100, "CS999");
     ```
   - Or use Admin menu (options 2, 6, 11).
3. **Debugging**:
   - Check `[DEBUG]` logs in `updateGrade` for permission or data issues.

## Contributing

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/YourFeature`).
3. Commit changes (`git commit -m "Add YourFeature"`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a pull request.

## Future Enhancements

- Add persistent storage (file I/O or database).
- Support additional student types (e.g., MSc).
- Implement grade history tracking.
- Enhance course allocation algorithms.

## License

MIT License. See LICENSE for details.

## Contact

For issues or suggestions, open an issue on the repository or contact the maintainer at \[deepaanjaan2020@gmail.com\].
