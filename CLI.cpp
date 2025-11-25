#include "CLI.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

// ---------- Helper printing functions ----------
static void printHeader(const string& title) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "  " << title << "\n";
    cout << string(60, '=') << "\n";
}

static void printSuccess(const string& msg) {
    cout << "\n[SUCCESS] " << msg << "\n";
}

static void printError(const string& msg) {
    cout << "\n[ERROR] " << msg << "\n";
}

// ---------- Small console helpers (local to cpp) ----------
static void clearInputBuffer() {
    cin.clear();
    while (cin.get() != '\n' && !cin.eof());
}

static void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// ---------- Constructor ----------
CLIInterface::CLIInterface(CourseManager& c, PeopleManager& p, Relations& r,
    CustomMap<int, int>& cf, CustomMap<int, int>& cr)
    : cm(c), pm(p), rel(r), courseToFaculty(cf), courseToRoom(cr), facultyToRoom()
{
}

// ---------- Methods ----------
void CLIInterface::showWelcome() {
    printHeader("FAST UNIVERSITY MANAGEMENT SYSTEM");
    cout << "\n  Welcome to the Advanced University Management System\n";
    cout << "  Powered by Discrete Mathematics Concepts\n";
    cout << "\n  Available Modules:\n";
    cout << "  - Functions & Mappings\n";
    cout << "  - Automated Proof Generation\n";
    cout << "  - Consistency Checking\n";
    cout << "  - Performance Benchmarking\n";
    cout << "  - Comprehensive Unit Testing\n\n";
}

void CLIInterface::displayStatistics() {
    printHeader("SYSTEM STATISTICS");

    cout << "\nCurrent System Status:\n";
    cout << "  Total Courses:  " << cm.count() << "\n";
    cout << "  Total Students: " << pm.getStudentCount() << "\n";
    cout << "  Total Faculty:  " << pm.getFacultyCount() << "\n";
    cout << "  Total Rooms:    " << pm.getRoomCount() << "\n";

    int totalPrereqs = 0;
    for (int i = 0; i < rel.getSize(); i++) {
        for (int j = 0; j < rel.getSize(); j++) {
            if (rel.getPrereq(i, j)) totalPrereqs++;
        }
    }
    cout << "  Prerequisites:  " << totalPrereqs << "\n";

    cout << "\nAssignments:\n";
    cout << "  Course-Faculty: " << courseToFaculty.size() << " mappings\n";
    cout << "  Course-Room:    " << courseToRoom.size() << " mappings\n";

    int totalEnrollments = 0;
    for (int i = 0; i < pm.getStudentCount(); i++) {
        auto* s = pm.getStudent(i);
        if (s) totalEnrollments += static_cast<int>(s->enrolled.size());
    }
    cout << "  Enrollments:    " << totalEnrollments << " total\n";
    cout << "\n";
}

void CLIInterface::quickSetup() {
    printHeader("QUICK SETUP WIZARD");

    cout << "\nThis will create sample data for testing.\n";
    cout << "Continue? (y/n): ";
    char confirm;
    cin >> confirm;
    clearInputBuffer();

    if (confirm != 'y' && confirm != 'Y') return;

    cout << "\nCreating sample courses...\n";
    cm.addCourse("CS101", "Programming", 3);
    cm.addCourse("CS102", "DataStructures", 4);
    cm.addCourse("CS201", "Algorithms", 4);
    cm.addCourse("MATH101", "Calculus", 3);

    rel.ensureSize(cm.count());
    rel.addPrereq(0, 1);
    rel.addPrereq(1, 2);

    cout << "Creating sample students...\n";
    pm.addStudent("Noor");
    pm.addStudent("Khadija");
    pm.addStudent("Nimra");

    cout << "Creating sample faculty...\n";
    pm.addFaculty("Sir Raza");
    pm.addFaculty("Sir Qamar");

    cout << "Creating sample rooms...\n";
    pm.addRoom("R101", 50);
    pm.addRoom("R102", 40);

    cout << "Assigning faculty and rooms...\n";
    courseToFaculty.insert(0, 0);
    courseToFaculty.insert(1, 0);
    courseToFaculty.insert(2, 1);
    courseToFaculty.insert(3, 1);

    courseToRoom.insert(0, 0);
    courseToRoom.insert(1, 0);
    courseToRoom.insert(2, 1);
    courseToRoom.insert(3, 1);

    cout << "Enrolling students...\n";
    auto* s1 = pm.getStudent(0);
    if (s1) {
        s1->enrolled.push_back(0);
        s1->enrolled.push_back(3);
    }

    auto* s2 = pm.getStudent(1);
    if (s2) {
        s2->enrolled.push_back(0);
        s2->enrolled.push_back(1);
    }

    printSuccess("Quick setup completed!");
    displayStatistics();
}

