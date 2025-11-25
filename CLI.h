#ifndef CLI_H
#define CLI_H

#include "DataStructures.h"
#include "PeopleManager.h"
#include <string>

class CLIInterface {
private:
    CourseManager& cm;
    PeopleManager& pm;
    Relations& rel;
    CustomMap<int, int>& courseToFaculty;
    CustomMap<int, int>& courseToRoom;
    CustomMap<int, int> facultyToRoom;

public:
    CLIInterface(CourseManager& c, PeopleManager& p, Relations& r,
        CustomMap<int, int>& cf, CustomMap<int, int>& cr);

    void showWelcome();
    void displayStatistics();
    void quickSetup();
    CustomMap<int, int>& getFacultyToRoom();
    void exportData(const std::string& filename);
    void showHelp();

    void addStudentMenu();
    void addCourseMenu();
    void addFacultyMenu();
    void addRoomMenu();

    // default args must match in declaration + definition
    void addPrerequisiteMenu(int courseId = -1);
    void enrollStudentMenu(int studentId = -1);

    void assignFacultyMenu();
    void assignRoomMenu();

    void listStudents();
    void listCourses();
    void listFaculty();
    void listRooms();

    void viewStudentDetails();
    void viewCourseDetails();

    void runVerification();
};

#endif // CLI_H
