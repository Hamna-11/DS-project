#ifndef RELATIONS_H
#define RELATIONS_H

#include <vector>

class CourseManager;

class Relations {
private:
    std::vector<std::vector<bool>> prereq;
    int size;
public:
    Relations();
    void ensureSize(int);
    void addPrereq(int, int);
    bool getPrereq(int, int) const;
    int getSize() const;
    std::vector<std::vector<bool>> closurePrereq() const;
    bool hasPrereqCycle() const;
    bool isReflexive() const;
    bool isSymmetric() const;
    bool isTransitive() const;
    bool isAntiSymmetric() const;
    bool isEquivalenceRelation() const;
    bool isPartialOrder() const;
    void displayMatrix(const CourseManager&) const;
    const std::vector<std::vector<bool>>& getPrereqMatrix() const;
};

#endif