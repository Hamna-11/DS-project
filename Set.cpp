#include "Set.h"
#include <iostream>

CustomSet<int> SetOps::unionSet(const CustomSet<int>& A, const CustomSet<int>& B) {
    CustomSet<int> result;
    for (int x : A.getVector()) result.insert(x);
    for (int x : B.getVector()) result.insert(x);
    return result;
}

CustomSet<int> SetOps::intersection(const CustomSet<int>& A, const CustomSet<int>& B) {
    CustomSet<int> result;
    for (int x : A.getVector()) {
        if (B.contains(x)) result.insert(x);
    }
    return result;
}

CustomSet<int> SetOps::difference(const CustomSet<int>& A, const CustomSet<int>& B) {
    CustomSet<int> result;
    for (int x : A.getVector()) {
        if (!B.contains(x)) result.insert(x);
    }
    return result;
}

CustomSet<int> SetOps::symmetricDifference(const CustomSet<int>& A, const CustomSet<int>& B) {
    CustomSet<int> result;
    for (int x : A.getVector()) if (!B.contains(x)) result.insert(x);
    for (int x : B.getVector()) if (!A.contains(x)) result.insert(x);
    return result;
}

std::vector<CustomSet<int>> SetOps::powerSet(const CustomSet<int>& S) {
    std::vector<CustomSet<int>> result;
    std::vector<int> elements = S.getVector();
    int n = elements.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        CustomSet<int> subset;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) subset.insert(elements[i]);
        }
        result.push_back(subset);
    }
    return result;
}

void SetOps::displaySet(const CustomSet<int>& s, const CourseManager& cm) {
    std::cout << "{ ";
    bool first = true;
    for (int id : s.getVector()) {
        if (!first) std::cout << ", ";
        const auto* c = cm.getCourse(id);
        std::cout << (c ? c->code : std::to_string(id));
        first = false;
    }
    std::cout << " }\n";
}

void SetOps::display(const CourseManager& cm, int s1, int s2, PeopleManager& pm) {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  SET OPERATIONS\n";
    std::cout << std::string(60, '=') << "\n\n";

    auto* st1 = pm.getStudent(s1);
    auto* st2 = pm.getStudent(s2);
    if (!st1 || !st2) {
        std::cout << "[ERROR] Invalid student IDs!\n";
        return;
    }

    CustomSet<int> A, B;
    for (int x : st1->enrolled) A.insert(x);
    for (int x : st2->enrolled) B.insert(x);

    std::cout << "Student 1: " << st1->name << " -> ";
    displaySet(A, cm);
    std::cout << "Student 2: " << st2->name << " -> ";
    displaySet(B, cm);

    std::cout << "\nOperations:\n";
    std::cout << "UNION: ";
    displaySet(unionSet(A, B), cm);
    std::cout << "INTERSECTION: ";
    displaySet(intersection(A, B), cm);
    std::cout << "DIFFERENCE (A-B): ";
    displaySet(difference(A, B), cm);
    std::cout << "SYMMETRIC DIFF: ";
    displaySet(symmetricDifference(A, B), cm);
    std::cout << "\n";
}