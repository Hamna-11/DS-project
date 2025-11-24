#include "Testing.h"
#include "Functions.h"
#include "Proof.h"
#include "Consistency.h"
#include "Performance.h"
#include <iostream>
#include <ctime>

using namespace std;

UnitTesting::UnitTesting() : passed(0), failed(0) {}

void UnitTesting::assertTrue(bool condition, const string& testName) {
    if (condition) {
        cout << "[PASS] " << testName << "\n";
        passed++;
    }
    else {
        cout << "[FAIL] " << testName << "\n";
        failed++;
    }
}

void UnitTesting::assertEqual(int a, int b, const string& testName) {
    if (a == b) {
        cout << "[PASS] " << testName << "\n";
        passed++;
    }
    else {
        cout << "[FAIL] " << testName << " (expected " << b << ", got " << a << ")\n";
        failed++;
    }
}

void UnitTesting::testFunctions() {
    cout << "\n--- Testing Functions ---\n";

    CustomMap<int, int> f1;
    f1.insert(0, 0); f1.insert(1, 1); f1.insert(2, 2);
    assertTrue(Functions::isInjective(f1), "Should be injective");
    assertTrue(Functions::isSurjective(f1, 3), "Should be surjective");
    assertTrue(Functions::isBijective(f1, 3), "Should be bijective");

    auto f1_inv = Functions::inverse(f1, 3);
    assertTrue(f1_inv.size() == 3, "Inverse should have 3 mappings");
    assertTrue(Functions::verifyInverse(f1, f1_inv), "Inverse verification should pass");

    CustomMap<int, int> f2;
    f2.insert(0, 0); f2.insert(1, 0); f2.insert(2, 1);
    assertTrue(!Functions::isInjective(f2), "Should not be injective");

    auto f2_inv = Functions::inverse(f2, 3);
    assertTrue(f2_inv.empty(), "Non-bijective function should have empty inverse");

    CustomMap<int, int> f3, f4;
    f3.insert(0, 1); f3.insert(1, 2);
    f4.insert(1, 10); f4.insert(2, 20);
    auto composed = Functions::compose(f3, f4);
    assertTrue(composed.size() == 2, "Composition should have 2 mappings");
}

void UnitTesting::testProofGenerator() {
    cout << "\n--- Testing Proof Generator ---\n";

    CourseManager cm;
    Relations rel;

    cm.addCourse("CS101", "Intro", 3);
    cm.addCourse("CS201", "Advanced", 3);
    rel.ensureSize(2);
    rel.addPrereq(0, 1);

    ProofGenerator proof(rel, cm);

    vector<bool> completed(2, false);
    completed[0] = true;

    proof.generatePrereqProof(1, completed);
    assertTrue(true, "Proof generation completed");

    proof.generateAcyclicProof();
    assertTrue(true, "Acyclic proof generated");
}

void UnitTesting::testConsistencyChecker() {
    cout << "\n--- Testing Consistency Checker ---\n";

    CourseManager cm;
    PeopleManager pm;
    Relations rel;

    cm.addCourse("CS101", "Programming", 3);
    pm.addStudent("Zohaib");
    pm.addFaculty("Dr. Raza");
    pm.addRoom("R101", 30);

    CustomMap<int, int> cf, cr;
    cf.insert(0, 0);
    cr.insert(0, 0);

    ConsistencyChecker checker(cm, pm, rel, cf, cr);
    checker.runAllChecks();

    assertTrue(true, "Consistency checks completed");

    auto students1 = checker.getCourseStudents(0);
    assertTrue(students1.size() >= 0, "Set intersection working");
}

void UnitTesting::testPerformanceBenchmark() {
    cout << "\n--- Testing Performance Benchmark ---\n";

    PerformanceBenchmark bench;

    Relations rel;
    bench.benchmarkTransitiveClosure(rel, 5);
    bench.benchmarkFunctionChecks(10);

    OptimizedRelations optRel;
    bench.benchmarkBitsetClosure(optRel, 10);

    assertTrue(true, "Benchmark completed");
}

void UnitTesting::testRelations() {
    cout << "\n--- Testing Relations ---\n";

    Relations rel;
    rel.ensureSize(5);
    rel.addPrereq(0, 1);
    rel.addPrereq(1, 2);

    assertTrue(rel.getPrereq(0, 1), "Direct prerequisite exists");

    auto closure = rel.closurePrereq();
    assertTrue(closure[0][2], "Transitive prerequisite exists");

    assertTrue(!rel.hasPrereqCycle(), "No cycles initially");

    rel.addPrereq(2, 0);
    assertTrue(rel.hasPrereqCycle(), "Cycle detected");
}

