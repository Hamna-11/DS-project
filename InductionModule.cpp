#include "InductionModule.h"
#include "RelationsModule.h"
#include "CourseManager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>

Scheduling::Scheduling(const Relations& r) : relations(r) {}

void Scheduling::backtrack(const std::vector<std::vector<bool>>& adj, std::vector<bool>& used,
    std::vector<int>& order, int n, int limit) {
    if ((int)validOrders.size() >= limit) return;
    if ((int)order.size() == n) {
        validOrders.push_back(order);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        bool hasIncoming = false;
        for (int j = 0; j < n; j++) {
            if (!used[j] && adj[j][i]) {
                hasIncoming = true;
                break;
            }
        }
        if (!hasIncoming) {
            used[i] = true;
            order.push_back(i);
            backtrack(adj, used, order, n, limit);
            order.pop_back();
            used[i] = false;
        }
    }
}

int Scheduling::generateOrders(int n, int limit) {
    validOrders.clear();
    if (n <= 0) return 0;
    auto adj = relations.getPrereqMatrix();
    std::vector<bool> used(n, false);
    std::vector<int> order;
    backtrack(adj, used, order, n, limit);
    return validOrders.size();
}

void Scheduling::displayOrders(const CourseManager& cm, int maxDisplay) const {
    std::cout << "\n" << std::string(60, '=') << "\n VALID COURSE SEQUENCES\n" << std::string(60, '=') << "\n\n";
    std::cout << "\nTotal sequences found: " << validOrders.size() << "\n\n";
    int display = std::min(maxDisplay, (int)validOrders.size());
    for (int i = 0; i < display; i++) {
        std::cout << "Sequence #" << (i + 1) << ": ";
        for (size_t j = 0; j < validOrders[i].size(); j++) {
            const auto* c = cm.getCourse(validOrders[i][j]);
            if (c) std::cout << c->code;
            else std::cout << validOrders[i][j];
            if (j < validOrders[i].size() - 1) std::cout << " -> ";
        }
        std::cout << "\n";
    }
    if ((int)validOrders.size() > maxDisplay) {
        std::cout << "\n... and " << (validOrders.size() - maxDisplay) << " more sequences\n";
    }
}

bool Induction::dfsCheck(int courseId, const std::vector<bool>& completed,
    std::vector<bool>& visited, const std::vector<std::vector<bool>>& prereq) const {
    if (courseId >= 0 && courseId < (int)completed.size() && completed[courseId]) return true;
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

void Induction::displayCheck(const CourseManager& cm, int courseId, const std::vector<bool>& completed) const {
    std::cout << "\n" << std::string(60, '=') << "\n INDUCTION VERIFICATION\n" << std::string(60, '=') << "\n\n";
    const auto* c = cm.getCourse(courseId);
    std::cout << "\nChecking prerequisites for: ";
    if (c) std::cout << c->code << " (" << c->name << ")\n";
    else std::cout << "Course #" << courseId << "\n";

    std::cout << "\n--- Completed Courses ---\n";
    for (int i = 0; i < (int)completed.size(); i++) {
        if (completed[i]) {
            const auto* cc = cm.getCourse(i);
            if (cc) std::cout << cc->code << " ";
        }
    }
    std::cout << "\n\n";

    bool rec = checkRecursive(courseId, completed);
    std::cout << "RECURSIVE INDUCTION: " << (rec ? "[PASS]" : "[FAIL]") << "\n";
    bool strong = checkStrong(courseId, completed);
    std::cout << "STRONG INDUCTION: " << (strong ? "[PASS]" : "[FAIL]") << "\n";

    auto indirect = listIndirect(courseId);
    if (!indirect.empty()) {
        std::cout << "\n--- All Prerequisites (Direct + Indirect) ---\n";
        for (int id : indirect) {
            const auto* pc = cm.getCourse(id);
            std::cout << (pc ? pc->code : std::to_string(id)) << " ";
            std::cout << (completed[id] ? "[DONE]" : "[MISSING]") << "\n";
        }
    }
    std::cout << "\n";
}

void StudentGroupModule::generateCombinations(int start, int k, std::vector<std::string>& current) {
    if ((int)current.size() == k) {
        groups.push_back(current);
        return;
    }
    for (int i = start; i < (int)students.size(); i++) {
        current.push_back(students[i]);
        generateCombinations(i + 1, k, current);
        current.pop_back();
    }
}

long long StudentGroupModule::nCr(int n, int r) const {
    if (r > n || r < 0) return 0;
    if (r == 0 || r == n) return 1;
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

bool StudentGroupModule::addStudent(const std::string& name) {
    if (std::find(students.begin(), students.end(), name) != students.end()) {
        std::cout << "[WARNING] Student already exists!\n";
        return false;
    }
    students.push_back(name);
    std::cout << "[SUCCESS] Added student: " << name << "\n";
    return true;
}

void StudentGroupModule::display() const {
    std::cout << "\n" << std::string(60, '=') << "\n STUDENT LIST\n" << std::string(60, '=') << "\n\n";
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << (i + 1) << ". " << students[i] << "\n";
    }
    std::cout << "\nTotal: " << students.size() << "\n";
}

void StudentGroupModule::displayCombinations(int groupSize) {
    std::cout << "\n" << std::string(60, '=') << "\n GROUP COMBINATIONS\n" << std::string(60, '=') << "\n\n";
    if (groupSize <= 0 || groupSize > (int)students.size()) {
        std::cout << "[ERROR] Invalid group size!\n";
        return;
    }
    groups.clear();
    std::vector<std::string> current;
    generateCombinations(0, groupSize, current);
    std::cout << "\nGroup Size: " << groupSize << "\n";
    std::cout << "Total Combinations: " << groups.size() << "\n";
    std::cout << "Formula: C(" << students.size() << "," << groupSize << ") = " << nCr(students.size(), groupSize) << "\n\n";
    int display = std::min(30, (int)groups.size());
    for (int i = 0; i < display; i++) {
        std::cout << "Group #" << (i + 1) << ": ";
        for (size_t j = 0; j < groups[i].size(); j++) {
            std::cout << groups[i][j];
            if (j < groups[i].size() - 1) std::cout << ", ";
        }
        std::cout << "\n";
    }
    if ((int)groups.size() > 30) {
        std::cout << "\n... and " << (groups.size() - 30) << " more\n";
    }
}