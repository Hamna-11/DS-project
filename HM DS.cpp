// ============================================================================
// FAST UNIVERSITY MANAGEMENT SYSTEM - COMPLETE MODULES 1-6
// Foundation: Courses, Students, Faculty, Rooms, Relations, Basic Operations
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

// ============================================================================
// UTILITY: Custom Set Implementation
// ============================================================================
template<typename T>
class CustomSet {
private:
    vector<T> data;

public:
    void insert(const T& val) {
        if (find(data.begin(), data.end(), val) == data.end()) {
            data.push_back(val);
        }
    }

    bool contains(const T& val) const {
        return find(data.begin(), data.end(), val) != data.end();
    }

    void erase(const T& val) {
        auto it = find(data.begin(), data.end(), val);
        if (it != data.end()) {
            data.erase(it);
        }
    }

    int size() const { return data.size(); }
    bool empty() const { return data.empty(); }
    void clear() { data.clear(); }

    typename vector<T>::iterator begin() { return data.begin(); }
    typename vector<T>::iterator end() { return data.end(); }
    typename vector<T>::const_iterator begin() const { return data.begin(); }
    typename vector<T>::const_iterator end() const { return data.end(); }

    const vector<T>& getVector() const { return data; }
};

// ============================================================================
// UTILITY: Custom Map Implementation
// ============================================================================
template<typename K, typename V>
class CustomMap {
private:
    vector<pair<K, V>> data;

public:
    void insert(const K& key, const V& val) {
        for (auto& p : data) {
            if (p.first == key) {
                p.second = val;
                return;
            }
        }
        data.push_back(make_pair(key, val));
    }

    bool contains(const K& key) const {
        for (const auto& p : data) {
            if (p.first == key) return true;
        }
        return false;
    }

    V* get(const K& key) {
        for (auto& p : data) {
            if (p.first == key) return &p.second;
        }
        return nullptr;
    }

    const V* get(const K& key) const {
        for (const auto& p : data) {
            if (p.first == key) return &p.second;
        }
        return nullptr;
    }

    V& operator[](const K& key) {
        for (auto& p : data) {
            if (p.first == key) return p.second;
        }
        data.push_back(make_pair(key, V()));
        return data.back().second;
    }

    void erase(const K& key) {
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it->first == key) {
                data.erase(it);
                return;
            }
        }
    }

    int size() const { return data.size(); }
    bool empty() const { return data.empty(); }
    void clear() { data.clear(); }

    typename vector<pair<K, V>>::iterator begin() { return data.begin(); }
    typename vector<pair<K, V>>::iterator end() { return data.end(); }
    typename vector<pair<K, V>>::const_iterator begin() const { return data.begin(); }
    typename vector<pair<K, V>>::const_iterator end() const { return data.end(); }
};

// ============================================================================
// UTILITY: Display Helper
// ============================================================================
class DisplayHelper {
public:
    static void printHeader(const string& title) {
        cout << "\n" << string(60, '=') << "\n";
        cout << "  " << title << "\n";
        cout << string(60, '=') << "\n";
    }

    static void printSuccess(const string& msg) {
        cout << "[SUCCESS] " << msg << "\n";
    }

    static void printError(const string& msg) {
        cout << "[ERROR] " << msg << "\n";
    }

    static void printWarning(const string& msg) {
        cout << "[WARNING] " << msg << "\n";
    }

    static void printInfo(const string& msg) {
        cout << "[INFO] " << msg << "\n";
    }
};

// ============================================================================
// MODULE 1: COURSE & SCHEDULING - Course Manager
// ============================================================================
class CourseManager {
public:
    struct Course {
        int id;
        string code;
        string name;
        int credits;
        bool active;

        Course() : id(-1), credits(0), active(false) {}
        Course(int i, string c, string n, int cr)
            : id(i), code(c), name(n), credits(cr), active(true) {}
    };

private:
    vector<Course> courses;
    CustomMap<string, int> codeToId;

public:
    int addCourse(const string& code, const string& name, int credits) {
        if (codeToId.contains(code)) {
            DisplayHelper::printError("Course code already exists!");
            return -1;
        }

        int id = courses.size();
        courses.push_back(Course(id, code, name, credits));
        codeToId.insert(code, id);

        DisplayHelper::printSuccess("Added course: " + code);
        return id;
    }

    const Course* getCourse(int id) const {
        if (id < 0 || id >= (int)courses.size()) return nullptr;
        return &courses[id];
    }

