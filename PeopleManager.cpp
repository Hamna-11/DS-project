#include "PeopleManager.h"
#include <iostream>
#include <iomanip>

PeopleManager::Student::Student() : id(-1) {}
PeopleManager::Student::Student(int i, std::string n) : id(i), name(n) {}

PeopleManager::Faculty::Faculty() : id(-1) {}
PeopleManager::Faculty::Faculty(int i, std::string n) : id(i), name(n) {}

PeopleManager::Room::Room() : id(-1), capacity(0) {}
PeopleManager::Room::Room(int i, std::string n, int cap)
    : id(i), name(n), roomNumber(n), capacity(cap) {
}

int PeopleManager::addStudent(const std::string& name) {
    int id = static_cast<int>(students.size());
    students.push_back(Student(id, name));
    std::cout << "[SUCCESS] Added student: " << name << "\n";
    return id;
}

int PeopleManager::addFaculty(const std::string& name) {
    int id = static_cast<int>(faculties.size());
    faculties.push_back(Faculty(id, name));
    std::cout << "[SUCCESS] Added faculty: " << name << "\n";
    return id;
}

int PeopleManager::addRoom(const std::string& name, int capacity) {
    int id = static_cast<int>(rooms.size());
    rooms.push_back(Room(id, name, capacity));
    std::cout << "[SUCCESS] Added room: " << name << "\n";
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
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << " ALL STUDENTS\n";
    std::cout << std::string(60, '=') << "\n\n";
    std::cout << std::left << std::setw(5) << "ID" << std::setw(30) << "Name"
        << "Enrolled\n";
    std::cout << std::string(60, '-') << "\n";
    for (const auto& s : students) {
        std::cout << std::left << std::setw(5) << s.id << std::setw(30) << s.name
            << s.enrolled.size() << " courses\n";
    }
    std::cout << "\nTotal Students: " << students.size() << "\n";
}

void PeopleManager::listAllFaculties() const {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << " ALL FACULTY\n";
    std::cout << std::string(60, '=') << "\n\n";
    std::cout << std::left << std::setw(5) << "ID" << std::setw(30) << "Name"
        << "Courses\n";
    std::cout << std::string(60, '-') << "\n";
    for (const auto& f : faculties) {
        std::cout << std::left << std::setw(5) << f.id << std::setw(30) << f.name
            << f.courses.size() << " courses\n";
    }
    std::cout << "\nTotal Faculty: " << faculties.size() << "\n";
}

void PeopleManager::listAllRooms() const {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << " ALL ROOMS\n";
    std::cout << std::string(60, '=') << "\n\n";
    std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "Room"
        << "Capacity\n";
    std::cout << std::string(60, '-') << "\n";
    for (const auto& r : rooms) {
        std::cout << std::left << std::setw(5) << r.id << std::setw(20) << r.roomNumber
            << r.capacity << "\n";
    }
    std::cout << "\nTotal Rooms: " << rooms.size() << "\n";
}