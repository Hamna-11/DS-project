#pragma once
#ifndef CONSISTENCY_H
#define CONSISTENCY_H

#include "DataStructures.h"
#include <vector>
#include <string>

using namespace std;

class ConsistencyChecker {
private:
    const CourseManager& cm;
    PeopleManager& pm;
    const Relations& rel;
    CustomMap<int, int>& courseToFaculty;
    CustomMap<int, int>& courseToRoom;

    vector<string> errors;
    vector<string> warnings;

public:
    ConsistencyChecker(const CourseManager& c, PeopleManager& p,
        const Relations& r, CustomMap<int, int>& cf, CustomMap<int, int>& cr);
    void runAllChecks();
    void checkPrereqCycles();
    void checkStudentPrereqs();
    void checkStudentOverload();
    void checkFacultyConflicts();
    void checkRoomCapacity();
    void checkUnassignedCourses();
    void checkCourseOverlaps();
    void checkScheduleConflicts();
    CustomSet<int> getCourseStudents(int courseId) const;
    void displayReport() const;

};

#endif