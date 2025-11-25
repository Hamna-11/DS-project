#include "UniversitySystem.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std;

// ============================================================================
// COURSE MANAGER IMPLEMENTATION
// ============================================================================

CourseManager::Course::Course() : id(-1), credits(0), active(true) {}

CourseManager::Course::Course(int i, string c, string n, int cr)
    : id(i), code(c), name(n), credits(cr), active(true) {}

int CourseManager::addCourse(const string& code, const string& name, int credits) {
    if (codeToId.contains(code)) {
        cout << "[ERROR] Course code already exists!\n";
        return -1;
    }
    int id = static_cast<int>(courses.size());
    courses.push_back(Course(id, code, name, credits));
    codeToId.insert(code, id);
    cout << "[SUCCESS] Added course: " << code << "\n";
    return id;
}

const CourseManager::Course* CourseManager::getCourse(int id) const {
    if (id < 0 || id >= static_cast<int>(courses.size())) return nullptr;
    return &courses[id];
}

CourseManager::Course* CourseManager::getCourse(int id) {
    if (id < 0 || id >= static_cast<int>(courses.size())) return nullptr;
    return &courses[id];
}

int CourseManager::getCourseByCode(const string& code) const {
    const int* id = codeToId.get(code);
    return id ? *id : -1;
}

int CourseManager::count() const {
    return static_cast<int>(courses.size());
}

void CourseManager::listAll() const {
    cout << "\n" << string(60, '=') << "\n";
    cout << "  ALL COURSES\n";
    cout << string(60, '=') << "\n\n";
    cout << left << setw(5) << "ID" << setw(12) << "Code"
        << setw(25) << "Name" << "Credits\n";
    cout << string(60, '-') << "\n";
    for (const auto& c : courses) {
        cout << left << setw(5) << c.id << setw(12) << c.code
            << setw(25) << c.name << c.credits << "\n";
    }
    cout << "\nTotal Courses: " << courses.size() << "\n";
}

const vector<CourseManager::Course>& CourseManager::getAllCourses() const {
    return courses;
}

// ============================================================================
// PEOPLE MANAGER IMPLEMENTATION
// ============================================================================

PeopleManager::Student::Student() : id(-1) {}
PeopleManager::Student::Student(int i, string n) : id(i), name(n) {}

PeopleManager::Faculty::Faculty() : id(-1) {}
PeopleManager::Faculty::Faculty(int i, string n) : id(i), name(n) {}

PeopleManager::Room::Room() : id(-1), capacity(0) {}
PeopleManager::Room::Room(int i, string n, int cap)
    : id(i), name(n), roomNumber(n), capacity(cap) {}

int PeopleManager::addStudent(const string& name) {
    int id = static_cast<int>(students.size());
    students.push_back(Student(id, name));
    cout << "[SUCCESS] Added student: " << name << "\n";
    return id;
}

int PeopleManager::addFaculty(const string& name) {
    int id = static_cast<int>(faculties.size());
    faculties.push_back(Faculty(id, name));
    cout << "[SUCCESS] Added faculty: " << name << "\n";
    return id;
}

int PeopleManager::addRoom(const string& name, int capacity) {
    int id = static_cast<int>(rooms.size());
    rooms.push_back(Room(id, name, capacity));
    cout << "[SUCCESS] Added room: " << name << "\n";
    return id;
}

PeopleManager::Student* PeopleManager::getStudent(int id) {
    if (id < 0 || id >= static_cast<int>(students.size())) return nullptr;
    return &students[id];
}

PeopleManager::Faculty* PeopleManager::getFaculty(int id) {
    if (id < 0 || id >= static_cast<int>(faculties.size())) return nullptr;
    return &faculties[id];
}

PeopleManager::Room* PeopleManager::getRoom(int id) {
    if (id < 0 || id >= static_cast<int>(rooms.size())) return nullptr;
    return &rooms[id];
}

const PeopleManager::Student* PeopleManager::getStudent(int id) const {
    if (id < 0 || id >= static_cast<int>(students.size())) return nullptr;
    return &students[id];
}

const PeopleManager::Faculty* PeopleManager::getFaculty(int id) const {
    if (id < 0 || id >= static_cast<int>(faculties.size())) return nullptr;
    return &faculties[id];
}

const PeopleManager::Room* PeopleManager::getRoom(int id) const {
    if (id < 0 || id >= static_cast<int>(rooms.size())) return nullptr;
    return &rooms[id];
}

