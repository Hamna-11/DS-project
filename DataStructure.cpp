#include "DataStructures.h"
#include <iostream>
#include <iomanip>

using namespace std;

CustomBitset::CustomBitset(int size) : totalBits(size) {
    int units = (size + BITS_PER_UNIT - 1) / BITS_PER_UNIT;
    bits.resize(units, 0ULL);
}

void CustomBitset::set(int pos) {
    if (pos < 0 || pos >= totalBits) return;
    int unit = pos / BITS_PER_UNIT;
    int offset = pos % BITS_PER_UNIT;
    bits[unit] |= (1ULL << offset);
}

void CustomBitset::reset(int pos) {
    if (pos < 0 || pos >= totalBits) return;
    int unit = pos / BITS_PER_UNIT;
    int offset = pos % BITS_PER_UNIT;
    bits[unit] &= ~(1ULL << offset);
}

bool CustomBitset::test(int pos) const {
    if (pos < 0 || pos >= totalBits) return false;
    int unit = pos / BITS_PER_UNIT;
    int offset = pos % BITS_PER_UNIT;
    return (bits[unit] & (1ULL << offset)) != 0;
}

int CustomBitset::count() const {
    int total = 0;
    for (unsigned long long unit : bits) {
        unsigned long long temp = unit;
        while (temp) {
            total += temp & 1;
            temp >>= 1;
        }
    }
    return total;
}

CustomBitset& CustomBitset::operator|=(const CustomBitset& other) {
    for (size_t i = 0; i < bits.size() && i < other.bits.size(); i++) {
        bits[i] |= other.bits[i];
    }
    return *this;
}

void CustomBitset::clear() {
    for (auto& unit : bits) {
        unit = 0ULL;
    }
}

void DisplayHelper::printHeader(const string& title) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "  " << title << "\n";
    cout << string(60, '=') << "\n";
}

void DisplayHelper::printSuccess(const string& msg) {
    cout << "[SUCCESS] " << msg << "\n";
}

void DisplayHelper::printError(const string& msg) {
    cout << "[ERROR] " << msg << "\n";
}

void DisplayHelper::printWarning(const string& msg) {
    cout << "[WARNING] " << msg << "\n";
}

void DisplayHelper::printInfo(const string& msg) {
    cout << "[INFO] " << msg << "\n";
}

CourseManager::Course::Course() : id(-1), credits(0) {}

CourseManager::Course::Course(int i, string c, string n, int cr)
    : id(i), code(c), name(n), credits(cr) {
}

int CourseManager::addCourse(const string& code, const string& name, int credits) {
    int id = courses.size();
    courses.push_back(Course(id, code, name, credits));
    return id;
}

const CourseManager::Course* CourseManager::getCourse(int id) const {
    if (id < 0 || id >= (int)courses.size()) return nullptr;
    return &courses[id];
}

int CourseManager::count() const {
    return courses.size();
}

void CourseManager::listAll() const {
    DisplayHelper::printHeader("ALL COURSES");
    cout << "\n" << left << setw(5) << "ID" << setw(12) << "Code"
        << setw(25) << "Name" << "Credits\n";
    cout << string(60, '-') << "\n";

    for (const auto& c : courses) {
        cout << left << setw(5) << c.id << setw(12) << c.code
            << setw(25) << c.name << c.credits << "\n";
    }
    cout << "\nTotal Courses: " << courses.size() << "\n";
}

PeopleManager::Student::Student() : id(-1) {}

PeopleManager::Student::Student(int i, string n) : id(i), name(n) {}

PeopleManager::Faculty::Faculty() : id(-1) {}

PeopleManager::Faculty::Faculty(int i, string n) : id(i), name(n) {}

PeopleManager::Room::Room() : id(-1), capacity(30) {}

PeopleManager::Room::Room(int i, string n, int cap) : id(i), name(n), capacity(cap) {}

int PeopleManager::addStudent(const string& name) {
    int id = students.size();
    students.push_back(Student(id, name));
    return id;
}

int PeopleManager::addFaculty(const string& name) {
    int id = faculties.size();
    faculties.push_back(Faculty(id, name));
    return id;
}