CustomMap<int, int>& CLIInterface::getFacultyToRoom() {
    return facultyToRoom;
}

void CLIInterface::exportData(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        printError("Could not open file for writing");
        return;
    }

    file << "FAST UNIVERSITY DATA EXPORT\n";
    file << "===========================\n\n";

    file << "COURSES:\n";
    for (int i = 0; i < cm.count(); i++) {
        auto* c = cm.getCourse(i);
        if (c) {
            file << c->id << "," << c->code << "," << c->name << "," << c->credits << "\n";
        }
    }

    file << "\nSTUDENTS:\n";
    for (int i = 0; i < pm.getStudentCount(); i++) {
        auto* s = pm.getStudent(i);
        if (s) {
            file << s->id << "," << s->name << ",";
            for (size_t j = 0; j < s->enrolled.size(); j++) {
                file << s->enrolled[j];
                if (j < s->enrolled.size() - 1) file << ";";
            }
            file << "\n";
        }
    }

    file.close();
    printSuccess("Data exported to " + filename);
}

void CLIInterface::showHelp() {
    printHeader("HELP & DOCUMENTATION");

    cout << "\nMODULE 7 - Functions:\n";
    cout << "  Tests function properties (injective, surjective, bijective)\n";
    cout << "  Example: Course->Faculty mapping analysis\n";

    cout << "\nMODULE 8 - Automated Proofs:\n";
    cout << "  Generates formal mathematical proofs\n";
    cout << "  Example: Prerequisite verification using induction\n";

    cout << "\nMODULE 9 - Consistency Checker:\n";
    cout << "  Detects system-wide conflicts and violations\n";
    cout << "  Checks: cycles, prerequisites, capacity, assignments\n";

    cout << "\nMODULE 10 - Performance:\n";
    cout << "  Benchmarks algorithm efficiency\n";
    cout << "  Tests: transitive closure, function checks, etc.\n";

    cout << "\nMODULE 11 - CLI (Current):\n";
    cout << "  Text-based interactive interface\n";
    cout << "  Features: quick setup, export, statistics\n";

    cout << "\nMODULE 12 - Unit Testing:\n";
    cout << "  Comprehensive automated test suite\n";
    cout << "  Validates all discrete structure operations\n\n";
}

// ----------------- Menu Implementations -----------------

void CLIInterface::addStudentMenu() {
    printHeader("ADD NEW STUDENT");

    cout << "\nEnter student name: ";
    string name;
    clearInputBuffer();
    getline(cin, name);

    if (name.empty()) {
        printError("Student name cannot be empty!");
        return;
    }

    int studentId = pm.addStudent(name);
    printSuccess("Student added successfully! ID: " + to_string(studentId));

    cout << "\nWould you like to enroll this student in courses? (y/n): ";
    char choice;
    cin >> choice;
    clearInputBuffer();

    if (choice == 'y' || choice == 'Y') {
        enrollStudentMenu(studentId);
    }
}

void CLIInterface::addCourseMenu() {
    printHeader("ADD NEW COURSE");

    cout << "\nEnter course code (e.g., CS101): ";
    string code;
    cin >> code;
    clearInputBuffer();

    cout << "Enter course name: ";
    string name;
    getline(cin, name);

    cout << "Enter credit hours: ";
    int credits;
    cin >> credits;
    clearInputBuffer();

    if (credits < 1 || credits > 6) {
        printError("Invalid credit hours! Must be between 1-6");
        return;
    }

    int courseId = cm.addCourse(code, name, credits);
    rel.ensureSize(cm.count());

    printSuccess("Course added successfully! ID: " + to_string(courseId));

    cout << "\nWould you like to add prerequisites for this course? (y/n): ";
    char choice;
    cin >> choice;
    clearInputBuffer();

    if (choice == 'y' || choice == 'Y') {
        addPrerequisiteMenu(courseId);
    }
}

void CLIInterface::addFacultyMenu() {
    printHeader("ADD NEW FACULTY");

    cout << "\nEnter faculty name: ";
    string name;
    clearInputBuffer();
    getline(cin, name);

    if (name.empty()) {
        printError("Faculty name cannot be empty!");
        return;
    }

    int facultyId = pm.addFaculty(name);
    printSuccess("Faculty added successfully! ID: " + to_string(facultyId));
}