int PeopleManager::getStudentCount() const {
    return static_cast<int>(students.size());
}

int PeopleManager::getFacultyCount() const {
    return static_cast<int>(faculties.size());
}

int PeopleManager::getRoomCount() const {
    return static_cast<int>(rooms.size());
}

void PeopleManager::listAllStudents() const {
    cout << "\n" << string(60, '=') << "\n";
    cout << "  ALL STUDENTS\n";
    cout << string(60, '=') << "\n\n";
    cout << left << setw(5) << "ID" << setw(30) << "Name" << "Enrolled\n";
    cout << string(60, '-') << "\n";
    for (const auto& s : students) {
        cout << left << setw(5) << s.id << setw(30) << s.name
            << s.enrolled.size() << " courses\n";
    }
    cout << "\nTotal Students: " << students.size() << "\n";
}

void PeopleManager::listAllFaculties() const {
    cout << "\n" << string(60, '=') << "\n";
    cout << "  ALL FACULTY\n";
    cout << string(60, '=') << "\n\n";
    cout << left << setw(5) << "ID" << setw(30) << "Name" << "Courses\n";
    cout << string(60, '-') << "\n";
    for (const auto& f : faculties) {
        cout << left << setw(5) << f.id << setw(30) << f.name
            << f.courses.size() << " courses\n";
    }
    cout << "\nTotal Faculty: " << faculties.size() << "\n";
}

void PeopleManager::listAllRooms() const {
    cout << "\n" << string(60, '=') << "\n";
    cout << "  ALL ROOMS\n";
    cout << string(60, '=') << "\n\n";
    cout << left << setw(5) << "ID" << setw(20) << "Room" << "Capacity\n";
    cout << string(60, '-') << "\n";
    for (const auto& r : rooms) {
        cout << left << setw(5) << r.id << setw(20) << r.roomNumber
            << r.capacity << "\n";
    }
    cout << "\nTotal Rooms: " << rooms.size() << "\n";
}

// ============================================================================
// PROOF GENERATOR IMPLEMENTATION
// ============================================================================

ProofGenerator::ProofGenerator(const Relations& r, const CourseManager& c)
    : relations(r), cm(c) {}

void ProofGenerator::generatePrereqProof(int courseId, const vector<bool>& completed) {
    proofSteps.clear();
    
    const auto* course = cm.getCourse(courseId);
    string courseName = course ? course->code : to_string(courseId);
    
    proofSteps.push_back("Theorem: Can student enroll in " + courseName + "?");
    proofSteps.push_back("Proof by checking prerequisites:");
    
    auto prereq = relations.getPrereqMatrix();
    bool hasDirectPrereq = false;
    
    for (int i = 0; i < static_cast<int>(prereq.size()); i++) {
        if (prereq[i][courseId]) {
            hasDirectPrereq = true;
            const auto* p = cm.getCourse(i);
            string pName = p ? p->code : to_string(i);
            
            if (i < static_cast<int>(completed.size()) && completed[i]) {
                proofSteps.push_back("  - Prerequisite " + pName + " is completed [OK]");
            } else {
                proofSteps.push_back("  - Prerequisite " + pName + " is NOT completed [FAIL]");
            }
        }
    }
    
    if (!hasDirectPrereq) {
        proofSteps.push_back("  - No prerequisites required");
    }
    
    auto closure = relations.closurePrereq();
    bool allSatisfied = true;
    for (int i = 0; i < static_cast<int>(closure.size()); i++) {
        if (closure[i][courseId] && (i >= static_cast<int>(completed.size()) || !completed[i])) {
            allSatisfied = false;
            break;
        }
    }
    
    proofSteps.push_back(allSatisfied ? "Conclusion: Enrollment ALLOWED" : "Conclusion: Enrollment DENIED");
}

void ProofGenerator::generateAcyclicProof() {
    proofSteps.clear();
    
    proofSteps.push_back("Theorem: The prerequisite graph is acyclic");
    proofSteps.push_back("Proof by contradiction:");
    
    bool hasCycle = relations.hasPrereqCycle();
    
    if (hasCycle) {
        proofSteps.push_back("  - Found course requiring itself transitively");
        proofSteps.push_back("  - This creates a circular dependency");
        proofSteps.push_back("Conclusion: Graph has cycles [INVALID]");
    } else {
        proofSteps.push_back("  - No course requires itself");
        proofSteps.push_back("  - No circular dependencies found");
        proofSteps.push_back("Conclusion: Graph is acyclic [VALID]");
    }
}

