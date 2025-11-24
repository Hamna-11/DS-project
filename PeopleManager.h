#ifndef PEOPLEMANAGER_H
#define PEOPLEMANAGER_H

#include <vector>
#include <string>

class PeopleManager {
public:
    struct Student {
        int id;
        std::string name;
        std::vector<int> enrolled;
        Student();
        Student(int, std::string);
    };

    struct Faculty {
        int id;
        std::string name;
        std::vector<int> courses;
        Faculty();
        Faculty(int, std::string);
    };

    struct Room {
        int id;
        std::string name;
        int capacity;
        Room();
        Room(int, std::string, int cap = 30);
    };

private:
    std::vector<Student> students;
    std::vector<Faculty> faculties;
    std::vector<Room> rooms;

public:
    int addStudent(const std::string&);
    int addFaculty(const std::string&);
    int addRoom(const std::string&, int capacity = 30);
    Student* getStudent(int);
    Faculty* getFaculty(int);
    Room* getRoom(int);
    int getStudentCount() const;
    int getFacultyCount() const;
    int getRoomCount() const;
    void listAllStudents() const;
    void listAllFaculties() const;
    void listAllRooms() const;
};

#endif#pragma once