    int getCourseByCode(const string& code) const {
        const int* id = codeToId.get(code);
        return id ? *id : -1;
    }

    int count() const { return courses.size(); }

    void listAll() const {
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

    const vector<Course>& getAllCourses() const { return courses; }
};

// ============================================================================
// MODULE 2: STUDENT GROUP COMBINATIONS - People Manager
// ============================================================================
class PeopleManager {
public:
    struct Student {
        int id;
        string name;
        vector<int> enrolled;

        Student() : id(-1) {}
        Student(int i, string n) : id(i), name(n) {}
    };

    struct Faculty {
        int id;
        string name;
        vector<int> courses;

        Faculty() : id(-1) {}
        Faculty(int i, string n) : id(i), name(n) {}
    };

    struct Room {
        int id;
        string name;
        int capacity;

        Room() : id(-1), capacity(30) {}
        Room(int i, string n, int cap = 30) : id(i), name(n), capacity(cap) {}
    };

private:
    vector<Student> students;
    vector<Faculty> faculties;
    vector<Room> rooms;

public:
    int addStudent(const string& name) {
        int id = students.size();
        students.push_back(Student(id, name));
        DisplayHelper::printSuccess("Added student: " + name);
        return id;
    }

    int addFaculty(const string& name) {
        int id = faculties.size();
        faculties.push_back(Faculty(id, name));
        DisplayHelper::printSuccess("Added faculty: " + name);
        return id;
    }

    int addRoom(const string& name, int capacity = 30) {
        int id = rooms.size();
        rooms.push_back(Room(id, name, capacity));
        DisplayHelper::printSuccess("Added room: " + name);
        return id;
    }

    Student* getStudent(int id) {
        if (id < 0 || id >= (int)students.size()) return nullptr;
        return &students[id];
    }

    Faculty* getFaculty(int id) {
        if (id < 0 || id >= (int)faculties.size()) return nullptr;
        return &faculties[id];
    }

    Room* getRoom(int id) {
        if (id < 0 || id >= (int)rooms.size()) return nullptr;
        return &rooms[id];
    }

    int getStudentCount() const { return students.size(); }
    int getFacultyCount() const { return faculties.size(); }
    int getRoomCount() const { return rooms.size(); }

    void listAllStudents() const {
        DisplayHelper::printHeader("ALL STUDENTS");
        cout << "\n" << left << setw(5) << "ID" << setw(25) << "Name"
            << "Enrolled Courses\n";
        cout << string(60, '-') << "\n";

        for (const auto& s : students) {
            cout << left << setw(5) << s.id << setw(25) << s.name << "[ ";
            for (size_t i = 0; i < s.enrolled.size(); i++) {
                cout << s.enrolled[i];
                if (i < s.enrolled.size() - 1) cout << ", ";
            }
            cout << " ]\n";
        }
        cout << "\nTotal Students: " << students.size() << "\n";
    }

    void listAllFaculties() const {
        DisplayHelper::printHeader("ALL FACULTY");
        cout << "\n" << left << setw(5) << "ID" << setw(25) << "Name"
            << "Teaching Courses\n";
        cout << string(60, '-') << "\n";

        for (const auto& f : faculties) {
            cout << left << setw(5) << f.id << setw(25) << f.name << "[ ";
            for (size_t i = 0; i < f.courses.size(); i++) {
                cout << f.courses[i];
                if (i < f.courses.size() - 1) cout << ", ";
            }
            cout << " ]\n";
        }
        cout << "\nTotal Faculty: " << faculties.size() << "\n";
    }

    void listAllRooms() const {
        DisplayHelper::printHeader("ALL ROOMS");
        cout << "\n" << left << setw(5) << "ID" << setw(20) << "Name"
            << "Capacity\n";
        cout << string(40, '-') << "\n";

        for (const auto& r : rooms) {
            cout << left << setw(5) << r.id << setw(20) << r.name
                << r.capacity << "\n";
        }
        cout << "\nTotal Rooms: " << rooms.size() << "\n";
    }
};

// Forward declarations
class Relations;

// ============================================================================
// MODULE 3: INDUCTION & STRONG INDUCTION - Scheduling with Topological Sort
// ============================================================================
class Scheduling {
private:
    const Relations& relations;
    vector<vector<int>> validOrders;

