#include "Induction.h"
#include "DataStructures.h"
#include "CourseManager.h"
#include <iostream>
#include <iomanip>

bool Induction::dfsCheck(int courseId, const std::vector<bool>& completed,
    std::vector<bool>& visited,
    const std::vector<std::vector<bool>>& prereq) const {
    if (courseId >= 0 && courseId < (int)completed.size() && completed[courseId])
        return true;
    if (visited[courseId]) return false;
    visited[courseId] = true;
    for (int i = 0; i < (int)prereq.size(); i++) {
        if (prereq[i][courseId]) {
            if (!dfsCheck(i, completed, visited, prereq)) return false;
        }
    }
    return completed[courseId];
}

Induction::Induction(const Relations& r) : relations(r) {}

bool Induction::checkRecursive(int courseId, const std::vector<bool>& completed) const {
    auto prereq = relations.getPrereqMatrix();
    std::vector<bool> visited(prereq.size(), false);
    return dfsCheck(courseId, completed, visited, prereq);
}

bool Induction::checkStrong(int courseId, const std::vector<bool>& completed) const {
    auto closure = relations.closurePrereq();
    for (int i = 0; i < (int)closure.size(); i++) {
        if (closure[i][courseId] && !completed[i]) return false;
    }
    return true;
}

std::vector<int> Induction::listIndirect(int courseId) const {
    auto closure = relations.closurePrereq();
    std::vector<int> result;
    for (int i = 0; i < (int)closure.size(); i++) {
        if (closure[i][courseId]) result.push_back(i);
    }
    return result;
}

void Induction::displayCheck(const CourseManager& cm, int courseId,
    const std::vector<bool>& completed) const {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  INDUCTION VERIFICATION\n";
    std::cout << std::string(60, '=') << "\n\n";

    const auto* c = cm.getCourse(courseId);
    std::cout << "Checking: " << (c ? c->code : std::to_string(courseId)) << "\n\n";

    bool rec = checkRecursive(courseId, completed);
    std::cout << "Recursive Check: " << (rec ? "[PASS]" : "[FAIL]") << "\n";

    bool strong = checkStrong(courseId, completed);
    std::cout << "Strong Check: " << (strong ? "[PASS]" : "[FAIL]") << "\n";

    auto indirect = listIndirect(courseId);
    if (!indirect.empty()) {
        std::cout << "\nAll Prerequisites:\n";
        for (int id : indirect) {
            const auto* pc = cm.getCourse(id);
            std::cout << "  " << (pc ? pc->code : std::to_string(id));
            std::cout << " " << (completed[id] ? "[DONE]" : "[MISSING]") << "\n";
        }
    }
    std::cout << "\n";
}