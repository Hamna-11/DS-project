#ifndef INDUCTIONMODULE_H
#define INDUCTIONMODULE_H

#include <vector>
#include <string>

class Relations;
class CourseManager;

class Scheduling {
private:
    const Relations& relations;
    std::vector<std::vector<int>> validOrders;
    void backtrack(const std::vector<std::vector<bool>>&, std::vector<bool>&, std::vector<int>&, int, int);
public:
    Scheduling(const Relations&);
    int generateOrders(int, int limit = 500);
    void displayOrders(const CourseManager&, int maxDisplay = 20) const;
    const std::vector<std::vector<int>>& getOrders() const;
};

class Induction {
private:
    const Relations& relations;
    bool dfsCheck(int, const std::vector<bool>&, std::vector<bool>&, const std::vector<std::vector<bool>>&) const;
public:
    Induction(const Relations&);
    bool checkRecursive(int, const std::vector<bool>&) const;
    bool checkStrong(int, const std::vector<bool>&) const;
    std::vector<int> listIndirect(int) const;
    void displayCheck(const CourseManager&, int, const std::vector<bool>&) const;
};

class StudentGroupModule {
private:
    std::vector<std::string> students;
    std::vector<std::vector<std::string>> groups;
    void generateCombinations(int, int, std::vector<std::string>&);
    long long nCr(int, int) const;
public:
    bool addStudent(const std::string&);
    void display() const;
    void displayCombinations(int);
};

#endif#pragma once