    void backtrack(const vector<vector<bool>>& adj, vector<bool>& used,
        vector<int>& order, int n, int limit) {
        if ((int)validOrders.size() >= limit) return;

        if ((int)order.size() == n) {
            validOrders.push_back(order);
            return;
        }

        for (int i = 0; i < n; i++) {
            if (used[i]) continue;

            bool hasIncoming = false;
            for (int j = 0; j < n; j++) {
                if (!used[j] && adj[j][i]) {
                    hasIncoming = true;
                    break;
                }
            }

            if (!hasIncoming) {
                used[i] = true;
                order.push_back(i);
                backtrack(adj, used, order, n, limit);
                order.pop_back();
                used[i] = false;
            }
        }
    }

public:
    Scheduling(const Relations& r);

    int generateOrders(int n, int limit = 500);
    void displayOrders(const CourseManager& cm, int maxDisplay = 20) const;
    const vector<vector<int>>& getOrders() const { return validOrders; }
};

// ============================================================================
// MODULE 4: LOGIC & INFERENCE ENGINE
// ============================================================================
class LogicEngine {
public:
    struct Rule {
        string name;
        vector<int> antecedent;
        vector<int> consequent;
        string description;
    };

private:
    vector<Rule> rules;
    CustomMap<string, bool> facts;

public:
    void addRule(const string& name, const vector<int>& ante,
        const vector<int>& cons, const string& desc) {
        rules.push_back({ name, ante, cons, desc });
        DisplayHelper::printSuccess("Added rule: " + name);
    }

    void addFact(const string& fact, bool value = true) {
        facts.insert(fact, value);
    }

    bool checkRule(const Rule& rule) const {
        for (int a : rule.antecedent) {
            string key = "course_" + to_string(a);
            const bool* val = facts.get(key);
            if (!val || !(*val)) return false;
        }
        return true;
    }

    vector<string> inferConsequences() {
        vector<string> inferred;
        bool changed = true;

        while (changed) {
            changed = false;
            for (const auto& rule : rules) {
                if (checkRule(rule)) {
                    for (int c : rule.consequent) {
                        string key = "course_" + to_string(c);
                        const bool* val = facts.get(key);
                        if (!val || !(*val)) {
                            facts.insert(key, true);
                            inferred.push_back("Inferred: " + rule.description);
                            changed = true;
                        }
                    }
                }
            }
        }

        return inferred;
    }

    void displayRules() const {
        DisplayHelper::printHeader("LOGIC RULES");

        for (size_t i = 0; i < rules.size(); i++) {
            cout << "\nRule " << (i + 1) << ": " << rules[i].name << "\n";
            cout << "  IF: ";
            for (size_t j = 0; j < rules[i].antecedent.size(); j++) {
                cout << "Course(" << rules[i].antecedent[j] << ")";
                if (j < rules[i].antecedent.size() - 1) cout << " AND ";
            }
            cout << "\n  THEN: ";
            for (size_t j = 0; j < rules[i].consequent.size(); j++) {
                cout << "Course(" << rules[i].consequent[j] << ")";
                if (j < rules[i].consequent.size() - 1) cout << " AND ";
            }
            cout << "\n  Description: " << rules[i].description << "\n";
        }
    }

    void displayFacts() const {
        DisplayHelper::printHeader("CURRENT FACTS");

        for (const auto& pair : facts) {
            cout << pair.first << " = " << (pair.second ? "TRUE" : "FALSE") << "\n";
        }
    }
};

// ============================================================================
// MODULE 5: SET OPERATIONS
// ============================================================================
class SetOps {
public:
    static CustomSet<int> unionSet(const CustomSet<int>& A, const CustomSet<int>& B) {
        CustomSet<int> result;
        for (int x : A.getVector()) result.insert(x);
        for (int x : B.getVector()) result.insert(x);
        return result;
    }

    static CustomSet<int> intersection(const CustomSet<int>& A, const CustomSet<int>& B) {
        CustomSet<int> result;
        for (int x : A.getVector()) {
            if (B.contains(x)) result.insert(x);
        }
        return result;
    }

    static CustomSet<int> difference(const CustomSet<int>& A, const CustomSet<int>& B) {
        CustomSet<int> result;
        for (int x : A.getVector()) {
            if (!B.contains(x)) result.insert(x);
        }
        return result;
    }

