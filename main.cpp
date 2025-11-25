#include "UniversitySystem.h"
#include <iostream>
#include <string>

using namespace std;

void quickSetup(CourseManager& cm, PeopleManager& pm, Relations& rel,
                CustomMap<int, int>& courseToFaculty, CustomMap<int, int>& courseToRoom) {
    cout << "\n[INFO] Running quick setup...\n\n";
    
    // Add courses
    cm.addCourse("CS101", "Programming Fundamentals", 3);
    cm.addCourse("CS102", "Data Structures", 4);
    cm.addCourse("CS201", "Algorithms", 4);
    cm.addCourse("CS202", "Database Systems", 3);
    cm.addCourse("MATH101", "Calculus I", 3);
    
    // Add prerequisites
    rel.addPrereq(0, 1); // CS101 -> CS102
    rel.addPrereq(1, 2); // CS102 -> CS201
    rel.addPrereq(1, 3); // CS102 -> CS202
    
    // Add students
    pm.addStudent("Ali Ahmed");
    pm.addStudent("Sara Khan");
    pm.addStudent("Hassan Ali");
    
    // Add faculty
    pm.addFaculty("Dr. Smith");
    pm.addFaculty("Dr. Johnson");
    pm.addFaculty("Dr. Williams");
    
    // Add rooms
    pm.addRoom("Room 101", 30);
    pm.addRoom("Room 102", 40);
    pm.addRoom("Room 103", 35);
    
    // Assign faculty to courses
    courseToFaculty.insert(0, 0);
    courseToFaculty.insert(1, 1);
    courseToFaculty.insert(2, 1);
    courseToFaculty.insert(3, 2);
    courseToFaculty.insert(4, 0);
    
    // Assign rooms to courses
    courseToRoom.insert(0, 0);
    courseToRoom.insert(1, 1);
    courseToRoom.insert(2, 1);
    courseToRoom.insert(3, 2);
    courseToRoom.insert(4, 0);
    
    // Enroll students
    auto* s1 = pm.getStudent(0);
    if (s1) {
        s1->enrolled.push_back(0);
        s1->enrolled.push_back(4);
        s1->completed.push_back(0);
    }
    
    auto* s2 = pm.getStudent(1);
    if (s2) {
        s2->enrolled.push_back(0);
        s2->enrolled.push_back(1);
        s2->completed.push_back(0);
    }
    
    cout << "\n[SUCCESS] Quick setup completed!\n";
}

void showMainMenu() {
    cout << "\n========== MAIN MENU ==========\n";
    cout << "BASIC OPERATIONS:\n";
    cout << " 1. Add Course\n";
    cout << " 2. Add Student\n";
    cout << " 3. Add Faculty\n";
    cout << " 4. Add Room\n";
    cout << " 5. Add Prerequisite\n";
    cout << " 6. Assign Faculty to Course\n";
    cout << " 7. Assign Room to Course\n";
    cout << " 8. Enroll Student\n";
    cout << " 9. List All Data\n";
    cout << "\nADVANCED FEATURES:\n";
    cout << "10. Function Properties & Analysis\n";
    cout << "11. Proof Generator\n";
    cout << "12. Consistency Checker\n";
    cout << "13. Performance Benchmarking\n";
    cout << "14. System Statistics\n";
    cout << "15. Unit Testing\n";
    cout << "16. Relations Analysis\n";
    cout << "\nUTILITIES:\n";
    cout << "17. Quick Setup\n";
    cout << "\n 0. Exit\n";
    cout << "\nChoice: ";
}

