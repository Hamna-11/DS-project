#pragma once
#ifndef TESTING_H
#define TESTING_H

#include "DataStructures.h"
#include <string>

using namespace std;

class UnitTesting {
private:
    int passed;
    int failed;

    void assertTrue(bool condition, const string& testName);
    void assertEqual(int a, int b, const string& testName);

public:
    UnitTesting();
    void testFunctions();
    void testProofGenerator();
    void testConsistencyChecker();
    void testPerformanceBenchmark();
    void testRelations();
    void testLargeScale();
    void testEdgeCases();
    void testStressOperations();
    void runAllTests();
};

#endif