void ProofGenerator::display() const {
    cout << "\n" << string(60, '=') << "\n";
    cout << "  FORMAL PROOF\n";
    cout << string(60, '=') << "\n\n";
    for (const auto& step : proofSteps) {
        cout << step << "\n";
    }
    cout << "\n";
}

// ============================================================================
// CONSISTENCY CHECKER IMPLEMENTATION
// ============================================================================

ConsistencyChecker::ConsistencyChecker(const CourseManager& c, const PeopleManager& p,
                                       const Relations& r, const CustomMap<int, int>& cf,
                                       const CustomMap<int, int>& cr)
    : cm(c), pm(p), rel(r), courseToFaculty(cf), courseToRoom(cr) {}

void ConsistencyChecker::runAllChecks() {
    errors.clear();
    warnings.clear();
    checkPrerequisites();
    checkEnrollments();
    checkAssignments();
    checkCapacity();
}

void ConsistencyChecker::checkPrerequisites() {
    if (rel.hasPrereqCycle()) {
        errors.push_back("Prerequisite cycle detected!");
    }
}

void ConsistencyChecker::checkEnrollments() {
    auto closure = rel.closurePrereq();
    
    for (int s = 0; s < pm.getStudentCount(); s++) {
        const auto* student = pm.getStudent(s);
        if (!student) continue;
        
        CustomSet<int> enrolled;
        for (int x : student->enrolled) enrolled.insert(x);
        
        for (int courseId : student->enrolled) {
            for (int i = 0; i < static_cast<int>(closure.size()); i++) {
                if (closure[i][courseId] && !enrolled.contains(i)) {
                    const auto* c = cm.getCourse(courseId);
                    const auto* p = cm.getCourse(i);
                    
                    stringstream ss;
                    ss << student->name << " missing prerequisite "
                       << (p ? p->code : to_string(i)) << " for "
                       << (c ? c->code : to_string(courseId));
                    errors.push_back(ss.str());
                }
            }
        }
        
        if (student->enrolled.size() > 6) {
            stringstream ss;
            ss << student->name << " enrolled in " << student->enrolled.size()
               << " courses (overload)";
            warnings.push_back(ss.str());
        }
    }
}

void ConsistencyChecker::checkAssignments() {
    for (int i = 0; i < cm.count(); i++) {
        if (!courseToFaculty.contains(i)) {
            const auto* c = cm.getCourse(i);
            stringstream ss;
            ss << (c ? c->code : to_string(i)) << " has no faculty assigned";
            warnings.push_back(ss.str());
        }
        
        if (!courseToRoom.contains(i)) {
            const auto* c = cm.getCourse(i);
            stringstream ss;
            ss << (c ? c->code : to_string(i)) << " has no room assigned";
            warnings.push_back(ss.str());
        }
    }
}

void ConsistencyChecker::checkCapacity() {
    for (const auto& pair : courseToRoom) {
        const auto* r = pm.getRoom(pair.second);
        if (!r) continue;
        
        int enrolled = 0;
        for (int s = 0; s < pm.getStudentCount(); s++) {
            const auto* student = pm.getStudent(s);
            if (student) {
                if (find(student->enrolled.begin(), student->enrolled.end(), pair.first)
                    != student->enrolled.end()) {
                    enrolled++;
                }
            }
        }
        
        if (enrolled > r->capacity) {
            const auto* c = cm.getCourse(pair.first);
            stringstream ss;
            ss << (c ? c->code : to_string(pair.first)) << " has " << enrolled
               << " students but room capacity is " << r->capacity;
            errors.push_back(ss.str());
        }
    }
}

void ConsistencyChecker::displayReport() const {
    cout << "\n" << string(60, '=') << "\n";
    cout << "  CONSISTENCY CHECK REPORT\n";
    cout << string(60, '=') << "\n\n";
    
    if (errors.empty() && warnings.empty()) {
        cout << "[SUCCESS] No issues found!\n";
    } else {
        if (!errors.empty()) {
            cout << "ERRORS (" << errors.size() << "):\n";
            for (const auto& err : errors) {
                cout << "  [ERROR] " << err << "\n";
            }
            cout << "\n";
        }
        
        if (!warnings.empty()) {
            cout << "WARNINGS (" << warnings.size() << "):\n";
            for (const auto& warn : warnings) {
                cout << "  [WARNING] " << warn << "\n";
            }
            cout << "\n";
        }
    }
}

