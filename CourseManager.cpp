#include "CourseManager.h"
#include <iostream>
#include <iomanip>

template<typename T>
void CustomSet<T>::insert(const T& val) {
    if (std::find(data.begin(), data.end(), val) == data.end())
        data.push_back(val);
}

template<typename T>
bool CustomSet<T>::contains(const T& val) const {
    return std::find(data.begin(), data.end(), val) != data.end();
}

template<typename T>
void CustomSet<T>::erase(const T& val) {
    auto it = std::find(data.begin(), data.end(), val);
    if (it != data.end()) data.erase(it);
}

template<typename T>
int CustomSet<T>::size() const { return data.size(); }

template<typename T>
bool CustomSet<T>::empty() const { return data.empty(); }

template<typename T>
void CustomSet<T>::clear() { data.clear(); }

template<typename T>
typename std::vector<T>::iterator CustomSet<T>::begin() { return data.begin(); }

template<typename T>
typename std::vector<T>::iterator CustomSet<T>::end() { return data.end(); }

template<typename T>
typename std::vector<T>::const_iterator CustomSet<T>::begin() const { return data.begin(); }

template<typename T>
typename std::vector<T>::const_iterator CustomSet<T>::end() const { return data.end(); }

template<typename T>
const std::vector<T>& CustomSet<T>::getVector() const { return data; }

template<typename K, typename V>
void CustomMap<K, V>::insert(const K& key, const V& val) {
    for (auto& p : data) {
        if (p.first == key) { p.second = val; return; }
    }
    data.push_back(std::make_pair(key, val));
}

template<typename K, typename V>
bool CustomMap<K, V>::contains(const K& key) const {
    for (const auto& p : data) if (p.first == key) return true;
    return false;
}

template<typename K, typename V>
V* CustomMap<K, V>::get(const K& key) {
    for (auto& p : data) if (p.first == key) return &p.second;
    return nullptr;
}

template<typename K, typename V>
const V* CustomMap<K, V>::get(const K& key) const {
    for (const auto& p : data) if (p.first == key) return &p.second;
    return nullptr;
}

template<typename K, typename V>
V& CustomMap<K, V>::operator[](const K& key) {
    for (auto& p : data) if (p.first == key) return p.second;
    data.push_back(std::make_pair(key, V()));
    return data.back().second;
}

template<typename K, typename V>
void CustomMap<K, V>::erase(const K& key) {
    for (auto it = data.begin(); it != data.end(); ++it)
        if (it->first == key) { data.erase(it); return; }
}

template<typename K, typename V>
int CustomMap<K, V>::size() const { return data.size(); }

template<typename K, typename V>
bool CustomMap<K, V>::empty() const { return data.empty(); }

template<typename K, typename V>
void CustomMap<K, V>::clear() { data.clear(); }

template<typename K, typename V>
typename std::vector<std::pair<K, V>>::iterator CustomMap<K, V>::begin() { return data.begin(); }

template<typename K, typename V>
typename std::vector<std::pair<K, V>>::iterator CustomMap<K, V>::end() { return data.end(); }

CourseManager::Course::Course() : id(-1), credits(0), active(false) {}

CourseManager::Course::Course(int i, std::string c, std::string n, int cr)
    : id(i), code(c), name(n), credits(cr), active(true) {
}

int CourseManager::addCourse(const std::string& code, const std::string& name, int credits) {
    if (codeToId.contains(code)) {
        std::cout << "[ERROR] Course code already exists!\n";
        return -1;
    }
    int id = courses.size();
    courses.push_back(Course(id, code, name, credits));
    codeToId.insert(code, id);
    std::cout << "[SUCCESS] Added course: " << code << "\n";
    return id;
}

const CourseManager::Course* CourseManager::getCourse(int id) const {
    if (id < 0 || id >= (int)courses.size()) return nullptr;
    return &courses[id];
}

int CourseManager::getCourseByCode(const std::string& code) const {
    const int* id = codeToId.get(code);
    return id ? *id : -1;
}

int CourseManager::count() const { return courses.size(); }

void CourseManager::listAll() const {
    std::cout << "\n" << std::string(60, '=') << "\n ALL COURSES\n" << std::string(60, '=') << "\n\n";
    std::cout << std::left << std::setw(5) << "ID" << std::setw(12) << "Code" << std::setw(25) << "Name" << "Credits\n";
    std::cout << std::string(60, '-') << "\n";
    for (const auto& c : courses) {
        std::cout << std::left << std::setw(5) << c.id << std::setw(12) << c.code
            << std::setw(25) << c.name << c.credits << "\n";
    }
    std::cout << "\nTotal Courses: " << courses.size() << "\n";
}

const std::vector<CourseManager::Course>& CourseManager::getAllCourses() const { return courses; }

template class CustomSet<int>;
template class CustomMap<std::string, int>;