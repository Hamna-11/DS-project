#pragma once
#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include "DataStructures.h"
#include <vector>
#include <string>

using namespace std;

class PerformanceBenchmark {
private:
    struct BenchResult {
        string operation;
        long long milliseconds;
        int dataSize;
    };

    vector<BenchResult> results;
    MemoizationCache cache;

    long long getTimeMillis();

public:
    template<typename Func>
    long long measure(Func f) {
        long long start = getTimeMillis();
        f();
        long long end = getTimeMillis();
        return end - start;
    }

    void benchmarkTransitiveClosure(Relations& rel, int size);
    void benchmarkBitsetClosure(OptimizedRelations& rel, int size);
    bool canTakeCourseRecursive(int student, int course, const Relations& rel,
        PeopleManager& pm, const vector<int>& completed);
    void benchmarkRecursiveMemoization(Relations& rel, PeopleManager& pm, int size);
    void benchmarkFunctionChecks(int size);
    void benchmarkConsistencyChecks(CourseManager& cm, PeopleManager& pm,
        Relations& rel, int size);
    void runAllBenchmarks();
    void displayResults() const;

};

#endif