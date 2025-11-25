#include "Functions.h"
#include <iostream>

using namespace std;

bool Functions::isInjective(const CustomMap<int, int>& f) {
    CustomSet<int> values;
    for (const auto& pair : f) {
        if (values.contains(pair.second)) return false;
        values.insert(pair.second);
    }
    return true;
}

bool Functions::isSurjective(const CustomMap<int, int>& f, int codomainSize) {
    CustomSet<int> values;
    for (const auto& pair : f) {
        values.insert(pair.second);
    }
    return values.size() == codomainSize;
}

bool Functions::isBijective(const CustomMap<int, int>& f, int codomainSize) {
    return isInjective(f) && isSurjective(f, codomainSize);
}

CustomMap<int, int> Functions::compose(const CustomMap<int, int>& f, const CustomMap<int, int>& g) {
    CustomMap<int, int> result;
    for (const auto& pair : f) {
        const int* gval = g.get(pair.second);
        if (gval) {
            result.insert(pair.first, *gval);
        }
    }
    return result;
}

CustomMap<int, int> Functions::inverse(const CustomMap<int, int>& f, int codomainSize) {
    CustomMap<int, int> inv;

    if (!isBijective(f, codomainSize)) {
        DisplayHelper::printError("Cannot create inverse - function must be bijective");
        return inv;
    }

    for (const auto& pair : f) {
        inv.insert(pair.second, pair.first);
    }

    DisplayHelper::printSuccess("Inverse function created");
    return inv;
}

bool Functions::verifyInverse(const CustomMap<int, int>& f, const CustomMap<int, int>& f_inv) {
    for (const auto& pair : f) {
        const int* inv_val = f_inv.get(pair.second);
        if (!inv_val || *inv_val != pair.first) {
            return false;
        }
    }
    return true;
}

void Functions::analyzeStudentCourses(PeopleManager& pm, const CourseManager& cm) {
    DisplayHelper::printHeader("STUDENT COURSE MAPPING");

    cout << "\nStudent Enrollments:\n";
    cout << "Total Students: " << pm.getStudentCount() << "\n\n";

    for (int i = 0; i < pm.getStudentCount(); i++) {
        auto* student = pm.getStudent(i);
        if (student) {
            cout << "  " << student->name << " -> {";
            for (size_t j = 0; j < student->enrolled.size(); j++) {
                auto* course = cm.getCourse(student->enrolled[j]);
                cout << (course ? course->code : to_string(student->enrolled[j]));
                if (j < student->enrolled.size() - 1) cout << ", ";
            }
            cout << "} (" << student->enrolled.size() << " courses)\n";
        }
    }
    cout << "\n";
}

void Functions::analyzeFacultyRooms(const CustomMap<int, int>& facultyToRoom, PeopleManager& pm) {
    DisplayHelper::printHeader("FACULTY ROOM ASSIGNMENT");

    cout << "\nFaculty-Room Mapping:\n";
    cout << "Total Assignments: " << facultyToRoom.size() << "\n";
    cout << "Available Rooms: " << pm.getRoomCount() << "\n\n";

    bool inj = isInjective(facultyToRoom);
    bool sur = isSurjective(facultyToRoom, pm.getRoomCount());

    cout << "Properties:\n";
    cout << "  Injective: " << (inj ? "Yes - Each faculty has unique room" : "No - Some rooms shared") << "\n";
    cout << "  Surjective: " << (sur ? "Yes - All rooms utilized" : "No - Some rooms unused") << "\n\n";

    cout << "Assignments:\n";
    for (const auto& pair : facultyToRoom) {
        auto* faculty = pm.getFaculty(pair.first);
        auto* room = pm.getRoom(pair.second);
        cout << "  " << (faculty ? faculty->name : to_string(pair.first))
            << " -> " << (room ? room->name : to_string(pair.second)) << "\n";
    }
    cout << "\n";
}

vector<CustomSet<int>> Functions::powerSet(const CustomSet<int>& s) {
    vector<CustomSet<int>> result;
    result.push_back(CustomSet<int>());

    for (const auto& elem : s.getVector()) {
        int currentSize = result.size();
        for (int i = 0; i < currentSize; i++) {
            CustomSet<int> newSet = result[i];
            newSet.insert(elem);
            result.push_back(newSet);
        }
    }
    return result;
}

vector<pair<int, int>> Functions::cartesianProduct(const CustomSet<int>& a, const CustomSet<int>& b) {
    vector<pair<int, int>> result;
    for (const auto& x : a.getVector()) {
        for (const auto& y : b.getVector()) {
            result.push_back(make_pair(x, y));
        }
    }
    return result;
}

void Functions::display(const CustomMap<int, int>& courseToFaculty, const CourseManager& cm, PeopleManager& pm) {
    DisplayHelper::printHeader("FUNCTION ANALYSIS");

    cout << "\nCourse-Faculty Mapping:\n";
    cout << "Courses Mapped: " << courseToFaculty.size() << "\n";
    cout << "Total Faculty: " << pm.getFacultyCount() << "\n\n";

    bool inj = isInjective(courseToFaculty);
    bool sur = isSurjective(courseToFaculty, pm.getFacultyCount());
    bool bij = isBijective(courseToFaculty, pm.getFacultyCount());

    cout << "Properties:\n";
    cout << "  Injective: " << (inj ? "Yes" : "No") << "\n";
    cout << "  Surjective: " << (sur ? "Yes" : "No") << "\n";
    cout << "  Bijective: " << (bij ? "Yes" : "No") << "\n\n";

    cout << "Mappings:\n";

    for (const auto& pair : courseToFaculty) {
        const auto* course = cm.getCourse(pair.first);
        auto* faculty = pm.getFaculty(pair.second);
        cout << "  " << (course ? course->code : to_string(pair.first)) << " -> "
            << (faculty ? faculty->name : to_string(pair.second)) << "\n";
    }
    cout << "\n";
}