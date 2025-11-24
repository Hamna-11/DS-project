#pragma once
#ifndef PROOF_H
#define PROOF_H

#include "DataStructures.h"
#include <vector>
#include <string>

using namespace std;

class ProofGenerator {
private:
    const Relations& relations;
    const CourseManager& cm;

    struct ProofStep {
        string statement;
        string justification;
        int level;
    };

    vector<ProofStep> proofSteps;

public:
    ProofGenerator(const Relations& r, const CourseManager& c);
    void generatePrereqProof(int courseId, const vector<bool>& completed);
    void generateCourseChainProof(int studentId, PeopleManager& pm);
    void generateAcyclicProof();
    void generateEquivalenceProof(const vector<vector<bool>>& relation);
    void generatePartitionProof(const vector<CustomSet<int>>& partition);
    void generatePigeonholeProof(int pigeons, int holes);
    void display() const;
};


#endif