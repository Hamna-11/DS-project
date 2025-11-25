#ifndef SET_H
#define SET_H

#include "CourseManager.h"
#include "PeopleManager.h"

class SetOps {
public:
    static CustomSet<int> unionSet(const CustomSet<int>&, const CustomSet<int>&);
    static CustomSet<int> intersection(const CustomSet<int>&, const CustomSet<int>&);
    static CustomSet<int> difference(const CustomSet<int>&, const CustomSet<int>&);
    static CustomSet<int> symmetricDifference(const CustomSet<int>&, const CustomSet<int>&);
    static std::vector<CustomSet<int>> powerSet(const CustomSet<int>&);
    static void display(const CourseManager&, int, int, PeopleManager&);
private:
    static void displaySet(const CustomSet<int>&, const CourseManager&);
};

#endif