void CLIInterface::addRoomMenu() {
    printHeader("ADD NEW ROOM");

    cout << "\nEnter room number (e.g., R101): ";
    string roomNum;
    cin >> roomNum;

    cout << "Enter room capacity: ";
    int capacity;
    cin >> capacity;
    clearInputBuffer();

    if (capacity < 1) {
        printError("Invalid capacity! Must be at least 1");
        return;
    }

    int roomId = pm.addRoom(roomNum, capacity);
    printSuccess("Room added successfully! ID: " + to_string(roomId));
}

void CLIInterface::addPrerequisiteMenu(int courseId) {
    if (courseId == -1) {
        printHeader("ADD PREREQUISITE");

        cout << "\nAvailable Courses:\n";
        listCourses();

        cout << "\nEnter course ID that needs prerequisite: ";
        cin >> courseId;
        clearInputBuffer();

        if (courseId < 0 || courseId >= cm.count()) {
            printError("Invalid course ID!");
            return;
        }
    }

    cout << "\nSelect prerequisite course:\n";
    listCourses();

    cout << "\nEnter prerequisite course ID: ";
    int prereqId;
    cin >> prereqId;
    clearInputBuffer();

    if (prereqId < 0 || prereqId >= cm.count()) {
        printError("Invalid prerequisite course ID!");
        return;
    }

    if (courseId == prereqId) {
        printError("A course cannot be its own prerequisite!");
        return;
    }

    rel.addPrereq(prereqId, courseId);

    auto* course = cm.getCourse(courseId);
    auto* prereq = cm.getCourse(prereqId);
    if (course && prereq) {
        printSuccess(prereq->name + " is now a prerequisite for " + course->name);
    }
}

void CLIInterface::enrollStudentMenu(int studentId) {
    if (studentId == -1) {
        printHeader("ENROLL STUDENT IN COURSE");

        cout << "\nAvailable Students:\n";
        listStudents();

        cout << "\nEnter student ID: ";
        cin >> studentId;
        clearInputBuffer();
    }

    if (studentId < 0 || studentId >= pm.getStudentCount()) {
        printError("Invalid student ID!");
        return;
    }

    auto* student = pm.getStudent(studentId);
    if (!student) {
        printError("Student not found!");
        return;
    }

    cout << "\nAvailable Courses:\n";
    listCourses();

    cout << "\nEnter course ID to enroll: ";
    int courseId;
    cin >> courseId;
    clearInputBuffer();

    if (courseId < 0 || courseId >= cm.count()) {
        printError("Invalid course ID!");
        return;
    }

    // Check if already enrolled
    for (int enrolled : student->enrolled) {
        if (enrolled == courseId) {
            printError("Student is already enrolled in this course!");
            return;
        }
    }

    // Check prerequisites
    bool prereqsMet = true;
    for (int i = 0; i < cm.count(); i++) {
        if (rel.getPrereq(i, courseId)) {
            bool found = false;
            for (int enrolled : student->enrolled) {
                if (enrolled == i) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                prereqsMet = false;
                auto* prereqCourse = cm.getCourse(i);
                if (prereqCourse) {
                    printError("Missing prerequisite: " + prereqCourse->name);
                }
            }
        }
    }

    if (!prereqsMet) {
        cout << "\nEnroll anyway? (y/n): ";
        char choice;
        cin >> choice;
        clearInputBuffer();
        if (choice != 'y' && choice != 'Y') return;
    }

    student->enrolled.push_back(courseId);
    auto* course = cm.getCourse(courseId);
    if (course) {
        printSuccess(student->name + " enrolled in " + course->name);
    }
}

void CLIInterface::assignFacultyMenu() {
    printHeader("ASSIGN FACULTY TO COURSE");

    cout << "\nAvailable Courses:\n";
    listCourses();

    cout << "\nEnter course ID: ";
    int courseId;
    cin >> courseId;
    clearInputBuffer();

    if (courseId < 0 || courseId >= cm.count()) {
        printError("Invalid course ID!");
        return;
    }

    cout << "\nAvailable Faculty:\n";
    listFaculty();

    cout << "\nEnter faculty ID: ";
    int facultyId;
    cin >> facultyId;
    clearInputBuffer();

    if (facultyId < 0 || facultyId >= pm.getFacultyCount()) {
        printError("Invalid faculty ID!");
        return;
    }

    courseToFaculty.insert(courseId, facultyId);

    auto* course = cm.getCourse(courseId);
    auto* faculty = pm.getFaculty(facultyId);
    if (course && faculty) {
        printSuccess(faculty->name + " assigned to " + course->name);
    }
}

