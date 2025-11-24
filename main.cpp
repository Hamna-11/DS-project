#include "CourseManager.h"
#include "PeopleManager.h"
#include "InductionModule.h"
#include "LogicEngine.h"
#include "SetOperations.h"
#include "RelationsModule.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

int main() {
    CourseManager cm;
    PeopleManager pm;
    Relations rel;
    StudentGroupModule groupModule;
    LogicEngine logic;
    CustomMap<int, int> courseToFaculty;
    CustomMap<int, int> courseToRoom;

    std::cout << std::string(60, '=') << "\n MHM MANAGEMENT SYSTEM - PART 1\n Modules 1-6: Foundation & Basic Operations\n" << std::string(60, '=') << "\n";

    while (true) {
        std::cout << "\n========== MAIN MENU (PART 1) ==========\n";
        std::cout << "BASIC OPERATIONS:\n";
        std::cout << " 1. Add Course\n 2. Add Student\n 3. Add Faculty\n 4. Add Room\n";
        std::cout << " 5. Add Prerequisite\n 6. Assign Faculty to Course\n 7. Assign Room to Course\n 8. Enroll Student\n 9. List All Data\n";
        std::cout << "\nMODULE 1-6 OPERATIONS:\n";
        std::cout << "10. Course Scheduling (Module 1 & 3)\n11. Student Group Combinations (Module 2)\n12. Induction Check (Module 3)\n";
        std::cout << "13. Logic & Inference (Module 4)\n14. Set Operations (Module 5)\n15. Relations Analysis (Module 6)\n\n 0. Exit\n\nChoice: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "\n" << std::string(60, '=') << "\n Thank you for using FAST System!\n" << std::string(60, '=') << "\n";
            break;
        }

        switch (choice) {
        case 1: {
            std::string code, name; int credits;
            std::cout << "Course code: "; std::cin >> code;
            std::cout << "Course name: "; std::cin.ignore(); std::getline(std::cin, name);
            std::cout << "Credits: "; std::cin >> credits;
            cm.addCourse(code, name, credits);
            rel.ensureSize(cm.count());
            break;
        }
        case 2: {
            std::string name;
            std::cout << "Student name: "; std::cin.ignore(); std::getline(std::cin, name);
            pm.addStudent(name);
            break;
        }
        case 3: {
            std::string name;
            std::cout << "Faculty name: "; std::cin.ignore(); std::getline(std::cin, name);
            pm.addFaculty(name);
            break;
        }
        case 4: {
            std::string name; int capacity;
            std::cout << "Room name: "; std::cin.ignore(); std::getline(std::cin, name);
            std::cout << "Capacity: "; std::cin >> capacity;
            pm.addRoom(name, capacity);
            break;
        }
        case 5: {
            int a, b;
            std::cout << "Prerequisite course ID: "; std::cin >> a;
            std::cout << "Dependent course ID: "; std::cin >> b;
            if (a >= 0 && a < cm.count() && b >= 0 && b < cm.count()) {
                rel.addPrereq(a, b);
                std::cout << "[SUCCESS] Prerequisite added\n";
            }
            else std::cout << "[ERROR] Invalid course IDs\n";
            break;
        }
        case 6: {
            int c, f;
            std::cout << "Course ID: "; std::cin >> c;
            std::cout << "Faculty ID: "; std::cin >> f;
            if (c >= 0 && c < cm.count() && f >= 0 && f < pm.getFacultyCount()) {
                courseToFaculty.insert(c, f);
                auto* fac = pm.getFaculty(f);
                if (fac) fac->courses.push_back(c);
                std::cout << "[SUCCESS] Faculty assigned\n";
            }
            else std::cout << "[ERROR] Invalid IDs\n";
            break;
        }
        case 7: {
            int c, r;
            std::cout << "Course ID: "; std::cin >> c;
            std::cout << "Room ID: "; std::cin >> r;
            if (c >= 0 && c < cm.count() && r >= 0 && r < pm.getRoomCount()) {
                courseToRoom.insert(c, r);
                std::cout << "[SUCCESS] Room assigned\n";
            }
            else std::cout << "[ERROR] Invalid IDs\n";
            break;
        }
        case 8: {
            int s, c;
            std::cout << "Student ID: "; std::cin >> s;
            std::cout << "Course ID: "; std::cin >> c;
            auto* student = pm.getStudent(s);
            if (student && c >= 0 && c < cm.count()) {
                student->enrolled.push_back(c);
                std::cout << "[SUCCESS] Student enrolled\n";
            }
            else std::cout << "[ERROR] Invalid IDs\n";
            break;
        }
        case 9: {
            std::cout << "\n1. Courses 2. Students 3. Faculty 4. Rooms\nChoice: ";
            int sub; std::cin >> sub;
            if (sub == 1) cm.listAll();
            else if (sub == 2) pm.listAllStudents();
            else if (sub == 3) pm.listAllFaculties();
            else if (sub == 4) pm.listAllRooms();
            break;
        }
        case 10: {
            if (rel.hasPrereqCycle()) std::cout << "[ERROR] Cycle detected!\n";
            else {
                Scheduling sched(rel);
                sched.generateOrders(cm.count(), 500);
                sched.displayOrders(cm, 30);
            }
            break;
        }
        case 11: {
            std::cout << "\n1. Add Student 2. Show Students 3. Generate Groups\nChoice: ";
            int sub; std::cin >> sub;
            if (sub == 1) {
                std::string name;
                std::cout << "Student name: "; std::cin.ignore(); std::getline(std::cin, name);
                groupModule.addStudent(name);
            }
            else if (sub == 2) groupModule.display();
            else if (sub == 3) {
                int size; std::cout << "Group size: "; std::cin >> size;
                groupModule.displayCombinations(size);
            }
            break;
        }
        case 12: {
            int c; std::cout << "Course ID to check: "; std::cin >> c;
            if (c >= 0 && c < cm.count()) {
                std::vector<bool> completed(cm.count(), false);
                std::cout << "Enter completed course IDs (-1 to stop): ";
                int x;
                while (std::cin >> x && x != -1) {
                    if (x >= 0 && x < cm.count()) completed[x] = true;
                }
                Induction ind(rel);
                ind.displayCheck(cm, c, completed);
            }
            else std::cout << "[ERROR] Invalid course ID\n";
            break;
        }
        case 13: {
            std::cout << "\n1. Add Logic Rule\n2. Add Fact\n3. Run Inference\n4. Display Rules\n5. Display Facts\nChoice: ";
            int sub; std::cin >> sub;
            if (sub == 1) {
                std::string name, desc;
                std::cout << "Rule name: "; std::cin >> name;
                std::cin.ignore(); std::cout << "Description: "; std::getline(std::cin, desc);
                int n; std::cout << "Number of antecedent courses: "; std::cin >> n;
                std::vector<int> ante(n);
                std::cout << "Enter course IDs: ";
                for (int i = 0; i < n; i++) std::cin >> ante[i];
                int m; std::cout << "Number of consequent courses: "; std::cin >> m;
                std::vector<int> cons(m);
                std::cout << "Enter course IDs: ";
                for (int i = 0; i < m; i++) std::cin >> cons[i];
                logic.addRule(name, ante, cons, desc);
            }
            else if (sub == 2) {
                std::string fact; std::cout << "Fact name: "; std::cin >> fact;
                logic.addFact(fact, true);
                std::cout << "[SUCCESS] Fact added\n";
            }
            else if (sub == 3) {
                auto inferred = logic.inferConsequences();
                std::cout << "\n" << std::string(60, '=') << "\n INFERENCE RESULTS\n" << std::string(60, '=') << "\n";
                if (inferred.empty()) std::cout << "No new inferences made.\n";
                else for (const auto& i : inferred) std::cout << "-> " << i << "\n";
            }
            else if (sub == 4) logic.displayRules();
            else if (sub == 5) logic.displayFacts();
            break;
        }
        case 14: {
            int s1, s2;
            std::cout << "First student ID: "; std::cin >> s1;
            std::cout << "Second student ID: "; std::cin >> s2;
            if (s1 >= 0 && s1 < pm.getStudentCount() && s2 >= 0 && s2 < pm.getStudentCount())
                SetOps::display(cm, s1, s2, pm);
            else std::cout << "[ERROR] Invalid student IDs\n";
            break;
        }
        case 15: {
            std::cout << "\n1. Display Prerequisite Matrix\n2. Check Relation Properties\n3. Display Transitive Closure\nChoice: ";
            int sub; std::cin >> sub;
            if (sub == 1) rel.displayMatrix(cm);
            else if (sub == 2) {
                std::cout << "\n" << std::string(60, '=') << "\n RELATION PROPERTIES\n" << std::string(60, '=') << "\n\n";
                std::cout << "\nPrerequisite Relation Analysis:\n";
                std::cout << " Reflexive: " << (rel.isReflexive() ? "[YES]" : "[NO]") << "\n";
                std::cout << " Symmetric: " << (rel.isSymmetric() ? "[YES]" : "[NO]") << "\n";
                std::cout << " Transitive: " << (rel.isTransitive() ? "[YES]" : "[NO]") << "\n";
                std::cout << " Equivalence: " << (rel.isEquivalence() ? "[YES]" : "[NO]") << "\n";
                std::cout << " Partial Order: " << (rel.isPartialOrder() ? "[YES]" : "[NO]") << "\n";
                std::cout << " Has Cycles: " << (rel.hasPrereqCycle() ? "[YES]" : "[NO]") << "\n\n";
            }
            else if (sub == 3) {
                auto closure = rel.closurePrereq();
                std::cout << "\n" << std::string(60, '=') << "\n TRANSITIVE CLOSURE\n" << std::string(60, '=') << "\n\n";
                std::cout << " ";
                for (int i = 0; i < rel.getSize(); i++) {
                    const auto* c = cm.getCourse(i);
                    std::cout << std::setw(6) << (c ? c->code : std::to_string(i));
                }
                std::cout << "\n";
                for (int i = 0; i < rel.getSize(); i++) {
                    const auto* c = cm.getCourse(i);
                    std::cout << std::setw(5) << (c ? c->code : std::to_string(i));
                    for (int j = 0; j < rel.getSize(); j++) {
                        std::cout << std::setw(6) << (closure[i][j] ? "Y" : ".");
                    }
                    std::cout << "\n";
                }
                std::cout << "\n";
            }
            break;
        }
        default:
            std::cout << "[ERROR] Invalid choice!\n";
        }
    }
    return 0;
    //maryam fatima
}