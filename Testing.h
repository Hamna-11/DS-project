#ifndef TESTING_H
#define TESTING_H

#include "DataStructures.h"
#include <string>

class UnitTesting {
private:
    int passed;
    int failed;

public:
    UnitTesting();
    void assertTrue(bool condition, const std::string& testName);
    void assertEqual(int a, int b, const std::string& testName);
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