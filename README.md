This is an Object Oriented implementation of the back-end of a College's Database system using C++. This has been inspired from the CS2810 (Object Oriented Algorithm Analysis and Implementation) and CS2800 (Design and Analyis of Algorithms) courses that I took during my 4th semester at the Indian Institute of Technology, Madras.

The codebase implements a hierarchical structure for the Students, where each Degree accounts for a separate class, while all of them derived from the abstract Student parent class.

It also implements separate Faculty class encapsulating each faculty type (Permanent / Adjunct), and also, a history of the past courses taught, a list of the current courses he/she is offerring, and also a list of courses that he/she is planning to take in the upcoming semester.

As is expected of any good database, it provides three levels of authority in terms of data availability and functionalities available, namely:

  a. The Student : Can view his own info, all faculty's basic info (what courses they are offerring, their advisees, projectees, etc.). Can also apply to new projects, upcoming courses in the next semester. But CANNOT VIEW OTHER STUDENTS' INFO or CHANGE ANY EXISTING INFO ON THE DATABASE.
    
  b. The Faculty Member : Can view details of all students (could be implemented such that he/she is able to view only his/her own advisees/projectees' info), can submit grades of all students taking his particular course for that semester, can apply to teach courses for upcoming semesters (since this is decided by respective departments in a meet, we have assumed that there would be no conflicts in course allocation for faculty members, direct allocation has been implemented). BUT STILL CANNOT CHANGE ANY OTHER INFO ON THE DATABASE.
    
  c. The Admin : Highest level of clearance, has all functionalities available.

This is implemented using another abstract User class, with derived Students, Faculties and Admin class.

Since the implementation comes with no external database linked to it as of now, for dry runs, some data can be fed into the system before every test run by a user of Admin level clearance. Then, each separate functionality can be checked accordingly on this data.

PLANS FOR THE FUTURE:

Adding authentication systems and multi-threading to account for multiple users and instances of the code trying to execute on a server. As of now, login data could be checked by iterating through a data file (hashing for faster hits). Consider the security drawbacks of this design and try to make it more robust.