    static CustomSet<int> symmetricDifference(const CustomSet<int>& A, const CustomSet<int>& B) {
        CustomSet<int> result;
        for (int x : A.getVector()) {
            if (!B.contains(x)) result.insert(x);
        }
        for (int x : B.getVector()) {
            if (!A.contains(x)) result.insert(x);
        }
        return result;
    }

    static vector<CustomSet<int>> powerSet(const CustomSet<int>& S) {
        vector<CustomSet<int>> result;
        vector<int> elements = S.getVector();
        int n = elements.size();

        for (int mask = 0; mask < (1 << n); mask++) {
            CustomSet<int> subset;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    subset.insert(elements[i]);
                }
            }
            result.push_back(subset);
        }
        return result;
    }

    static void display(const CourseManager& cm, int s1, int s2, PeopleManager& pm);

private:
    static void displaySet(const CustomSet<int>& s, const CourseManager& cm) {
        cout << "{ ";
        bool first = true;
        for (int id : s.getVector()) {
            if (!first) cout << ", ";
            const auto* c = cm.getCourse(id);
            cout << (c ? c->code : to_string(id));
            first = false;
        }
        cout << " }\n";
    }
};

// ============================================================================
// MODULE 6: RELATIONS
// ============================================================================
class Relations {
private:
    vector<vector<bool>> prereq;
    vector<vector<bool>> implication;
    int size;

public:
    Relations() : size(0) {}

    void ensureSize(int n) {
        if (n > size) {
            prereq.resize(n, vector<bool>(n, false));
            implication.resize(n, vector<bool>(n, false));
            size = n;
        }
    }

    void addPrereq(int a, int b) {
        ensureSize(max(a, b) + 1);
        prereq[a][b] = true;
    }

    void addImplication(int a, int b) {
        ensureSize(max(a, b) + 1);
        implication[a][b] = true;
    }

    bool getPrereq(int a, int b) const {
        if (a < 0 || b < 0 || a >= size || b >= size) return false;
        return prereq[a][b];
    }

    int getSize() const { return size; }

    // Transitive closure (Floyd-Warshall)
    vector<vector<bool>> closurePrereq() const {
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

    bool hasPrereqCycle() const {
        auto closure = closurePrereq();
        for (int i = 0; i < size; i++) {
            if (closure[i][i]) return true;
        }
        return false;
    }

    bool isReflexive() const {
        for (int i = 0; i < size; i++) {
            if (!prereq[i][i]) return false;
        }
        return true;
    }

    bool isSymmetric() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (prereq[i][j] != prereq[j][i]) return false;
            }
        }
        return true;
    }

    bool isTransitive() const {
        auto closure = closurePrereq();
        return closure == prereq;
    }

    bool isEquivalence() const {
        return isReflexive() && isSymmetric() && isTransitive();
    }

    bool isPartialOrder() const {
        return isReflexive() && !isSymmetric() && isTransitive();
    }

    void displayMatrix(const CourseManager& cm) const {
        DisplayHelper::printHeader("PREREQUISITE MATRIX");

        cout << "\n     ";
        for (int i = 0; i < size; i++) {
            const auto* c = cm.getCourse(i);
            cout << setw(6) << (c ? c->code : to_string(i));
        }
        cout << "\n";

        for (int i = 0; i < size; i++) {
            const auto* c = cm.getCourse(i);
            cout << setw(5) << (c ? c->code : to_string(i));
            for (int j = 0; j < size; j++) {
                cout << setw(6) << (prereq[i][j] ? "Y" : ".");
            }
            cout << "\n";
        }

        cout << "\nY = Has prerequisite | . = No relationship\n";
    }

    const vector<vector<bool>>& getPrereqMatrix() const { return prereq; }
};

// ============================================================================
// INDUCTION MODULE IMPLEMENTATION
// ============================================================================
class Induction {
private:
    const Relations& relations;

    bool dfsCheck(int courseId, const vector<bool>& completed,
        vector<bool>& visited, const vector<vector<bool>>& prereq) const {
        if (courseId >= 0 && courseId < (int)completed.size() && completed[courseId])
            return true;
        if (visited[courseId]) return false;

        visited[courseId] = true;

        for (int i = 0; i < (int)prereq.size(); i++) {
            if (prereq[i][courseId]) {
                if (!dfsCheck(i, completed, visited, prereq)) {
                    return false;
                }
            }
        }

        return completed[courseId];
    }

public:
    Induction(const Relations& r) : relations(r) {}

