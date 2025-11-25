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
        std::vector<int> completed;

        Student();
        Student(int i, std::string n);
    };

    struct Faculty {
        int id;
        std::string name;
        std::vector<int> courses;

        Faculty();
        Faculty(int i, std::string n);
    };

    struct Room {
        int id;
        std::string name;
        std::string roomNumber;
        int capacity;

        Room();
        Room(int i, std::string n, int cap = 30);
    };

private:
    std::vector<Student> students;
    std::vector<Faculty> faculties;
    std::vector<Room> rooms;

public:
    int addStudent(const std::string& name);
    int addFaculty(const std::string& name);
    int addRoom(const std::string& name, int capacity = 30);

    Student* getStudent(int id);
    Faculty* getFaculty(int id);
    Room* getRoom(int id);

    int getStudentCount() const;
    int getFacultyCount() const;
    int getRoomCount() const;

    void listAllStudents() const;
    void listAllFaculties() const;
    void listAllRooms() const;
};

#endif