// ============================================================================
// PERFORMANCE BENCHMARK IMPLEMENTATION
// ============================================================================

void PerformanceBenchmark::runAllBenchmarks() {
    results.clear();
    cout << "\n" << string(60, '=') << "\n";
    cout << "  PERFORMANCE BENCHMARKING\n";
    cout << string(60, '=') << "\n\n";
    
    benchmarkSetOperations();
    benchmarkMapOperations();
    benchmarkRelationsClosure();
    benchmarkFunctionComposition();
    
    displayResults();
}

void PerformanceBenchmark::benchmarkSetOperations() {
    auto start = chrono::high_resolution_clock::now();
    
    CustomSet<int> a, b;
    for (int i = 0; i < 1000; i++) a.insert(i);
    for (int i = 500; i < 1500; i++) b.insert(i);
    
    auto result = SetOps::setUnion(a, b);
    auto intersection = SetOps::setIntersection(a, b);
    
    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration<double, milli>(end - start).count();
    
    results.push_back({"Set Operations", time, "Union and intersection of 1000-element sets"});
}

void PerformanceBenchmark::benchmarkMapOperations() {
    auto start = chrono::high_resolution_clock::now();
    
    CustomMap<int, int> map;
    for (int i = 0; i < 1000; i++) {
        map.insert(i, i * 2);
    }
    
    for (int i = 0; i < 1000; i++) {
        map.get(i);
    }
    
    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration<double, milli>(end - start).count();
    
    results.push_back({"Map Operations", time, "1000 insertions and 1000 lookups"});
}

void PerformanceBenchmark::benchmarkRelationsClosure() {
    auto start = chrono::high_resolution_clock::now();
    
    Relations rel;
    for (int i = 0; i < 100; i++) {
        for (int j = i + 1; j < min(i + 5, 100); j++) {
            rel.addPrereq(i, j);
        }
    }
    
    auto closure = rel.closurePrereq();
    
    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration<double, milli>(end - start).count();
    
    results.push_back({"Transitive Closure", time, "Floyd-Warshall on 100x100 matrix"});
}

void PerformanceBenchmark::benchmarkFunctionComposition() {
    auto start = chrono::high_resolution_clock::now();
    
    CustomMap<int, int> f, g;
    for (int i = 0; i < 100; i++) {
        f.insert(i, (i * 2) % 100);
        g.insert(i, (i + 50) % 100);
    }
    
    auto composed = Functions::compose(f, g);
    
    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration<double, milli>(end - start).count();
    
    results.push_back({"Function Composition", time, "Composing two 100-element functions"});
}

void PerformanceBenchmark::displayResults() const {
    cout << "\nBenchmark Results:\n";
    cout << left << setw(30) << "Test" << setw(15) << "Time (ms)" << "Description\n";
    cout << string(60, '-') << "\n";
    
    for (const auto& r : results) {
        cout << left << setw(30) << r.name
             << setw(15) << fixed << setprecision(3) << r.timeMs
             << r.description << "\n";
    }
    cout << "\n";
}

// ============================================================================
// UNIT TESTING IMPLEMENTATION
// ============================================================================

UnitTesting::UnitTesting() : passed(0), failed(0) {}

void UnitTesting::assert(bool condition, const string& testName) {
    if (condition) {
        cout << "  [PASS] " << testName << "\n";
        passed++;
    } else {
        cout << "  [FAIL] " << testName << "\n";
        failed++;
    }
}

void UnitTesting::runAllTests() {
    passed = 0;
    failed = 0;
    
    cout << "\n" << string(60, '=') << "\n";
    cout << "  UNIT TESTING\n";
    cout << string(60, '=') << "\n\n";
    
    testSetOperations();
    testMapOperations();
    testRelations();
    testFunctions();
    
    displaySummary();
}

void UnitTesting::testSetOperations() {
    cout << "Testing Set Operations:\n";
    
    CustomSet<int> a, b;
    a.insert(1); a.insert(2); a.insert(3);
    b.insert(2); b.insert(3); b.insert(4);
    
    assert(a.size() == 3, "Set size");
    assert(a.contains(2), "Set contains");
    assert(!a.contains(5), "Set not contains");
    
    auto un = SetOps::setUnion(a, b);
    assert(un.size() == 4, "Set union size");
    
    auto inter = SetOps::setIntersection(a, b);
    assert(inter.size() == 2, "Set intersection size");
    
    cout << "\n";
}