int main() {
    CourseManager cm;
    PeopleManager pm;
    Relations rel;
    CustomMap<int, int> courseToFaculty;
    CustomMap<int, int> courseToRoom;
    
    cout << string(60, '=') << "\n";
    cout << " FAST UNIVERSITY MANAGEMENT SYSTEM\n";
    cout << " Complete Discrete Mathematics Implementation\n";
    cout << string(60, '=') << "\n";
    
    while (true) {
        showMainMenu();
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        if (choice == 0) {
            cout << "\n" << string(60, '=') << "\n";
            cout << " Thank you for using FAST System!\n";
            cout << string(60, '=') << "\n";
            break;
        }
        
        switch (choice) {
        case 1: {
            string code, name;
            int credits;
            cout << "Course Code: ";
            cin >> code;
            cin.ignore();
            cout << "Course Name: ";
            getline(cin, name);
            cout << "Credits: ";
            cin >> credits;
            cm.addCourse(code, name, credits);
            break;
        }
        
        case 2: {
            string name;
            cout << "Student Name: ";
            getline(cin, name);
            pm.addStudent(name);
            break;
        }
        
        case 3: {
            string name;
            cout << "Faculty Name: ";
            getline(cin, name);
            pm.addFaculty(name);
            break;
        }
        
        case 4: {
            string name;
            int capacity;
            cout << "Room Name: ";
            getline(cin, name);
            cout << "Capacity: ";
            cin >> capacity;
            pm.addRoom(name, capacity);
            break;
        }
        
        case 5: {
            int from, to;
            cout << "Prerequisite Course ID: ";
            cin >> from;
            cout << "For Course ID: ";
            cin >> to;
            if (from >= 0 && from < cm.count() && to >= 0 && to < cm.count()) {
                rel.addPrereq(from, to);
                cout << "[SUCCESS] Prerequisite added\n";
            } else {
                cout << "[ERROR] Invalid course IDs\n";
            }
            break;
        }
        
        case 6: {
            int courseId, facultyId;
            cout << "Course ID: ";
            cin >> courseId;
            cout << "Faculty ID: ";
            cin >> facultyId;
            if (courseId >= 0 && courseId < cm.count() && facultyId >= 0 && facultyId < pm.getFacultyCount()) {
                courseToFaculty.insert(courseId, facultyId);
                auto* fac = pm.getFaculty(facultyId);
                if (fac) fac->courses.push_back(courseId);
                cout << "[SUCCESS] Faculty assigned\n";
            } else {
                cout << "[ERROR] Invalid IDs\n";
            }
            break;
        }
        
        case 7: {
            int courseId, roomId;
            cout << "Course ID: ";
            cin >> courseId;
            cout << "Room ID: ";
            cin >> roomId;
            if (courseId >= 0 && courseId < cm.count() && roomId >= 0 && roomId < pm.getRoomCount()) {
                courseToRoom.insert(courseId, roomId);
                cout << "[SUCCESS] Room assigned\n";
            } else {
                cout << "[ERROR] Invalid IDs\n";
            }
            break;
        }
        
        case 8: {
            int studentId, courseId;
            cout << "Student ID: ";
            cin >> studentId;
            cout << "Course ID: ";
            cin >> courseId;
            auto* student = pm.getStudent(studentId);
            if (student && courseId >= 0 && courseId < cm.count()) {
                student->enrolled.push_back(courseId);
                cout << "[SUCCESS] Student enrolled\n";
            } else {
                cout << "[ERROR] Invalid IDs\n";
            }
            break;
        }
        
        case 9: {
            cout << "\n1. Courses\n2. Students\n3. Faculty\n4. Rooms\nChoice: ";
            int sub;
            cin >> sub;
            if (sub == 1) cm.listAll();
            else if (sub == 2) pm.listAllStudents();
            else if (sub == 3) pm.listAllFaculties();
            else if (sub == 4) pm.listAllRooms();
            break;
        }
        
        case 10: {
            DisplayHelper::displayFunctionAnalysis(courseToFaculty, cm, pm, "COURSE-FACULTY MAPPING ANALYSIS");
            break;
        }
        
        case 11: {
            cout << "\n1. Prerequisite Proof\n2. Acyclic Graph Proof\nChoice: ";
            int sub;
            cin >> sub;
            ProofGenerator proof(rel, cm);
            if (sub == 1) {
                int c;
                cout << "Course ID: ";
                cin >> c;
                if (c >= 0 && c < cm.count()) {
                    vector<bool> completed(cm.count(), false);
                    cout << "Enter completed course IDs (-1 to stop): ";
                    int x;
                    while (cin >> x && x != -1) {
                        if (x >= 0 && x < cm.count()) completed[x] = true;
                    }
                    proof.generatePrereqProof(c, completed);
                    proof.display();
                }
            } else if (sub == 2) {
                proof.generateAcyclicProof();
                proof.display();
            }
            break;
        }
        
        case 12: {
            ConsistencyChecker checker(cm, pm, rel, courseToFaculty, courseToRoom);
            checker.runAllChecks();
            checker.displayReport();
            break;
        }
        
        case 13: {
            PerformanceBenchmark bench;
            bench.runAllBenchmarks();
            break;
        }
        
        case 14: {
            DisplayHelper::printHeader("SYSTEM STATISTICS");
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
            cout << "  Course-Faculty: " << courseToFaculty.size() << " mappings\n";
            cout << "  Course-Room:    " << courseToRoom.size() << " mappings\n\n";
            break;
        }
        
        case 15: {
            UnitTesting tester;
            tester.runAllTests();
            break;
        }
        
        case 16: {
            cout << "\n1. Display Matrix\n2. Check Properties\n3. Transitive Closure\nChoice: ";
            int sub;
            cin >> sub;
            if (sub == 1) {
                DisplayHelper::displayMatrix(rel, cm);
            } else if (sub == 2) {
                DisplayHelper::printHeader("RELATION PROPERTIES");
                cout << "\nReflexive: " << (rel.isReflexive() ? "YES" : "NO") << "\n";
                cout << "Symmetric: " << (rel.isSymmetric() ? "YES" : "NO") << "\n";
                cout << "Transitive: " << (rel.isTransitive() ? "YES" : "NO") << "\n";
                cout << "Anti-Symmetric: " << (rel.isAntiSymmetric() ? "YES" : "NO") << "\n";
                cout << "Has Cycles: " << (rel.hasPrereqCycle() ? "YES" : "NO") << "\n\n";
            } else if (sub == 3) {
                auto closure = rel.closurePrereq();
                DisplayHelper::printHeader("TRANSITIVE CLOSURE");
                for (int i = 0; i < rel.getSize(); i++) {
                    for (int j = 0; j < rel.getSize(); j++) {
                        cout << (closure[i][j] ? "1 " : "0 ");
                    }
                    cout << "\n";
                }
                cout << "\n";
            }
            break;
        }
        
        case 17:
            quickSetup(cm, pm, rel, courseToFaculty, courseToRoom);
            break;
        
        default:
            DisplayHelper::printError("Invalid choice!");
        }
    }
    
    return 0;
}
