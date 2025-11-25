#ifndef UNIVERSITY_SYSTEM_H
#define UNIVERSITY_SYSTEM_H

#include "DiscreteStructures.h"
#include <vector>
#include <string>
#include <iostream>

// ============================================================================
// COURSE MANAGER
// ============================================================================

class CourseManager {
public:
    struct Course {
        int id;
        std::string code;
        std::string name;
        int credits;
        bool active;
        Course();
        Course(int i, std::string c, std::string n, int cr);
    };

private:
    std::vector<Course> courses;
    CustomMap<std::string, int> codeToId;

public:
    int addCourse(const std::string& code, const std::string& name, int credits);
    const Course* getCourse(int id) const;
    Course* getCourse(int id);
    int getCourseByCode(const std::string& code) const;
    int count() const;
    void listAll() const;
    const std::vector<Course>& getAllCourses() const;
};

// ============================================================================
// PEOPLE MANAGER
// ============================================================================

class PeopleManager {
public:
    struct Student {
        int id;
        std::string name;
        std::vector<int> enrolled;
        std::vector<int> completed;
        Student();
        Student(int i, std::string n);
    };

    struct Faculty {
        int id;
        std::string name;
        std::vector<int> courses;
        Faculty();
        Faculty(int i, std::string n);
    };

    struct Room {
        int id;
        std::string name;
        std::string roomNumber;
        int capacity;
        Room();
        Room(int i, std::string n, int cap = 30);
    };

private:
    std::vector<Student> students;
    std::vector<Faculty> faculties;
    std::vector<Room> rooms;

public:
    int addStudent(const std::string& name);
    int addFaculty(const std::string& name);
    int addRoom(const std::string& name, int capacity = 30);

    Student* getStudent(int id);
    Faculty* getFaculty(int id);
    Room* getRoom(int id);

    const Student* getStudent(int id) const;
    const Faculty* getFaculty(int id) const;
    const Room* getRoom(int id) const;

    int getStudentCount() const;
    int getFacultyCount() const;
    int getRoomCount() const;

    void listAllStudents() const;
    void listAllFaculties() const;
    void listAllRooms() const;
};

// ============================================================================
// PROOF GENERATOR
// ============================================================================

class ProofGenerator {
private:
    const Relations& relations;
    const CourseManager& cm;
    std::vector<std::string> proofSteps;

public:
    ProofGenerator(const Relations& r, const CourseManager& c);
    void generatePrereqProof(int courseId, const std::vector<bool>& completed);
    void generateAcyclicProof();
    void display() const;
};

// ============================================================================
// CONSISTENCY CHECKER
// ============================================================================

class ConsistencyChecker {
private:
    const CourseManager& cm;
    const PeopleManager& pm;
    const Relations& rel;
    const CustomMap<int, int>& courseToFaculty;
    const CustomMap<int, int>& courseToRoom;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;

public:
    ConsistencyChecker(const CourseManager& c, const PeopleManager& p, const Relations& r,
                       const CustomMap<int, int>& cf, const CustomMap<int, int>& cr);
    
    void runAllChecks();
    void checkPrerequisites();
    void checkEnrollments();
    void checkAssignments();
    void checkCapacity();
    void displayReport() const;
};

// ============================================================================
// PERFORMANCE BENCHMARK
// ============================================================================

class PerformanceBenchmark {
public:
    struct BenchResult {
        std::string name;
        double timeMs;
        std::string description;
    };

private:
    std::vector<BenchResult> results;

public:
    void runAllBenchmarks();
    void benchmarkSetOperations();
    void benchmarkMapOperations();
    void benchmarkRelationsClosure();
    void benchmarkFunctionComposition();
    void displayResults() const;
};

// ============================================================================
// UNIT TESTING
// ============================================================================

class UnitTesting {
private:
    int passed;
    int failed;

    void assert(bool condition, const std::string& testName);

public:
    UnitTesting();
    void runAllTests();
    void testSetOperations();
    void testMapOperations();
    void testRelations();
    void testFunctions();
    void displaySummary() const;
};

// ============================================================================
// DISPLAY UTILITIES
// ============================================================================

class DisplayHelper {
public:
    static void printHeader(const std::string& title);
    static void printSuccess(const std::string& msg);
    static void printError(const std::string& msg);
    static void printWarning(const std::string& msg);
    static void printInfo(const std::string& msg);
    static void displayMatrix(const Relations& rel, const CourseManager& cm);
    static void displayFunctionAnalysis(const CustomMap<int, int>& f, const CourseManager& cm, 
                                       PeopleManager& pm, const std::string& title);
};

#endif // UNIVERSITY_SYSTEM_H