void CLIInterface::assignRoomMenu() {
    printHeader("ASSIGN ROOM TO COURSE");

    cout << "\nAvailable Courses:\n";
    listCourses();

    cout << "\nEnter course ID: ";
    int courseId;
    cin >> courseId;
    clearInputBuffer();

    if (courseId < 0 || courseId >= cm.count()) {
        printError("Invalid course ID!");
        return;
    }

    cout << "\nAvailable Rooms:\n";
    listRooms();

    cout << "\nEnter room ID: ";
    int roomId;
    cin >> roomId;
    clearInputBuffer();

    if (roomId < 0 || roomId >= pm.getRoomCount()) {
        printError("Invalid room ID!");
        return;
    }

    courseToRoom.insert(courseId, roomId);

    auto* course = cm.getCourse(courseId);
    auto* room = pm.getRoom(roomId);
    if (course && room) {
        printSuccess(course->name + " assigned to " + room->roomNumber);
    }
}

void CLIInterface::listStudents() {
    for (int i = 0; i < pm.getStudentCount(); i++) {
        auto* s = pm.getStudent(i);
        if (s) {
            cout << "  [" << s->id << "] " << s->name
                << " (Enrolled: " << s->enrolled.size() << " courses)\n";
        }
    }
}

void CLIInterface::listCourses() {
    for (int i = 0; i < cm.count(); i++) {
        auto* c = cm.getCourse(i);
        if (c) {
            cout << "  [" << c->id << "] " << c->code << " - " << c->name
                << " (" << c->credits << " credits)\n";
        }
    }
}

void CLIInterface::listFaculty() {
    for (int i = 0; i < pm.getFacultyCount(); i++) {
        auto* f = pm.getFaculty(i);
        if (f) {
            cout << "  [" << f->id << "] " << f->name << "\n";
        }
    }
}

void CLIInterface::listRooms() {
    for (int i = 0; i < pm.getRoomCount(); i++) {
        auto* r = pm.getRoom(i);
        if (r) {
            cout << "  [" << r->id << "] " << r->roomNumber
                << " (Capacity: " << r->capacity << ")\n";
        }
    }
}

void CLIInterface::viewStudentDetails() {
    printHeader("STUDENT DETAILS");

    cout << "\nAvailable Students:\n";
    listStudents();

    cout << "\nEnter student ID: ";
    int studentId;
    cin >> studentId;
    clearInputBuffer();

    if (studentId < 0 || studentId >= pm.getStudentCount()) {
        printError("Invalid student ID!");
        return;
    }

    auto* student = pm.getStudent(studentId);
    if (!student) {
        printError("Student not found!");
        return;
    }

    cout << "\n" << string(50, '=') << "\n";
    cout << "Student ID:   " << student->id << "\n";
    cout << "Name:         " << student->name << "\n";
    cout << "Enrolled in:  " << student->enrolled.size() << " courses\n";
    cout << string(50, '=') << "\n";

    if (!student->enrolled.empty()) {
        cout << "\nEnrolled Courses:\n";
        for (int courseId : student->enrolled) {
            auto* course = cm.getCourse(courseId);
            if (course) {
                cout << "  - " << course->code << ": " << course->name
                    << " (" << course->credits << " credits)\n";
            }
        }
    }
    else {
        cout << "\nNot enrolled in any courses.\n";
    }
}

