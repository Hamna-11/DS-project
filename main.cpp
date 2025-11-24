#include "DataStructures.h"
#include "Functions.h"
#include "Proof.h"
#include "Consistency.h"
#include "Performance.h"
#include "CLI.h"
#include "Testing.h"
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    CourseManager cm;
    PeopleManager pm;
    Relations rel;

    CustomMap<int, int> courseToFaculty;
    CustomMap<int, int> courseToRoom;


    CLIInterface cli(cm, pm, rel, courseToFaculty, courseToRoom);

    cout << string(60, '=') << "\n";
    cout << "  MHM MANAGEMENT SYSTEM\n";
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
        cout << " 9. List All Courses\n";
        cout << "\nADVANCED FEATURES:\n";
        cout << "10. Function Properties & Inverse\n";
        cout << "11. Proof Generator\n";
        cout << "12. Consistency Checker\n";
        cout << "13. Performance Benchmarking\n";
        cout << "14. System Statistics & Export\n";
        cout << "15. Unit Testing\n";
        cout << "\nADDITIONAL TOOLS:\n";
        cout << "18. Test Inverse Functions\n";
        cout << "19. Analyze Student Enrollments\n";
        cout << "20. Analyze Faculty Assignments\n";
        cout << "21. Test Optimized Implementation\n";
        cout << "22. Set Operations & Relations\n";
        cout << "\nUTILITIES:\n";
        cout << "16. Quick Setup\n";
        cout << "17. Help\n";
        cout << "\n 0. Exit\n";
        cout << "\nChoice: ";

        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "\n" << string(60, '=') << "\n";
            cout << "  Thank you for using MHM System!\n";
            cout << string(60, '=') << "\n";
            break;
        }

        switch (choice) {
        case 1: {
            string code, name;
            int credits;
            cout << "Course code: ";
            cin >> code;
            cout << "Course name: ";
            cin >> name;
            cout << "Credits: ";
            cin >> credits;

            cm.addCourse(code, name, credits);
            rel.ensureSize(cm.count());
            DisplayHelper::printSuccess("Course added");
            break;
        }

        case 2: {
            string name;
            cout << "Student name: ";
            cin >> name;
            pm.addStudent(name);
            DisplayHelper::printSuccess("Student added");
            break;
        }

        case 3: {
            string name;
            cout << "Faculty name: ";
            cin >> name;
            pm.addFaculty(name);
            DisplayHelper::printSuccess("Faculty added");
            break;
        }

        case 4: {
            string name;
            int capacity;
            cout << "Room name: ";
            cin >> name;
            cout << "Capacity: ";
            cin >> capacity;
            pm.addRoom(name, capacity);
            DisplayHelper::printSuccess("Room added");
            break;
        }

        case 5: {
            int a, b;
            cout << "Prerequisite course ID: ";
            cin >> a;
            cout << "Dependent course ID: ";
            cin >> b;

            if (a >= 0 && a < cm.count() && b >= 0 && b < cm.count()) {
                rel.addPrereq(a, b);
                DisplayHelper::printSuccess("Prerequisite added");
            }
            else {
                DisplayHelper::printError("Invalid course IDs");
            }
            break;
        }

        case 6: {
            int c, f;
            cout << "Course ID: ";
            cin >> c;
            cout << "Faculty ID: ";
            cin >> f;

            if (c >= 0 && c < cm.count() && f >= 0 && f < pm.getFacultyCount()) {
                courseToFaculty.insert(c, f);
                auto* fac = pm.getFaculty(f);
                if (fac) fac->courses.push_back(c);
                DisplayHelper::printSuccess("Faculty assigned");
            }
            else {
                DisplayHelper::printError("Invalid IDs");
            }
            break;
        }

        case 7: {
            int c, r;
            cout << "Course ID: ";
            cin >> c;
            cout << "Room ID: ";
            cin >> r;

            if (c >= 0 && c < cm.count() && r >= 0 && r < pm.getRoomCount()) {
                courseToRoom.insert(c, r);
                DisplayHelper::printSuccess("Room assigned");
            }
            else {
                DisplayHelper::printError("Invalid IDs");
            }
            break;
        }

        case 8: {
            int s, c;
            cout << "Student ID: ";
            cin >> s;
            cout << "Course ID: ";
            cin >> c;

            auto* student = pm.getStudent(s);
            if (student && c >= 0 && c < cm.count()) {
                student->enrolled.push_back(c);
                DisplayHelper::printSuccess("Student enrolled");
            }
            else {
                DisplayHelper::printError("Invalid IDs");
            }
            break;
        }

        case 9: {
            cm.listAll();
            break;
        }

        case 10: {
            Functions::display(courseToFaculty, cm, pm);

            cout << "\nAdditional Operations:\n";
            cout << "1. Test Function Composition\n";
            cout << "2. Test Inverse Function\n";
            cout << "Choice (or 0 to skip): ";

            int sub;
            cin >> sub;

            if (sub == 1) {
                DisplayHelper::printHeader("FUNCTION COMPOSITION");

                CustomMap<int, int> f1, f2;
                for (const auto& pair : courseToFaculty) {
                    f1.insert(pair.first, pair.second);
                }

                cout << "Enter faculty->room mappings (-1 to stop):\n";
                int fid, rid;
                while (true) {
                    cout << "Faculty ID: ";
                    cin >> fid;
                    if (fid == -1) break;
                    cout << "Room ID: ";
                    cin >> rid;
                    f2.insert(fid, rid);
                }

                auto composed = Functions::compose(f1, f2);
                cout << "\nComposed function: course -> room\n";
                for (const auto& pair : composed) {
                    const auto* c = cm.getCourse(pair.first);
                    auto* r = pm.getRoom(pair.second);
                    cout << "  " << (c ? c->code : to_string(pair.first))
                        << " -> " << (r ? r->name : to_string(pair.second)) << "\n";
                }
            }
            else if (sub == 2) {
                DisplayHelper::printHeader("INVERSE FUNCTION TEST");

                auto inverse = Functions::inverse(courseToFaculty, pm.getFacultyCount());

                if (!inverse.empty()) {
                    cout << "\nInverse mapping (faculty -> course):\n";
                    for (const auto& pair : inverse) {
                        auto* fac = pm.getFaculty(pair.first);
                        const auto* course = cm.getCourse(pair.second);
                        cout << "  " << (fac ? fac->name : to_string(pair.first))
                            << " -> " << (course ? course->code : to_string(pair.second)) << "\n";
                    }

                    if (Functions::verifyInverse(courseToFaculty, inverse)) {
                        DisplayHelper::printSuccess("Inverse verification passed!");
                    }
                }
            }
            break;
        }

        case 11: {
            cout << "\n1. Prerequisite Proof\n";
            cout << "2. Equivalence Relation Proof\n";
            cout << "3. Course Chain Proof\n";
            cout << "4. Acyclic Graph Proof\n";
            cout << "5. Partition Proof\n";
            cout << "6. Pigeonhole Principle Proof\n";
            cout << "Choice: ";

            int sub;
            cin >> sub;

            ProofGenerator proof(rel, cm);

            if (sub == 1) {
                int c;
                cout << "Course ID to verify: ";
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
                else {
                    DisplayHelper::printError("Invalid course ID");
                }
            }
            else if (sub == 2) {
                auto matrix = rel.getPrereqMatrix();
                proof.generateEquivalenceProof(matrix);
                proof.display();
            }
            else if (sub == 3) {
                int s;
                cout << "Student ID: ";
                cin >> s;

                if (s >= 0 && s < pm.getStudentCount()) {
                    proof.generateCourseChainProof(s, pm);
                    proof.display();
                }
            }
            else if (sub == 4) {
                proof.generateAcyclicProof();
                proof.display();
            }
            else if (sub == 5) {
                vector<CustomSet<int>> partition;
                cout << "Enter number of sets in partition: ";
                int numSets;
                cin >> numSets;

                for (int i = 0; i < numSets; i++) {
                    CustomSet<int> s;
                    cout << "Enter elements for set " << i << " (-1 to stop): ";
                    int elem;
                    while (cin >> elem && elem != -1) {
                        s.insert(elem);
                    }
                    partition.push_back(s);
                }

                proof.generatePartitionProof(partition);
                proof.display();
            }
            else if (sub == 6) {
                int students, slots;
                cout << "Enter number of students: ";
                cin >> students;
                cout << "Enter number of time slots: ";
                cin >> slots;

                proof.generatePigeonholeProof(students, slots);
                proof.display();
            }
            break;
        }

        case 12: {
            ConsistencyChecker checker(cm, pm, rel, courseToFaculty, courseToRoom);
            checker.runAllChecks();
            checker.checkScheduleConflicts();
            checker.displayReport();
            break;
        }

        case 13: {
            PerformanceBenchmark bench;
            bench.runAllBenchmarks();
            break;
        }

        case 14: {
            cout << "\n1. Show System Statistics\n";
            cout << "2. Export Data to File\n";
            cout << "Choice: ";

            int sub;
            cin >> sub;

            if (sub == 1) {
                cli.displayStatistics();
            }
            else if (sub == 2) {
                string filename;
                cout << "Enter filename: ";
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
            cli.quickSetup();
            break;
        }

        case 17: {
            cli.showHelp();
            break;
        }

        case 18: {
            DisplayHelper::printHeader("INVERSE FUNCTION TEST");

            cout << "\nTesting inverse of Course->Faculty mapping:\n";

            auto inverse = Functions::inverse(courseToFaculty, pm.getFacultyCount());

            if (!inverse.empty()) {
                cout << "\nOriginal: Course -> Faculty\n";
                for (const auto& pair : courseToFaculty) {
                    const auto* c = cm.getCourse(pair.first);
                    auto* f = pm.getFaculty(pair.second);
                    cout << "  f(" << (c ? c->code : to_string(pair.first)) << ") = "
                        << (f ? f->name : to_string(pair.second)) << "\n";
                }

                cout << "\nInverse: Faculty -> Course\n";
                for (const auto& pair : inverse) {
                    auto* f = pm.getFaculty(pair.first);
                    const auto* c = cm.getCourse(pair.second);
                    cout << "  f^-1(" << (f ? f->name : to_string(pair.first)) << ") = "
                        << (c ? c->code : to_string(pair.second)) << "\n";
                }

                cout << "\nVerification:\n";
                for (const auto& pair : inverse) {
                    const int* original = courseToFaculty.get(pair.second);
                    if (original && *original == pair.first) {
                        cout << "  Verified for faculty ID " << pair.first << "\n";
                    }
                }
            }
            break;
        }

        case 19: {
            Functions::analyzeStudentCourses(pm, cm);
            break;
        }

        case 20: {
            cout << "\nAssign Faculty->Room mappings:\n";
            cout << "Enter mappings (-1 to stop):\n";

            CustomMap<int, int>& facultyToRoom = cli.getFacultyToRoom();

            int fid, rid;
            while (true) {
                cout << "Faculty ID: ";
                cin >> fid;
                if (fid == -1) break;
                cout << "Room ID: ";
                cin >> rid;

                if (fid >= 0 && fid < pm.getFacultyCount() &&
                    rid >= 0 && rid < pm.getRoomCount()) {
                    facultyToRoom.insert(fid, rid);
                    DisplayHelper::printSuccess("Mapping added");
                }
                else {
                    DisplayHelper::printError("Invalid IDs");
                }
            }

            Functions::analyzeFacultyRooms(facultyToRoom, pm);
            break;
        }

        case 21: {
            DisplayHelper::printHeader("OPTIMIZED IMPLEMENTATION TEST");

            cout << "\nComparing standard vs optimized implementation:\n\n";

            Relations standardRel;
            standardRel.ensureSize(100);
            for (int i = 0; i < 99; i++) {
                standardRel.addPrereq(i, i + 1);
            }

            auto start1 = clock();
            auto closure1 = standardRel.closurePrereq();
            auto end1 = clock();
            long long time1 = (end1 - start1) * 1000 / CLOCKS_PER_SEC;

            cout << "Standard Implementation:\n";
            cout << "  Time: " << time1 << " ms\n\n";

            OptimizedRelations bitsetRel;
            bitsetRel.ensureSize(100);
            for (int i = 0; i < 99; i++) {
                bitsetRel.addPrereq(i, i + 1);
            }

            auto start2 = clock();
            auto closure2 = bitsetRel.closurePrereq();
            auto end2 = clock();
            long long time2 = (end2 - start2) * 1000 / CLOCKS_PER_SEC;

            cout << "Optimized Implementation:\n";
            cout << "  Time: " << time2 << " ms\n\n";

            if (time2 < time1) {
                cout << "Speedup: " << (float)time1 / time2 << "x faster!\n";
                DisplayHelper::printSuccess("Optimization effective!");
            }
            else {
                cout << "Note: Speedup visible with larger datasets\n";
            }

            cout << "\nVerifying correctness:\n";
            cout << "  Standard: " << (closure1[0][99] ? "Path exists" : "No path") << "\n";
            cout << "  Optimized: " << (closure2[0].test(99) ? "Path exists" : "No path") << "\n";

            if (closure1[0][99] == closure2[0].test(99)) {
                DisplayHelper::printSuccess("Both implementations produce same result!");
            }
            break;
        }

        case 22: {
            DisplayHelper::printHeader("SET OPERATIONS & RELATIONS");

            cout << "\n1. Power Set of Courses\n";
            cout << "2. Cartesian Product\n";
            cout << "3. Check Relation Properties\n";
            cout << "Choice: ";

            int sub;
            cin >> sub;

            if (sub == 1) {
                CustomSet<int> courses;
                cout << "Enter course IDs for power set (-1 to stop): ";
                int c;
                while (cin >> c && c != -1) {
                    if (c >= 0 && c < cm.count()) {
                        courses.insert(c);
                    }
                }

                auto ps = Functions::powerSet(courses);
                cout << "\nPower Set (" << ps.size() << " subsets):\n";

                for (size_t i = 0; i < ps.size(); i++) {
                    cout << "  {";
                    const auto& subset = ps[i].getVector();
                    for (size_t j = 0; j < subset.size(); j++) {
                        const auto* course = cm.getCourse(subset[j]);
                        cout << (course ? course->code : to_string(subset[j]));
                        if (j < subset.size() - 1) cout << ", ";
                    }
                    cout << "}\n";
                }
            }
            else if (sub == 2) {
                CustomSet<int> setA, setB;

                cout << "Enter elements for Set A (-1 to stop): ";
                int elem;
                while (cin >> elem && elem != -1) {
                    setA.insert(elem);
                }

                cout << "Enter elements for Set B (-1 to stop): ";
                while (cin >> elem && elem != -1) {
                    setB.insert(elem);
                }

                auto cp = Functions::cartesianProduct(setA, setB);
                cout << "\nCartesian Product (" << cp.size() << " pairs):\n";

                for (const auto& p : cp) {
                    cout << "  (" << p.first << ", " << p.second << ")\n";
                }
            }
            else if (sub == 3) {
                cout << "\nRelation Properties:\n\n";
                cout << "Reflexive: " << (rel.isReflexive() ? "Yes" : "No") << "\n";
                cout << "Symmetric: " << (rel.isSymmetric() ? "Yes" : "No") << "\n";
                cout << "Transitive: " << (rel.isTransitive() ? "Yes" : "No") << "\n";
                cout << "Anti-Symmetric: " << (rel.isAntiSymmetric() ? "Yes" : "No") << "\n\n";
                cout << "Equivalence Relation: " << (rel.isEquivalenceRelation() ? "Yes" : "No") << "\n";
                cout << "Partial Order: " << (rel.isPartialOrder() ? "Yes" : "No") << "\n";
            }
            break;
        }

        default:
            DisplayHelper::printError("Invalid choice!");
        }
    }

    return 0;
    //maryam fatima
}