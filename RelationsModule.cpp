#include "RelationsModule.h"
#include "CourseManager.h"
#include <iostream>
#include <iomanip>

Relations::Relations() : size(0) {}

void Relations::ensureSize(int n) {
    if (n > size) {
        prereq.resize(n, std::vector<bool>(n, false));
        implication.resize(n, std::vector<bool>(n, false));
        size = n;
    }
}

void Relations::addPrereq(int a, int b) {
    ensureSize(std::max(a, b) + 1);
    prereq[a][b] = true;
}

void Relations::addImplication(int a, int b) {
    ensureSize(std::max(a, b) + 1);
    implication[a][b] = true;
}

bool Relations::getPrereq(int a, int b) const {
    if (a < 0 || b < 0 || a >= size || b >= size) return false;
    return prereq[a][b];
}

int Relations::getSize() const { return size; }

std::vector<std::vector<bool>> Relations::closurePrereq() const {
    std::vector<std::vector<bool>> result = prereq;
    for (int k = 0; k < size; k++)
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (result[i][k] && result[k][j])
                    result[i][j] = true;
    return result;
}

bool Relations::hasPrereqCycle() const {
    auto closure = closurePrereq();
    for (int i = 0; i < size; i++) if (closure[i][i]) return true;
    return false;
}

bool Relations::isReflexive() const {
    for (int i = 0; i < size; i++) if (!prereq[i][i]) return false;
    return true;
}

bool Relations::isSymmetric() const {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (prereq[i][j] != prereq[j][i]) return false;
    return true;
}

bool Relations::isTransitive() const {
    auto closure = closurePrereq();
    return closure == prereq;
}

bool Relations::isEquivalence() const {
    return isReflexive() && isSymmetric() && isTransitive();
}

bool Relations::isPartialOrder() const {
    return isReflexive() && !isSymmetric() && isTransitive();
}

void Relations::displayMatrix(const CourseManager& cm) const {
    std::cout << "\n" << std::string(60, '=') << "\n PREREQUISITE MATRIX\n" << std::string(60, '=') << "\n\n";
    std::cout << " ";
    for (int i = 0; i < size; i++) {
        const auto* c = cm.getCourse(i);
        std::cout << std::setw(6) << (c ? c->code : std::to_string(i));
    }
    std::cout << "\n";
    for (int i = 0; i < size; i++) {
        const auto* c = cm.getCourse(i);
        std::cout << std::setw(5) << (c ? c->code : std::to_string(i));
        for (int j = 0; j < size; j++) {
            std::cout << std::setw(6) << (prereq[i][j] ? "Y" : ".");
        }
        std::cout << "\n";
    }
    std::cout << "\nY = Has prerequisite | . = No relationship\n";
}

const std::vector<std::vector<bool>>& Relations::getPrereqMatrix() const { return prereq; }