    bool checkRecursive(int courseId, const vector<bool>& completed) const {
        auto prereq = relations.getPrereqMatrix();
        vector<bool> visited(prereq.size(), false);
        return dfsCheck(courseId, completed, visited, prereq);
    }

    bool checkStrong(int courseId, const vector<bool>& completed) const {
        auto closure = relations.closurePrereq();

        for (int i = 0; i < (int)closure.size(); i++) {
            if (closure[i][courseId] && !completed[i]) {
                return false;
            }
        }
        return true;
    }

    vector<int> listIndirect(int courseId) const {
        auto closure = relations.closurePrereq();
        vector<int> result;

        for (int i = 0; i < (int)closure.size(); i++) {
            if (closure[i][courseId]) {
                result.push_back(i);
            }
        }
        return result;
    }

    void displayCheck(const CourseManager& cm, int courseId,
        const vector<bool>& completed) const {
        DisplayHelper::printHeader("INDUCTION VERIFICATION");

        const auto* c = cm.getCourse(courseId);
        cout << "\nChecking prerequisites for: ";
        if (c) cout << c->code << " (" << c->name << ")\n";
        else cout << "Course #" << courseId << "\n";

        cout << "\n--- Completed Courses ---\n";
        for (int i = 0; i < (int)completed.size(); i++) {
            if (completed[i]) {
                const auto* cc = cm.getCourse(i);
                if (cc) cout << cc->code << " ";
            }
        }
        cout << "\n\n";

        bool rec = checkRecursive(courseId, completed);
        cout << "RECURSIVE INDUCTION:  " << (rec ? "[PASS]" : "[FAIL]") << "\n";

        bool strong = checkStrong(courseId, completed);
        cout << "STRONG INDUCTION:     " << (strong ? "[PASS]" : "[FAIL]") << "\n";

        auto indirect = listIndirect(courseId);
        if (!indirect.empty()) {
            cout << "\n--- All Prerequisites (Direct + Indirect) ---\n";
            for (int id : indirect) {
                const auto* pc = cm.getCourse(id);
                cout << (pc ? pc->code : to_string(id)) << " ";
                cout << (completed[id] ? "[DONE]" : "[MISSING]") << "\n";
            }
        }
        cout << "\n";
    }
};

// ============================================================================
// STUDENT GROUP COMBINATIONS
// ============================================================================
class StudentGroupModule {
private:
    vector<string> students;
    vector<vector<string>> groups;

    void generateCombinations(int start, int k, vector<string>& current) {
        if ((int)current.size() == k) {
            groups.push_back(current);
            return;
        }

        for (int i = start; i < (int)students.size(); i++) {
            current.push_back(students[i]);
            generateCombinations(i + 1, k, current);
            current.pop_back();
        }
    }

    long long nCr(int n, int r) const {
        if (r > n || r < 0) return 0;
        if (r == 0 || r == n) return 1;
        long long result = 1;
        for (int i = 0; i < r; i++) {
            result *= (n - i);
            result /= (i + 1);
        }
        return result;
    }

public:
    bool addStudent(const string& name) {
        if (find(students.begin(), students.end(), name) != students.end()) {
            DisplayHelper::printWarning("Student already exists!");
            return false;
        }
        students.push_back(name);
        DisplayHelper::printSuccess("Added student: " + name);
        return true;
    }

    void display() const {
        DisplayHelper::printHeader("STUDENT LIST");

        for (size_t i = 0; i < students.size(); i++) {
            cout << (i + 1) << ". " << students[i] << "\n";
        }
        cout << "\nTotal: " << students.size() << "\n";
    }

    void displayCombinations(int groupSize) {
        DisplayHelper::printHeader("GROUP COMBINATIONS");

        if (groupSize <= 0 || groupSize > (int)students.size()) {
            DisplayHelper::printError("Invalid group size!");
            return;
        }

        groups.clear();
        vector<string> current;
        generateCombinations(0, groupSize, current);

        cout << "\nGroup Size: " << groupSize << "\n";
        cout << "Total Combinations: " << groups.size() << "\n";
        cout << "Formula: C(" << students.size() << "," << groupSize << ") = "
            << nCr(students.size(), groupSize) << "\n\n";

        int display = min(30, (int)groups.size());
        for (int i = 0; i < display; i++) {
            cout << "Group #" << (i + 1) << ": ";
            for (size_t j = 0; j < groups[i].size(); j++) {
                cout << groups[i][j];
                if (j < groups[i].size() - 1) cout << ", ";
            }
            cout << "\n";
        }

        if ((int)groups.size() > 30) {
            cout << "\n... and " << (groups.size() - 30) << " more\n";
        }
    }
};