int PeopleManager::addRoom(const string& name, int capacity) {
    int id = rooms.size();
    rooms.push_back(Room(id, name, capacity));
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

OptimizedRelations::OptimizedRelations() : size(0) {
    prereqBits.resize(MAX_SIZE, CustomBitset(MAX_SIZE));
}

void OptimizedRelations::ensureSize(int n) {
    if (n > size) {
        size = n;
    }
}

void OptimizedRelations::addPrereq(int a, int b) {
    ensureSize(max(a, b) + 1);
    prereqBits[a].set(b);
}

bool OptimizedRelations::getPrereq(int a, int b) const {
    if (a < 0 || b < 0 || a >= size || b >= size) return false;
    return prereqBits[a].test(b);
}

int OptimizedRelations::getSize() const {
    return size;
}

vector<CustomBitset> OptimizedRelations::closurePrereq() const {
    vector<CustomBitset> result = prereqBits;

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            if (result[i].test(k)) {
                result[i] |= result[k];
            }
        }
    }
    return result;
}

bool OptimizedRelations::hasPrereqCycle() const {
    auto closure = closurePrereq();
    for (int i = 0; i < size; i++) {
        if (closure[i].test(i)) return true;
    }
    return false;
}

int OptimizedRelations::countPrereqs(int course) const {
    return prereqBits[course].count();
}

vector<vector<bool>> OptimizedRelations::toMatrix() const {
    vector<vector<bool>> matrix(size, vector<bool>(size, false));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = prereqBits[i].test(j);
        }
    }
    return matrix;
}

Relations::Relations() : size(0) {}

void Relations::ensureSize(int n) {
    if (n > size) {
        prereq.resize(n, vector<bool>(n, false));
        size = n;
    }
}

void Relations::addPrereq(int a, int b) {
    ensureSize(max(a, b) + 1);
    prereq[a][b] = true;
}

bool Relations::getPrereq(int a, int b) const {
    if (a < 0 || b < 0 || a >= size || b >= size) return false;
    return prereq[a][b];
}

int Relations::getSize() const {
    return size;
}

vector<vector<bool>> Relations::closurePrereq() const {
    vector<vector<bool>> result = prereq;

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (result[i][k] && result[k][j]) {
                    result[i][j] = true;
                }
            }
        }
    }
    return result;
}

bool Relations::hasPrereqCycle() const {
    auto closure = closurePrereq();
    for (int i = 0; i < size; i++) {
        if (closure[i][i]) return true;
    }
    return false;
}

const vector<vector<bool>>& Relations::getPrereqMatrix() const {
    return prereq;
}

bool Relations::isReflexive() const {
    for (int i = 0; i < size; i++) {
        if (!prereq[i][i]) return false;
    }
    return true;
}

bool Relations::isSymmetric() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (prereq[i][j] != prereq[j][i]) return false;
        }
    }
    return true;

}

bool Relations::isTransitive() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                if (prereq[i][j] && prereq[j][k] && !prereq[i][k]) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Relations::isAntiSymmetric() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j && prereq[i][j] && prereq[j][i]) {
                return false;
            }
        }
    }
    return true;
}

bool Relations::isEquivalenceRelation() const {
    return isReflexive() && isSymmetric() && isTransitive();
}

bool Relations::isPartialOrder() const {
    return isReflexive() && isTransitive() && isAntiSymmetric();
}

void MemoizationCache::clearAll() {
    prereqCache.clear();
    reachableCache.clear();
}

bool MemoizationCache::hasPrereqCached(int student, int course) const {
    return prereqCache.contains(make_pair(student, course));
}

bool MemoizationCache::getPrereqCached(int student, int course) const {
    const bool* val = prereqCache.get(make_pair(student, course));
    return val ? *val : false;
}

void MemoizationCache::cachePrereq(int student, int course, bool value) {
    prereqCache.insert(make_pair(student, course), value);
}

bool MemoizationCache::hasReachableCached(int course) const {
    return reachableCache.contains(course);
}

vector<int> MemoizationCache::getReachableCached(int course) const {
    const vector<int>* val = reachableCache.get(course);
    return val ? *val : vector<int>();
}

void MemoizationCache::cacheReachable(int course, const vector<int>& reachable) {
    reachableCache.insert(course, reachable);
}

void MemoizationCache::displayStats() const {
    cout << "\nCache Statistics:\n";
    cout << "  Prerequisite cache: " << prereqCache.size() << " entries\n";
    cout << "  Reachable cache: " << reachableCache.size() << " entries\n";
}