#include "CourseManager.h"
#include "PeopleManager.h"
#include "DataStructures.h"
#include "Functions.h"
#include "Proof.h"
#include "Consistency.h"
#include "Performance.h"
#include "CLI.h"
#include "Testing.h"
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

int main() {
    CourseManager cm;
    PeopleManager pm;
    Relations rel;
    CustomMap<int, int> courseToFaculty;
    CustomMap<int, int> courseToRoom;

    CLIInterface cli(cm, pm, rel, courseToFaculty, courseToRoom);

    cout << string(60, '=') << "\n";
    cout << " FAST UNIVERSITY MANAGEMENT SYSTEM\n";
    cout << " Complete Discrete Mathematics Implementation\n";
    cout << string(60, '=') << "\n";

    cli.showWelcome();

    while (true) {
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
        cout << "14. System Statistics & Export\n";
        cout << "15. Unit Testing\n";
        cout << "16. Relations Analysis\n";
        cout << "\nUTILITIES:\n";
        cout << "17. Quick Setup\n";
        cout << "18. Help\n";
        cout << "\n 0. Exit\n";
        cout << "\nChoice: ";

        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "\n" << string(60, '=') << "\n";
            cout << " Thank you for using FAST System!\n";
            cout << string(60, '=') << "\n";
            break;
        }

        switch (choice) {
        case 1:
            cli.addCourseMenu();
            break;

        case 2:
            cli.addStudentMenu();
            break;

        case 3:
            cli.addFacultyMenu();
            break;

        case 4:
            cli.addRoomMenu();
            break;

        case 5:
            cli.addPrerequisiteMenu();
            break;

        case 6:
            cli.assignFacultyMenu();
            break;

        case 7:
            cli.assignRoomMenu();
            break;

        case 8:
            cli.enrollStudentMenu();
            break;

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

        case 10:
            Functions::display(courseToFaculty, cm, pm);
            break;

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
            }
            else if (sub == 2) {
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
            cout << "\n1. Show Statistics\n2. Export Data\nChoice: ";
            int sub;
            cin >> sub;
            if (sub == 1) {
                cli.displayStatistics();
            }
            else if (sub == 2) {
                string filename;
                cout << "Filename: ";
                cin >> filename;
                cli.exportData(filename);
            }
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
                rel.displayMatrix(cm);
            }
            else if (sub == 2) {
                DisplayHelper::printHeader("RELATION PROPERTIES");
                cout << "\nReflexive: " << (rel.isReflexive() ? "YES" : "NO") << "\n";
                cout << "Symmetric: " << (rel.isSymmetric() ? "YES" : "NO") << "\n";
                cout << "Transitive: " << (rel.isTransitive() ? "YES" : "NO") << "\n";
                cout << "Anti-Symmetric: " << (rel.isAntiSymmetric() ? "YES" : "NO") << "\n";
                cout << "Has Cycles: " << (rel.hasPrereqCycle() ? "YES" : "NO") << "\n";
            }
            else if (sub == 3) {
                auto closure = rel.closurePrereq();
                DisplayHelper::printHeader("TRANSITIVE CLOSURE");
                for (int i = 0; i < rel.getSize(); i++) {
                    for (int j = 0; j < rel.getSize(); j++) {
                        cout << (closure[i][j] ? "1 " : "0 ");
                    }
                    cout << "\n";
                }
            }
            break;
        }

        case 17:
            cli.quickSetup();
            break;

        case 18:
            cli.showHelp();
            break;

        default:
            DisplayHelper::printError("Invalid choice!");
        }
    }

    return system("pause");
}