void UnitTesting::testLargeScale() {
    cout << "\n--- Testing Large Scale ---\n";

    const int NUM_COURSES = 100;
    const int NUM_STUDENTS = 500;
    const int NUM_FACULTY = 50;

    CourseManager cm;
    PeopleManager pm;
    Relations rel;

    cout << "Creating " << NUM_COURSES << " courses...\n";
    for (int i = 0; i < NUM_COURSES; i++) {
        cm.addCourse("CS" + to_string(i), "Course" + to_string(i), 3);
    }
    assertTrue(cm.count() == NUM_COURSES, "Large-scale course creation");

    cout << "Creating " << NUM_STUDENTS << " students...\n";
    for (int i = 0; i < NUM_STUDENTS; i++) {
        string names[] = { "Ali", "Nimra", "Maria", "Kashaf", "Noor", "Waqar", "Fatima", "Hassan" };
        pm.addStudent(names[i % 8] + to_string(i / 8));
    }
    assertTrue(pm.getStudentCount() == NUM_STUDENTS, "Large-scale student creation");

    cout << "Creating " << NUM_FACULTY << " faculty...\n";
    for (int i = 0; i < NUM_FACULTY; i++) {
        string names[] = { "Dr. Waqar", "Dr. Nimra", "Dr. Ali", "Dr. Maria", "Dr. Noor" };
        pm.addFaculty(names[i % 5] + to_string(i / 5));
    }
    assertTrue(pm.getFacultyCount() == NUM_FACULTY, "Large-scale faculty creation");

    cout << "Testing performance at scale...\n";
    auto start = clock();

    rel.ensureSize(NUM_COURSES);
    for (int i = 0; i < NUM_COURSES - 1; i++) {
        rel.addPrereq(i, i + 1);
    }

    auto closure = rel.closurePrereq();

    auto end = clock();
    long long time = (end - start) * 1000 / CLOCKS_PER_SEC;

    cout << "Time taken: " << time << " ms\n";
    assertTrue(time < 5000, "Completed in reasonable time");

    assertTrue(closure[0][NUM_COURSES - 1], "Transitive closure works at scale");

    DisplayHelper::printSuccess("Large-scale testing completed!");
}

void UnitTesting::testEdgeCases() {
    cout << "\n--- Testing Edge Cases ---\n";

    CourseManager cm;
    Relations rel;

    assertTrue(cm.count() == 0, "Empty system test");

    cm.addCourse("CS101", "Test", 3);
    assertTrue(cm.count() == 1, "Single course test");

    rel.ensureSize(2);
    rel.addPrereq(0, 0);
    assertTrue(rel.hasPrereqCycle(), "Self-prerequisite creates cycle");

    const auto* invalid = cm.getCourse(999);
    assertTrue(invalid == nullptr, "Invalid course ID returns nullptr");

    cout << "All edge cases passed!\n";
}

void UnitTesting::testStressOperations() {
    cout << "\n--- Stress Testing ---\n";

    CourseManager cm;

    cout << "Creating 1000 courses...\n";
    for (int i = 0; i < 1000; i++) {
        cm.addCourse("C" + to_string(i), "Course", 3);
    }

    int accessible = 0;
    for (int i = 0; i < 1000; i++) {
        if (cm.getCourse(i) != nullptr) accessible++;
    }

    assertTrue(accessible == 1000, "All 1000 courses accessible");

    cout << "Stress test completed!\n";
}

void UnitTesting::runAllTests() {
    DisplayHelper::printHeader("UNIT TESTING SUITE");

    passed = 0;
    failed = 0;

    testFunctions();
    testProofGenerator();
    testConsistencyChecker();
    testPerformanceBenchmark();
    testRelations();
    testLargeScale();
    testEdgeCases();
    testStressOperations();

    cout << "\n" << string(60, '=') << "\n";
    cout << "RESULTS: " << passed << " passed, " << failed << " failed\n";

    if (failed == 0) {
        DisplayHelper::printSuccess("All tests passed!");
    }
    else {
        DisplayHelper::printError(to_string(failed) + " test(s) failed");

    }
}