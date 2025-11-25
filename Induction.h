#ifndef INDUCTION_H
#define INDUCTION_H

#include <vector>
#include <string>

class Relations;
class CourseManager;

class Induction {
private:
    const Relations& relations;
    bool dfsCheck(int, const std::vector<bool>&, std::vector<bool>&,
        const std::vector<std::vector<bool>>&) const;
public:
    Induction(const Relations&);
    bool checkRecursive(int, const std::vector<bool>&) const;
    bool checkStrong(int, const std::vector<bool>&) const;
    std::vector<int> listIndirect(int) const;
    void displayCheck(const CourseManager&, int, const std::vector<bool>&) const;
};

#endif