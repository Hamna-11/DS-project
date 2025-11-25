#ifndef PROOF_H
#define PROOF_H

#include "Relations.h"
#include "CourseManager.h"
#include <vector>
#include <string>

class ProofGenerator {
private:
    const Relations& rel;
    const CourseManager& cm;
    std::vector<std::string> steps;

public:
    ProofGenerator(const Relations& r, const CourseManager& c) : rel(r), cm(c) {}

    void generatePrereqProof(int courseId, const std::vector<bool>& completed) {
        steps.clear();
        steps.push_back("=== PREREQUISITE PROOF ===");

        const auto* course = cm.getCourse(courseId);
        if (course) {
            steps.push_back("Goal: Verify prerequisites for " + course->code);
        }

        auto closure = rel.closurePrereq();
        bool allMet = true;

        for (int i = 0; i < rel.getSize(); i++) {
            if (closure[i][courseId]) {
                const auto* prereq = cm.getCourse(i);
                if (completed[i]) {
                    steps.push_back("✓ " + (prereq ? prereq->code : std::to_string(i)) + " [COMPLETED]");
                }
                else {
                    steps.push_back("✗ " + (prereq ? prereq->code : std::to_string(i)) + " [MISSING]");
                    allMet = false;
                }
            }
        }

        if (allMet) {
            steps.push_back("CONCLUSION: All prerequisites satisfied ∎");
        }
        else {
            steps.push_back("CONCLUSION: Prerequisites NOT satisfied ∎");
        }
    }

    void generateAcyclicProof() {
        steps.clear();
        steps.push_back("=== ACYCLIC GRAPH PROOF ===");
        steps.push_back("Theorem: Prerequisite graph contains no cycles");
        steps.push_back("Proof by contradiction:");

        if (rel.hasPrereqCycle()) {
            steps.push_back("Found cycle in prerequisite graph");
            steps.push_back("CONCLUSION: Graph is NOT acyclic ∎");
        }
        else {
            steps.push_back("Base case: Empty graph has no cycles");
            steps.push_back("Inductive step: Each added edge maintains acyclic property");
            steps.push_back("No course depends on itself directly or indirectly");
            steps.push_back("CONCLUSION: Graph is acyclic ∎");
        }
    }

    void display() const {
        for (const auto& step : steps) {
            std::cout << step << "\n";
        }
        std::cout << "\n";
    }
};

#endif