// ============================================================================
// SCHEDULING IMPLEMENTATION
// ============================================================================
Scheduling::Scheduling(const Relations& r) : relations(r) {}

int Scheduling::generateOrders(int n, int limit) {
    validOrders.clear();
    if (n <= 0) return 0;

    auto adj = relations.getPrereqMatrix();
    vector<bool> used(n, false);
    vector<int> order;

    backtrack(adj, used, order, n, limit);
    return validOrders.size();
}

void Scheduling::displayOrders(const CourseManager& cm, int maxDisplay) const {
    DisplayHelper::printHeader("VALID COURSE SEQUENCES");

    cout << "\nTotal sequences found: " << validOrders.size() << "\n\n";

    int display = min(maxDisplay, (int)validOrders.size());
    for (int i = 0; i < display; i++) {
        cout << "Sequence #" << (i + 1) << ": ";
        for (size_t j = 0; j < validOrders[i].size(); j++) {
            const auto* c = cm.getCourse(validOrders[i][j]);
            if (c) cout << c->code;
            else cout << validOrders[i][j];
            if (j < validOrders[i].size() - 1) cout << " -> ";
        }
        cout << "\n";
    }

    if ((int)validOrders.size() > maxDisplay) {
        cout << "\n... and " << (validOrders.size() - maxDisplay)
            << " more sequences\n";
    }
}

// ============================================================================
// SET OPERATIONS DISPLAY IMPLEMENTATION
// ============================================================================
void SetOps::display(const CourseManager& cm, int s1, int s2, PeopleManager& pm) {
    DisplayHelper::printHeader("SET OPERATIONS");

    auto* st1 = pm.getStudent(s1);
    auto* st2 = pm.getStudent(s2);

    if (!st1 || !st2) {
        DisplayHelper::printError("Invalid student IDs!");
        return;
    }

    CustomSet<int> A, B;
    for (int x : st1->enrolled) A.insert(x);
    for (int x : st2->enrolled) B.insert(x);

    cout << "\nStudent 1: " << st1->name << " -> ";
    displaySet(A, cm);
    cout << "Student 2: " << st2->name << " -> ";
    displaySet(B, cm);

    cout << "\n--- Operations ---\n";
    cout << "UNION (A U B): ";
    displaySet(unionSet(A, B), cm);

    cout << "INTERSECTION (A n B): ";
    displaySet(intersection(A, B), cm);

    cout << "DIFFERENCE (A - B): ";
    displaySet(difference(A, B), cm);

    cout << "SYMMETRIC DIFF (A ^ B): ";
    displaySet(symmetricDifference(A, B), cm);

    cout << "\n";
}

