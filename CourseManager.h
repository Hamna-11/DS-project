#ifndef COURSEMANAGER_H
#define COURSEMANAGER_H

#include <vector>
#include <string>

template<typename T>
class CustomSet {
private:
    std::vector<T> data;
public:
    void insert(const T&);
    bool contains(const T&) const;
    void erase(const T&);
    int size() const;
    bool empty() const;
    void clear();
    typename std::vector<T>::iterator begin();
    typename std::vector<T>::iterator end();
    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::const_iterator end() const;
    const std::vector<T>& getVector() const;
    CustomSet<T> intersection(const CustomSet<T>& other) const;
    CustomSet<T> setUnion(const CustomSet<T>& other) const;
};

template<typename K, typename V>
class CustomMap {
private:
    std::vector<std::pair<K, V>> data;
public:
    void insert(const K&, const V&);
    bool contains(const K&) const;
    V* get(const K&);
    const V* get(const K&) const;
    V get(const K&, const V& defaultValue) const;
    V& operator[](const K&);
    void erase(const K&);
    int size() const;
    bool empty() const;
    void clear();
    typename std::vector<std::pair<K, V>>::iterator begin();
    typename std::vector<std::pair<K, V>>::iterator end();
    typename std::vector<std::pair<K, V>>::const_iterator begin() const;
    typename std::vector<std::pair<K, V>>::const_iterator end() const;
};

class CourseManager {
public:
    struct Course {
        int id;
        std::string code;
        std::string name;
        int credits;
        bool active;
        Course();
        Course(int, std::string, std::string, int);
    };
private:
    std::vector<Course> courses;
    CustomMap<std::string, int> codeToId;
public:
    int addCourse(const std::string&, const std::string&, int);
    const Course* getCourse(int) const;
    Course* getCourse(int);
    int getCourseByCode(const std::string&) const;
    int count() const;
    void listAll() const;
    const std::vector<Course>& getAllCourses() const;
};

#endif