#include "PeopleManager.h"
#include <iostream>
#include <iomanip>
#include <string>

PeopleManager::Student::Student() : id(-1) {}

PeopleManager::Student::Student(int i, std::string n) : id(i), name(n) {}

PeopleManager::Faculty::Faculty() : id(-1) {}

PeopleManager::Faculty::Faculty(int i, std::string n) : id(i), name(n) {}

PeopleManager::Room::Room() : id(-1), capacity(30) {}

PeopleManager::Room::Room(int i, std::string n, int cap)
    : id(i), name(n), capacity(cap) {
}

int PeopleManager::addStudent(const std::string& name) {
    int id = students.size();
    students.push_back(Student(id, name));
    std::cout << "[SUCCESS] Added student: " << name << "\n";
    return id;
}

int PeopleManager::addFaculty(const std::string& name) {
    int id = faculties.size();
    faculties.push_back(Faculty(id, name));
    std::cout << "[SUCCESS] Added faculty: " << name << "\n";
    return id;
}

int PeopleManager::addRoom(const std::string& name, int capacity) {
    int id = rooms.size();
    rooms.push_back(Room(id, name, capacity));
    std::cout << "[SUCCESS] Added room: " << name << "\n";
    return id;
}

PeopleManager::Student* PeopleManager::getStudent(int id) {
    if (id < 0 || id >= (int)students.size()) return nullptr;
    return &students[id];
}

PeopleManager::Faculty* PeopleManager::getFaculty(int id) {
    if (id < 0 || id >= (int)faculties.size()) return nullptr;
    return &faculties[id];
}

PeopleManager::Room* PeopleManager::getRoom(int id) {
    if (id < 0 || id >= (int)rooms.size()) return nullptr;
    return &rooms[id];
}

int PeopleManager::getStudentCount() const {
    return students.size();
}

int PeopleManager::getFacultyCount() const {
    return faculties.size();
}

int PeopleManager::getRoomCount() const {
    return rooms.size();
}

void PeopleManager::listAllStudents() const {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  ALL STUDENTS\n";
    std::cout << std::string(60, '=') << "\n\n";

    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(25) << "Name"
        << "Enrolled Courses\n";
    std::cout << std::string(60, '-') << "\n";

    for (const auto& s : students) {
        std::cout << std::left << std::setw(5) << s.id
            << std::setw(25) << s.name << "[ ";
        for (size_t i = 0; i < s.enrolled.size(); i++) {
            std::cout << s.enrolled[i];
            if (i < s.enrolled.size() - 1) std::cout << ", ";
        }
        std::cout << " ]\n";
    }
    std::cout << "\nTotal Students: " << students.size() << "\n";
}

void PeopleManager::listAllFaculties() const {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  ALL FACULTY\n";
    std::cout << std::string(60, '=') << "\n\n";

    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(25) << "Name"
        << "Teaching Courses\n";
    std::cout << std::string(60, '-') << "\n";

    for (const auto& f : faculties) {
        std::cout << std::left << std::setw(5) << f.id
            << std::setw(25) << f.name << "[ ";
        for (size_t i = 0; i < f.courses.size(); i++) {
            std::cout << f.courses[i];
            if (i < f.courses.size() - 1) std::cout << ", ";
        }
        std::cout << " ]\n";
    }
    std::cout << "\nTotal Faculty: " << faculties.size() << "\n";
}

void PeopleManager::listAllRooms() const {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  ALL ROOMS\n";
    std::cout << std::string(60, '=') << "\n\n";

    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(20) << "Name"
        << "Capacity\n";
    std::cout << std::string(40, '-') << "\n";

    for (const auto& r : rooms) {
        std::cout << std::left << std::setw(5) << r.id
            << std::setw(20) << r.name
            << r.capacity << "\n";
    }
    std::cout << "\nTotal Rooms: " << rooms.size() << "\n";
}