void CLIInterface::viewCourseDetails() {
    printHeader("COURSE DETAILS");

    cout << "\nAvailable Courses:\n";
    listCourses();

    cout << "\nEnter course ID: ";
    int courseId;
    cin >> courseId;
    clearInputBuffer();

    if (courseId < 0 || courseId >= cm.count()) {
        printError("Invalid course ID!");
        return;
    }

    auto* course = cm.getCourse(courseId);
    if (!course) {
        printError("Course not found!");
        return;
    }

    cout << "\n" << string(50, '=') << "\n";
    cout << "Course ID:    " << course->id << "\n";
    cout << "Code:         " << course->code << "\n";
    cout << "Name:         " << course->name << "\n";
    cout << "Credits:      " << course->credits << "\n";
    cout << string(50, '=') << "\n";

    // Show prerequisites
    bool hasPrereqs = false;
    cout << "\nPrerequisites:\n";
    for (int i = 0; i < cm.count(); i++) {
        if (rel.getPrereq(i, courseId)) {
            hasPrereqs = true;
            auto* prereq = cm.getCourse(i);
            if (prereq) {
                cout << "  - " << prereq->code << ": " << prereq->name << "\n";
            }
        }
    }
    if (!hasPrereqs) {
        cout << "  None\n";
    }

    // Show assigned faculty
    int facultyId = courseToFaculty.get(courseId);
    if (facultyId != -1) {
        auto* faculty = pm.getFaculty(facultyId);
        if (faculty) {
            cout << "\nAssigned Faculty: " << faculty->name << "\n";
        }
    }
    else {
        cout << "\nAssigned Faculty: None\n";
    }

    // Show assigned room
    int roomId = courseToRoom.get(courseId);
    if (roomId != -1) {
        auto* room = pm.getRoom(roomId);
        if (room) {
            cout << "Assigned Room: " << room->roomNumber
                << " (Capacity: " << room->capacity << ")\n";
        }
    }
    else {
        cout << "Assigned Room: None\n";
    }

    // Count enrolled students
    int enrolledCount = 0;
    for (int i = 0; i < pm.getStudentCount(); i++) {
        auto* s = pm.getStudent(i);
        if (s) {
            for (int enrolled : s->enrolled) {
                if (enrolled == courseId) {
                    enrolledCount++;
                    break;
                }
            }
        }
    }
    cout << "Enrolled Students: " << enrolledCount << "\n";
}

void CLIInterface::runVerification() {
    printHeader("SYSTEM VERIFICATION");

    cout << "\nRunning comprehensive system checks...\n\n";

    int issueCount = 0;

    // Check 1: Prerequisite cycles (self-loop detection)
    cout << "1. Checking for prerequisite cycles... ";
    bool hasCycle = false;
    for (int i = 0; i < cm.count(); i++) {
        if (rel.getPrereq(i, i)) {
            hasCycle = true;
            break;
        }
    }
    if (hasCycle) {
        cout << "FAILED\n";
        printError("   Circular prerequisites detected!");
        issueCount++;
    }
    else {
        cout << "PASSED\n";
    }

    // Check 2: Room capacity
    cout << "2. Checking room capacities... ";
    bool capacityIssue = false;
    for (int i = 0; i < cm.count(); i++) {
        int roomId = courseToRoom.get(i);
        if (roomId != -1) {
            auto* room = pm.getRoom(roomId);
            if (room) {
                int enrolled = 0;
                for (int j = 0; j < pm.getStudentCount(); j++) {
                    auto* s = pm.getStudent(j);
                    if (s) {
                        for (int courseId : s->enrolled) {
                            if (courseId == i) enrolled++;
                        }
                    }
                }
                if (enrolled > room->capacity) {
                    capacityIssue = true;
                    auto* course = cm.getCourse(i);
                    if (course) {
                        cout << "FAILED\n";
                        printError("   " + course->name +
                            " has " + to_string(enrolled) + " students but room capacity is " +
                            to_string(room->capacity));
                        issueCount++;
                    }
                }
            }
        }
    }
    if (!capacityIssue) {
        cout << "PASSED\n";
    }

    // Check 3: Faculty assignments
    cout << "3. Checking faculty assignments... ";
    int unassignedCourses = 0;
    for (int i = 0; i < cm.count(); i++) {
        if (courseToFaculty.get(i) == -1) {
            unassignedCourses++;
        }
    }
    if (unassignedCourses > 0) {
        cout << "WARNING\n";
        cout << "   " << unassignedCourses << " courses without assigned faculty\n";
    }
    else {
        cout << "PASSED\n";
    }

    // Check 4: Student prerequisites
    cout << "4. Checking student prerequisites... ";
    int prereqViolations = 0;
    for (int i = 0; i < pm.getStudentCount(); i++) {
        auto* student = pm.getStudent(i);
        if (student) {
            for (int courseId : student->enrolled) {
                for (int j = 0; j < cm.count(); j++) {
                    if (rel.getPrereq(j, courseId)) {
                        bool hasPrereq = false;
                        for (int enrolled : student->enrolled) {
                            if (enrolled == j) {
                                hasPrereq = true;
                                break;
                            }
                        }
                        if (!hasPrereq) {
                            prereqViolations++;
                        }
                    }
                }
            }
        }
    }
    if (prereqViolations > 0) {
        cout << "WARNING\n";
        cout << "   " << prereqViolations << " prerequisite violations found\n";
    }
    else {
        cout << "PASSED\n";
    }

    cout << "\n" << string(50, '=') << "\n";
    if (issueCount == 0) {
        printSuccess("All critical checks passed!");
    }
    else {
        printError("Found " + to_string(issueCount) + " critical issues");
    }
    cout << string(50, '=') << "\n";
}
