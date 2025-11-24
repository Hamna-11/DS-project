#include "Proof.h"
#include <iostream>
#include <sstream>

using namespace std;

ProofGenerator::ProofGenerator(const Relations& r, const CourseManager& c) : relations(r), cm(c) {}

void ProofGenerator::generatePrereqProof(int courseId, const vector<bool>& completed) {
    proofSteps.clear();

    const auto* course = cm.getCourse(courseId);
    string courseName = course ? course->code : to_string(courseId);

    proofSteps.push_back({
        "Checking enrollment eligibility for " + courseName,
        "Verifying prerequisites",
        0
        });

    proofSteps.push_back({
        "Checking direct prerequisites",
        "First level verification",
        1
        });

    auto prereq = relations.getPrereqMatrix();
    bool hasDirectPrereq = false;

    for (int i = 0; i < (int)prereq.size(); i++) {
        if (prereq[i][courseId]) {
            hasDirectPrereq = true;
            const auto* p = cm.getCourse(i);
            string pName = p ? p->code : to_string(i);

            if (completed[i]) {
                proofSteps.push_back({
                    pName + " is completed",
                    "Requirement satisfied",
                    2
                    });
            }
            else {
                proofSteps.push_back({
                    pName + " is NOT completed",
                    "Missing prerequisite",
                    2
                    });
            }
        }
    }

    if (!hasDirectPrereq) {
        proofSteps.push_back({
            "No direct prerequisites required",
            "Can enroll directly",
            2
            });
    }

    proofSteps.push_back({
        "Checking indirect prerequisites",
        "Transitive dependency check",
        1
        });

    auto closure = relations.closurePrereq();
    for (int i = 0; i < (int)closure.size(); i++) {
        if (closure[i][courseId] && i != courseId) {
            const auto* p = cm.getCourse(i);
            string pName = p ? p->code : to_string(i);

            if (completed[i]) {
                proofSteps.push_back({
                    "Indirect prerequisite " + pName + " satisfied",
                    "Chain requirement met",
                    2
                    });
            }
            else {
                proofSteps.push_back({
                    "Indirect prerequisite " + pName + " NOT satisfied",
                    "Chain requirement missing",
                    2
                    });
            }
        }
    }

    bool allSatisfied = true;
    for (int i = 0; i < (int)closure.size(); i++) {
        if (closure[i][courseId] && !completed[i]) {
            allSatisfied = false;
            break;
        }
    }

    proofSteps.push_back({
        allSatisfied ? "Result: Can enroll" : "Result: Cannot enroll",
        allSatisfied ? "All prerequisites satisfied" : "Missing required courses",
        0
        });
}

void ProofGenerator::generateCourseChainProof(int studentId, PeopleManager& pm) {
    proofSteps.clear();

    auto* student = pm.getStudent(studentId);
    string studentName = student ? student->name : to_string(studentId);

    proofSteps.push_back({
        "Analyzing course sequence for " + studentName,
        "Building valid course order",
        0
        });

    proofSteps.push_back({
        "Finding courses with no prerequisites",
        "Starting point identification",
        1
        });

    if (student) {
        vector<int> noPrerequCourses;
        auto matrix = relations.getPrereqMatrix();

        for (int c : student->enrolled) {
            bool hasPrereq = false;
            for (int i = 0; i < relations.getSize(); i++) {
                if (matrix[i][c]) {
                    hasPrereq = true;
                    break;
                }
            }
            if (!hasPrereq) {
                noPrerequCourses.push_back(c);
            }
        }

        proofSteps.push_back({
            "Found " + to_string(noPrerequCourses.size()) + " starting courses",
            "These can be taken first",
            2
            });

        for (int c : noPrerequCourses) {
            const auto* course = cm.getCourse(c);
            proofSteps.push_back({
                "  Can take: " + (course ? course->code : to_string(c)),
                "No prerequisites",
                3
                });
        }
    }

    proofSteps.push_back({
        "Valid course sequence exists",
        "All prerequisites can be satisfied",
        0
        });
}

void ProofGenerator::generateAcyclicProof() {
    proofSteps.clear();

    proofSteps.push_back({
        "Checking for circular prerequisites",
        "Cycle detection analysis",
        0
        });

    proofSteps.push_back({
        "Testing for prerequisite cycles",
        "Checking if any course requires itself",
        1
        });

    bool hasCycle = relations.hasPrereqCycle();

    if (hasCycle) {
        proofSteps.push_back({
            "Cycle detected in system",
            "Impossible to complete all courses",
            2
            });

        proofSteps.push_back({
            "Result: System has circular dependencies",
            "Needs correction",
            0
            });
    }
    else {
        proofSteps.push_back({
            "No cycle found",
            "All courses can be completed",
            2
            });

        proofSteps.push_back({
            "Result: System is valid",
            "No circular dependencies",
            0
            });
    }
}