// ============================================================================
// MAIN PROGRAM
// ============================================================================
int main() {
    CourseManager cm;
    PeopleManager pm;
    Relations rel;
    StudentGroupModule groupModule;
    LogicEngine logic;

    CustomMap<int, int> courseToFaculty;
    CustomMap<int, int> courseToRoom;

    cout << string(60, '=') << "\n";
    cout << "  FAST UNIVERSITY MANAGEMENT SYSTEM - PART 1\n";
    cout << "  Modules 1-6: Foundation & Basic Operations\n";
    cout << string(60, '=') << "\n";

    while (true) {
        cout << "\n========== MAIN MENU (PART 1) ==========\n";
        cout << "BASIC OPERATIONS:\n";
        cout << " 1. Add Course\n";
        cout << " 2. Add Student\n";
        cout << " 3. Add Faculty\n";
        cout << " 4. Add Room\n";
        cout << " 5. Add Prerequisite\n";
        cout << " 6. Assign Faculty to Course\n";
        cout << " 7. Assign Room to Course\n";
        cout << " 8. Enroll Student\n";
        cout << " 9. List All Data\n";
        cout << "\nMODULE 1-6 OPERATIONS:\n";
        cout << "10. Course Scheduling (Module 1 & 3)\n";
        cout << "11. Student Group Combinations (Module 2)\n";
        cout << "12. Induction Check (Module 3)\n";
        cout << "13. Logic & Inference (Module 4)\n";
        cout << "14. Set Operations (Module 5)\n";
        cout << "15. Relations Analysis (Module 6)\n";
        cout << "\n 0. Exit\n";
        cout << "\nChoice: ";

        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "\n" << string(60, '=') << "\n";
            cout << "  Thank you for using FAST System!\n";
            cout << string(60, '=') << "\n";
            break;
        }

        switch (choice) {
        case 1: {
            string code, name;
            int credits;
            cout << "Course code: ";
            cin >> code;
            cout << "Course name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Credits: ";
            cin >> credits;

            cm.addCourse(code, name, credits);
            rel.ensureSize(cm.count());
            break;
        }

        case 2: {
            string name;
            cout << "Student name: ";
            cin.ignore();
            getline(cin, name);
            pm.addStudent(name);
            break;
        }

        case 3: {
            string name;
            cout << "Faculty name: ";
            cin.ignore();
            getline(cin, name);
            pm.addFaculty(name);
            break;
        }

        case 4: {
            string name;
            int capacity;
            cout << "Room name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Capacity: ";
            cin >> capacity;
            pm.addRoom(name, capacity);
            break;
        }

        case 5: {
            int a, b;
            cout << "Prerequisite course ID: ";
            cin >> a;
            cout << "Dependent course ID: ";
            cin >> b;

            if (a >= 0 && a < cm.count() && b >= 0 && b < cm.count()) {
                rel.addPrereq(a, b);
                DisplayHelper::printSuccess("Prerequisite added");
            }
            else {
                DisplayHelper::printError("Invalid course IDs");
            }
            break;
        }

        case 6: {
            int c, f;
            cout << "Course ID: ";
            cin >> c;
            cout << "Faculty ID: ";
            cin >> f;

            if (c >= 0 && c < cm.count() && f >= 0 && f < pm.getFacultyCount()) {
                courseToFaculty.insert(c, f);
                auto* fac = pm.getFaculty(f);
                if (fac) fac->courses.push_back(c);
                DisplayHelper::printSuccess("Faculty assigned");
            }
            else {
                DisplayHelper::printError("Invalid IDs");
            }
            break;
        }

        case 7: {
            int c, r;
            cout << "Course ID: ";
            cin >> c;
            cout << "Room ID: ";
            cin >> r;

            if (c >= 0 && c < cm.count() && r >= 0 && r < pm.getRoomCount()) {
                courseToRoom.insert(c, r);
                DisplayHelper::printSuccess("Room assigned");
            }
            else {
                DisplayHelper::printError("Invalid IDs");
            }
            break;
        }

        case 8: {
            int s, c;
            cout << "Student ID: ";
            cin >> s;
            cout << "Course ID: ";
            cin >> c;

            auto* student = pm.getStudent(s);
            if (student && c >= 0 && c < cm.count()) {
                student->enrolled.push_back(c);
                DisplayHelper::printSuccess("Student enrolled");
            }
            else {
                DisplayHelper::printError("Invalid IDs");
            }
            break;
        }

        case 9: {
            cout << "\n1. Courses  2. Students  3. Faculty  4. Rooms\nChoice: ";
            int sub;
            cin >> sub;
            if (sub == 1) cm.listAll();
            else if (sub == 2) pm.listAllStudents();
            else if (sub == 3) pm.listAllFaculties();
            else if (sub == 4) pm.listAllRooms();
            break;
        }

        case 10: {
            if (rel.hasPrereqCycle()) {
                DisplayHelper::printError("Cycle detected!");
            }
            else {
                Scheduling sched(rel);
                sched.generateOrders(cm.count(), 500);
                sched.displayOrders(cm, 30);
            }
            break;
        }

        case 11: {
            cout << "\n1. Add Student  2. Show Students  3. Generate Groups\nChoice: ";
            int sub;
            cin >> sub;

            if (sub == 1) {
                string name;
                cout << "Student name: ";
                cin.ignore();
                getline(cin, name);
                groupModule.addStudent(name);
            }
            else if (sub == 2) {
                groupModule.display();
            }
            else if (sub == 3) {
                int size;
                cout << "Group size: ";
                cin >> size;
                groupModule.displayCombinations(size);
            }
            break;
        }

        case 12: {
            int c;
            cout << "Course ID to check: ";
            cin >> c;

            if (c >= 0 && c < cm.count()) {
                vector<bool> completed(cm.count(), false);
                cout << "Enter completed course IDs (-1 to stop): ";
                int x;
                while (cin >> x && x != -1) {
                    if (x >= 0 && x < cm.count()) completed[x] = true;
                }

                Induction ind(rel);
                ind.displayCheck(cm, c, completed);
            }
            else {
                DisplayHelper::printError("Invalid course ID");
            }
            break;
        }

        case 13: {
            cout << "\n1. Add Logic Rule\n";
            cout << "2. Add Fact\n";
            cout << "3. Run Inference\n";
            cout << "4. Display Rules\n";
            cout << "5. Display Facts\n";
            cout << "Choice: ";

            int sub;
            cin >> sub;

            if (sub == 1) {
                string name, desc;
                cout << "Rule name: ";
                cin >> name;
                cin.ignore();
                cout << "Description: ";
                getline(cin, desc);

                cout << "Number of antecedent courses: ";
                int n;
                cin >> n;
                vector<int> ante(n);
                cout << "Enter course IDs: ";
                for (int i = 0; i < n; i++) cin >> ante[i];

                cout << "Number of consequent courses: ";
                int m;
                cin >> m;
                vector<int> cons(m);
                cout << "Enter course IDs: ";
                for (int i = 0; i < m; i++) cin >> cons[i];

                logic.addRule(name, ante, cons, desc);
            }
            else if (sub == 2) {
                string fact;
                cout << "Fact name: ";
                cin >> fact;
                logic.addFact(fact, true);
                DisplayHelper::printSuccess("Fact added");
            }
            else if (sub == 3) {
                auto inferred = logic.inferConsequences();
                DisplayHelper::printHeader("INFERENCE RESULTS");
                if (inferred.empty()) {
                    cout << "No new inferences made.\n";
                }
                else {
                    for (const auto& i : inferred) {
                        cout << "-> " << i << "\n";
                    }
                }
            }
            else if (sub == 4) {
                logic.displayRules();
            }
            else if (sub == 5) {
                logic.displayFacts();
            }
            break;
        }

        case 14: {
            int s1, s2;
            cout << "First student ID: ";
            cin >> s1;
            cout << "Second student ID: ";
            cin >> s2;

            if (s1 >= 0 && s1 < pm.getStudentCount() &&
                s2 >= 0 && s2 < pm.getStudentCount()) {
                SetOps::display(cm, s1, s2, pm);
            }
            else {
                DisplayHelper::printError("Invalid student IDs");
            }
            break;
        }

        case 15: {
            cout << "\n1. Display Prerequisite Matrix\n";
            cout << "2. Check Relation Properties\n";
            cout << "3. Display Transitive Closure\n";
            cout << "Choice: ";

            int sub;
            cin >> sub;

            if (sub == 1) {
                rel.displayMatrix(cm);
            }
            else if (sub == 2) {
                DisplayHelper::printHeader("RELATION PROPERTIES");

                cout << "\nPrerequisite Relation Analysis:\n";
                cout << "  Reflexive:   " << (rel.isReflexive() ? "[YES]" : "[NO]") << "\n";
                cout << "  Symmetric:   " << (rel.isSymmetric() ? "[YES]" : "[NO]") << "\n";
                cout << "  Transitive:  " << (rel.isTransitive() ? "[YES]" : "[NO]") << "\n";
                cout << "  Equivalence: " << (rel.isEquivalence() ? "[YES]" : "[NO]") << "\n";
                cout << "  Partial Order: " << (rel.isPartialOrder() ? "[YES]" : "[NO]") << "\n";
                cout << "  Has Cycles:  " << (rel.hasPrereqCycle() ? "[YES]" : "[NO]") << "\n";
                cout << "\n";
            }
            else if (sub == 3) {
                auto closure = rel.closurePrereq();
                DisplayHelper::printHeader("TRANSITIVE CLOSURE");

                cout << "\n     ";
                for (int i = 0; i < rel.getSize(); i++) {
                    const auto* c = cm.getCourse(i);
                    cout << setw(6) << (c ? c->code : to_string(i));
                }
                cout << "\n";

                for (int i = 0; i < rel.getSize(); i++) {
                    const auto* c = cm.getCourse(i);
                    cout << setw(5) << (c ? c->code : to_string(i));
                    for (int j = 0; j < rel.getSize(); j++) {
                        cout << setw(6) << (closure[i][j] ? "Y" : ".");
                    }
                    cout << "\n";
                }
                cout << "\n";
            }
            break;
        }

        default:
            DisplayHelper::printError("Invalid choice!");
        }
    }

    return 0;
}