void UnitTesting::testMapOperations() {
    cout << "Testing Map Operations:\n";
    
    CustomMap<int, int> map;
    map.insert(1, 10);
    map.insert(2, 20);
    
    assert(map.size() == 2, "Map size");
    assert(map.contains(1), "Map contains key");
    assert(!map.contains(3), "Map not contains key");
    
    const int* val = map.get(1);
    assert(val != nullptr && *val == 10, "Map get value");
    
    cout << "\n";
}

void UnitTesting::testRelations() {
    cout << "Testing Relations:\n";
    
    Relations rel;
    rel.addPrereq(0, 1);
    rel.addPrereq(1, 2);
    
    assert(rel.getPrereq(0, 1), "Direct prerequisite");
    assert(!rel.getPrereq(0, 2), "No direct prerequisite");
    
    auto closure = rel.closurePrereq();
    assert(closure[0][2], "Transitive prerequisite");
    
    assert(!rel.hasPrereqCycle(), "No cycle");
    
    cout << "\n";
}

void UnitTesting::testFunctions() {
    cout << "Testing Functions:\n";
    
    CustomMap<int, int> f;
    f.insert(0, 1);
    f.insert(1, 2);
    f.insert(2, 0);
    
    assert(Functions::isInjective(f), "Function is injective");
    assert(Functions::isSurjective(f, 3), "Function is surjective");
    assert(Functions::isBijective(f, 3), "Function is bijective");
    
    cout << "\n";
}

void UnitTesting::displaySummary() const {
    cout << string(60, '=') << "\n";
    cout << "Test Summary:\n";
    cout << "  Passed: " << passed << "\n";
    cout << "  Failed: " << failed << "\n";
    cout << "  Total:  " << (passed + failed) << "\n";
    
    if (failed == 0) {
        cout << "\n[SUCCESS] All tests passed!\n";
    } else {
        cout << "\n[WARNING] Some tests failed!\n";
    }
    cout << "\n";
}

// ============================================================================
// DISPLAY UTILITIES IMPLEMENTATION
// ============================================================================

void DisplayHelper::printHeader(const string& title) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "  " << title << "\n";
    cout << string(60, '=') << "\n";
}

void DisplayHelper::printSuccess(const string& msg) {
    cout << "[SUCCESS] " << msg << "\n";
}

void DisplayHelper::printError(const string& msg) {
    cout << "[ERROR] " << msg << "\n";
}

void DisplayHelper::printWarning(const string& msg) {
    cout << "[WARNING] " << msg << "\n";
}

void DisplayHelper::printInfo(const string& msg) {
    cout << "[INFO] " << msg << "\n";
}

void DisplayHelper::displayMatrix(const Relations& rel, const CourseManager& cm) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "  PREREQUISITE MATRIX\n";
    cout << string(60, '=') << "\n\n";
    
    int size = rel.getSize();
    cout << "   ";
    for (int i = 0; i < size; i++) {
        const auto* c = cm.getCourse(i);
        cout << setw(6) << (c ? c->code : to_string(i));
    }
    cout << "\n";
    
    auto matrix = rel.getPrereqMatrix();
    for (int i = 0; i < size; i++) {
        const auto* c = cm.getCourse(i);
        cout << setw(3) << (c ? c->code : to_string(i));
        for (int j = 0; j < size; j++) {
            cout << setw(6) << (matrix[i][j] ? "Y" : ".");
        }
        cout << "\n";
    }
    cout << "\n";
}

void DisplayHelper::displayFunctionAnalysis(const CustomMap<int, int>& f, const CourseManager& cm,
                                           PeopleManager& pm, const string& title) {
    printHeader(title);
    
    cout << "\nMappings: " << f.size() << "\n";
    cout << "Injective: " << (Functions::isInjective(f) ? "YES" : "NO") << "\n";
    
    cout << "\nDetails:\n";
    for (const auto& pair : f) {
        const auto* c = cm.getCourse(pair.first);
        auto* fac = pm.getFaculty(pair.second);
        cout << "  " << (c ? c->code : to_string(pair.first)) << " -> "
             << (fac ? fac->name : to_string(pair.second)) << "\n";
    }
    cout << "\n";
}
