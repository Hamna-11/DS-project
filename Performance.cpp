#include "Performance.h"
#include "Functions.h"
#include "Consistency.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

long long PerformanceBenchmark::getTimeMillis() {
    return clock() * 1000 / CLOCKS_PER_SEC;
}

void PerformanceBenchmark::benchmarkTransitiveClosure(Relations& rel, int size) {
    rel.ensureSize(size);

    for (int i = 0; i < size - 1; i++) {
        rel.addPrereq(i, i + 1);
    }

    long long time = measure([&]() {
        rel.closurePrereq();
        });

    results.push_back({ "Transitive Closure (Standard)", time, size });
}

void PerformanceBenchmark::benchmarkBitsetClosure(OptimizedRelations& rel, int size) {
    rel.ensureSize(size);

    for (int i = 0; i < size - 1; i++) {
        rel.addPrereq(i, i + 1);
    }

    long long time = measure([&]() {
        rel.closurePrereq();
        });

    results.push_back({ "Transitive Closure (Optimized)", time, size });
}

bool PerformanceBenchmark::canTakeCourseRecursive(int student, int course, const Relations& rel,
    PeopleManager& pm, const vector<int>& completed) {
    if (cache.hasPrereqCached(student, course)) {
        return cache.getPrereqCached(student, course);
    }

    if (find(completed.begin(), completed.end(), course) != completed.end()) {
        cache.cachePrereq(student, course, true);
        return true;
    }

    auto matrix = rel.getPrereqMatrix();
    for (int i = 0; i < rel.getSize(); i++) {
        if (matrix[i][course]) {
            if (!canTakeCourseRecursive(student, i, rel, pm, completed)) {
                cache.cachePrereq(student, course, false);
                return false;
            }
        }
    }

    cache.cachePrereq(student, course, true);
    return true;
}

void PerformanceBenchmark::benchmarkRecursiveMemoization(Relations& rel, PeopleManager& pm, int size) {
    rel.ensureSize(size);
    for (int i = 0; i < size - 1; i++) {
        rel.addPrereq(i, i + 1);
    }

    vector<int> completed;
    for (int i = 0; i < size / 2; i++) {
        completed.push_back(i);
    }

    cache.clearAll();

    long long time = measure([&]() {
        for (int c = 0; c < size; c++) {
            canTakeCourseRecursive(0, c, rel, pm, completed);
        }
        });

    results.push_back({ "Prerequisite Check (Memoized)", time, size });
}

void PerformanceBenchmark::benchmarkFunctionChecks(int size) {
    CustomMap<int, int> f;
    for (int i = 0; i < size; i++) {
        f.insert(i, i % (size / 2));
    }

    long long time = measure([&]() {
        Functions::isInjective(f);
        Functions::isSurjective(f, size);
        Functions::isBijective(f, size);
        });

    results.push_back({ "Function Property Checks", time, size });
}

void PerformanceBenchmark::benchmarkConsistencyChecks(CourseManager& cm, PeopleManager& pm,
    Relations& rel, int size) {
    for (int i = 0; i < size; i++) {
        cm.addCourse("CS" + to_string(i), "Course" + to_string(i), 3);
        pm.addStudent("Student" + to_string(i));
    }

    CustomMap<int, int> cf, cr;
    ConsistencyChecker checker(cm, pm, rel, cf, cr);

    long long time = measure([&]() {
        checker.runAllChecks();
        });

    results.push_back({ "Consistency Checks", time, size });
}

void PerformanceBenchmark::runAllBenchmarks() {
    DisplayHelper::printHeader("PERFORMANCE BENCHMARKING");

    cout << "\nRunning benchmarks...\n\n";

    Relations rel1, rel2, rel3, rel4;
    OptimizedRelations optRel1, optRel2;

    benchmarkTransitiveClosure(rel1, 10);
    benchmarkTransitiveClosure(rel2, 20);
    benchmarkTransitiveClosure(rel3, 50);

    benchmarkBitsetClosure(optRel1, 50);
    benchmarkBitsetClosure(optRel2, 100);

    PeopleManager pm;
    benchmarkRecursiveMemoization(rel4, pm, 30);

    benchmarkFunctionChecks(100);
    benchmarkFunctionChecks(500);
    benchmarkFunctionChecks(1000);

    CourseManager cm;
    PeopleManager pm2;
    Relations rel5;
    benchmarkConsistencyChecks(cm, pm2, rel5, 20);

    displayResults();
    cache.displayStats();
}

void PerformanceBenchmark::displayResults() const {
    DisplayHelper::printHeader("BENCHMARK RESULTS");

    cout << "\n" << left << setw(40) << "Operation"
        << setw(12) << "Time (ms)"
        << "Data Size\n";
    cout << string(65, '-') << "\n";

    for (const auto& r : results) {
        cout << left << setw(40) << r.operation
            << setw(12) << r.milliseconds
            << r.dataSize << "\n";
    }
    cout << "\n";

}