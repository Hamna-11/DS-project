#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "DataStructures.h"
#include <vector>

using namespace std;

class Functions {
public:
    static bool isInjective(const CustomMap<int, int>& f);
    static bool isSurjective(const CustomMap<int, int>& f, int codomainSize);
    static bool isBijective(const CustomMap<int, int>& f, int codomainSize);
    static CustomMap<int, int> compose(const CustomMap<int, int>& f, const CustomMap<int, int>& g);
    static CustomMap<int, int> inverse(const CustomMap<int, int>& f, int codomainSize);
    static bool verifyInverse(const CustomMap<int, int>& f, const CustomMap<int, int>& f_inv);
    static void analyzeStudentCourses(PeopleManager& pm, const CourseManager& cm);
    static void analyzeFacultyRooms(const CustomMap<int, int>& facultyToRoom, PeopleManager& pm);
    static vector<CustomSet<int>> powerSet(const CustomSet<int>& s);
    static vector<pair<int, int>> cartesianProduct(const CustomSet<int>& a, const CustomSet<int>& b);
    static void display(const CustomMap<int, int>& courseToFaculty, const CourseManager& cm, PeopleManager& pm);
};

#endif