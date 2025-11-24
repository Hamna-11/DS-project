#include "Consistency.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

ConsistencyChecker::ConsistencyChecker(const CourseManager& c, PeopleManager& p,
    const Relations& r, CustomMap<int, int>& cf, CustomMap<int, int>& cr)
    : cm(c), pm(p), rel(r), courseToFaculty(cf), courseToRoom(cr) {
}

void ConsistencyChecker::runAllChecks() {
    errors.clear();
    warnings.clear();

    checkPrereqCycles();
    checkStudentPrereqs();
    checkStudentOverload();
    checkFacultyConflicts();
    checkRoomCapacity();
    checkUnassignedCourses();
    checkCourseOverlaps();
}

void ConsistencyChecker::checkPrereqCycles() {
    if (rel.hasPrereqCycle()) {
        errors.push_back("Prerequisite cycle detected - impossible to complete all courses");
    }
}

void ConsistencyChecker::checkStudentPrereqs() {
    auto closure = rel.closurePrereq();

    for (int s = 0; s < pm.getStudentCount(); s++) {
        auto* student = pm.getStudent(s);
        if (!student) continue;

        CustomSet<int> enrolled;
        for (int x : student->enrolled) enrolled.insert(x);

        for (int courseId : student->enrolled) {
            for (int i = 0; i < (int)closure.size(); i++) {
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
    }
}

void ConsistencyChecker::checkStudentOverload() {
    for (int s = 0; s < pm.getStudentCount(); s++) {
        auto* student = pm.getStudent(s);
        if (student && student->enrolled.size() > 6) {
            stringstream ss;
            ss << student->name << " enrolled in " << student->enrolled.size()
                << " courses (overload)";
            warnings.push_back(ss.str());
        }
    }
}

void ConsistencyChecker::checkFacultyConflicts() {
    CustomMap<int, vector<int>> facultyCourses;

    for (const auto& pair : courseToFaculty) {
        vector<int>* courses = facultyCourses.get(pair.second);
        if (courses) {
            courses->push_back(pair.first);
        }
        else {
            vector<int> newVec;
            newVec.push_back(pair.first);
            facultyCourses.insert(pair.second, newVec);
        }
    }

    for (const auto& pair : facultyCourses) {
        if (pair.second.size() > 4) {
            auto* fac = pm.getFaculty(pair.first);
            stringstream ss;
            ss << (fac ? fac->name : to_string(pair.first))
                << " teaching " << pair.second.size() << " courses (high load)";
            warnings.push_back(ss.str());
        }
    }
}

void ConsistencyChecker::checkRoomCapacity() {
    for (const auto& pair : courseToRoom) {
        auto* r = pm.getRoom(pair.second);
        if (!r) continue;

        int enrolled = 0;
        for (int s = 0; s < pm.getStudentCount(); s++) {
            auto* student = pm.getStudent(s);
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
                << " students but room " << r->name << " capacity is " << r->capacity;
            errors.push_back(ss.str());
        }
    }
}

void ConsistencyChecker::checkUnassignedCourses() {
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

void ConsistencyChecker::checkCourseOverlaps() {
    for (int c1 = 0; c1 < cm.count(); c1++) {
        for (int c2 = c1 + 1; c2 < cm.count(); c2++) {
            CustomSet<int> students1 = getCourseStudents(c1);
            CustomSet<int> students2 = getCourseStudents(c2);

            CustomSet<int> intersection = students1.intersection(students2);

            if (intersection.size() > 0) {
                const auto* course1 = cm.getCourse(c1);
                const auto* course2 = cm.getCourse(c2);

                stringstream ss;
                ss << intersection.size() << " students enrolled in both "
                    << (course1 ? course1->code : to_string(c1)) << " and "
                    << (course2 ? course2->code : to_string(c2));

                DisplayHelper::printInfo(ss.str());
            }
        }
    }
}

void ConsistencyChecker::checkScheduleConflicts() {
    vector<CustomSet<int>> conflictGraph(cm.count());

    for (int c1 = 0; c1 < cm.count(); c1++) {
        for (int c2 = c1 + 1; c2 < cm.count(); c2++) {
            CustomSet<int> students1 = getCourseStudents(c1);
            CustomSet<int> students2 = getCourseStudents(c2);

            CustomSet<int> common = students1.intersection(students2);

            if (common.size() > 0) {
                conflictGraph[c1].insert(c2);
                conflictGraph[c2].insert(c1);
            }
        }
    }

    vector<int> colors(cm.count(), -1);
    int maxColor = 0;

    for (int c = 0; c < cm.count(); c++) {
        CustomSet<int> usedColors;

        for (const auto& neighbor : conflictGraph[c].getVector()) {
            if (colors[neighbor] != -1) {
                usedColors.insert(colors[neighbor]);
            }
        }

        int color = 0;
        while (usedColors.contains(color)) color++;

        colors[c] = color;
        maxColor = max(maxColor, color);
    }

    stringstream ss;
    ss << "Minimum time slots needed: " << (maxColor + 1);
    DisplayHelper::printInfo(ss.str());
}

CustomSet<int> ConsistencyChecker::getCourseStudents(int courseId) const {
    CustomSet<int> students;
    for (int s = 0; s < pm.getStudentCount(); s++) {
        auto* student = pm.getStudent(s);
        if (student) {
            if (find(student->enrolled.begin(), student->enrolled.end(), courseId)
                != student->enrolled.end()) {
                students.insert(s);
            }
        }
    }
    return students;
}

void ConsistencyChecker::displayReport() const {
    DisplayHelper::printHeader("CONSISTENCY REPORT");

    if (errors.empty() && warnings.empty()) {
        DisplayHelper::printSuccess("All consistency checks passed!");
        return;
    }

    if (!errors.empty()) {
        cout << "\n=== ERRORS (" << errors.size() << ") ===\n";
        for (const auto& err : errors) {
            DisplayHelper::printError(err);
        }
    }

    if (!warnings.empty()) {
        cout << "\n=== WARNINGS (" << warnings.size() << ") ===\n";
        for (const auto& warn : warnings) {
            DisplayHelper::printWarning(warn);
        }
    }

    cout << "\n";

}