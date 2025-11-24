#pragma once
#ifndef CLI_H
#define CLI_H

#include "DataStructures.h"
#include <string>

using namespace std;

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
    void exportData(const string& filename);
    void showHelp();

};

#endif