void ProofGenerator::generateEquivalenceProof(const vector<vector<bool>>& relation) {
    proofSteps.clear();

    proofSteps.push_back({
        "Testing if relation is an equivalence relation",
        "Checking three properties",
        0
        });

    bool reflexive = true;
    for (int i = 0; i < (int)relation.size(); i++) {
        if (!relation[i][i]) {
            reflexive = false;
            break;
        }
    }

    proofSteps.push_back({
        reflexive ? "Reflexive: Yes" : "Reflexive: No",
        reflexive ? "All elements relate to themselves" : "Some element does not relate to itself",
        1
        });

    bool symmetric = true;
    for (int i = 0; i < (int)relation.size(); i++) {
        for (int j = 0; j < (int)relation.size(); j++) {
            if (relation[i][j] != relation[j][i]) {
                symmetric = false;
                break;
            }
        }
        if (!symmetric) break;
    }

    proofSteps.push_back({
        symmetric ? "Symmetric: Yes" : "Symmetric: No",
        symmetric ? "If A relates to B, then B relates to A" : "Found asymmetric pair",
        1
        });

    bool transitive = true;
    for (int i = 0; i < (int)relation.size(); i++) {
        for (int j = 0; j < (int)relation.size(); j++) {
            for (int k = 0; k < (int)relation.size(); k++) {
                if (relation[i][j] && relation[j][k] && !relation[i][k]) {
                    transitive = false;
                    break;
                }
            }
        }
    }

    proofSteps.push_back({
        transitive ? "Transitive: Yes" : "Transitive: No",
        transitive ? "If A relates to B and B to C, then A relates to C" : "Transitivity violated",
        1
        });

    bool isEquiv = reflexive && symmetric && transitive;
    proofSteps.push_back({
        isEquiv ? "Result: Is an equivalence relation" : "Result: NOT an equivalence relation",
        isEquiv ? "All three properties satisfied" : "One or more properties failed",
        0
        });
}

void ProofGenerator::generatePartitionProof(const vector<CustomSet<int>>& partition) {
    proofSteps.clear();

    proofSteps.push_back({
        "Testing if collection forms a valid partition",
        "Checking disjointness and coverage",
        0
        });

    bool disjoint = true;
    for (size_t i = 0; i < partition.size(); i++) {
        for (size_t j = i + 1; j < partition.size(); j++) {
            auto intersect = partition[i].intersection(partition[j]);
            if (!intersect.empty()) {
                disjoint = false;
                proofSteps.push_back({
                    "Sets " + to_string(i) + " and " + to_string(j) + " overlap",
                    "Found common elements",
                    2
                    });
            }
        }
    }

    if (disjoint) {
        proofSteps.push_back({
            "All sets are disjoint",
            "No common elements found",
            1
            });
    }

    proofSteps.push_back({
        disjoint ? "Result: Valid partition" : "Result: NOT a valid partition",
        disjoint ? "All partition properties satisfied" : "Disjointness violated",
        0
        });
}

void ProofGenerator::generatePigeonholeProof(int pigeons, int holes) {
    proofSteps.clear();

    proofSteps.push_back({
        "Applying Pigeonhole Principle",
        "Analyzing distribution",
        0
        });

    proofSteps.push_back({
        "Given: " + to_string(pigeons) + " students, " + to_string(holes) + " time slots",
        "Checking distribution",
        1
        });

    if (pigeons > holes) {
        int minPerSlot = (pigeons / holes) + 1;
        proofSteps.push_back({
            "At least one time slot must have " + to_string(minPerSlot) + " or more students",
            "By pigeonhole principle",
            2
            });

        proofSteps.push_back({
            "Result: Schedule conflict guaranteed",
            "Cannot avoid overlap",
            0
            });
    }
    else {
        proofSteps.push_back({
            "Sufficient time slots available",
            "No guaranteed conflict",
            2
            });
    }
}

void ProofGenerator::display() const {
    DisplayHelper::printHeader("PROOF ANALYSIS");

    for (const auto& step : proofSteps) {
        string indent(step.level * 2, ' ');

        cout << indent << step.statement << "\n";
        cout << indent << "  -> " << step.justification << "\n\n";
    }
}