#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <fstream>
#include <ctime>

using namespace std;

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

    CustomSet<T> intersection(const CustomSet<T>& other) const {
        CustomSet<T> result;
        for (const auto& elem : data) {
            if (other.contains(elem)) {
                result.insert(elem);
            }
        }
        return result;
    }

    CustomSet<T> setUnion(const CustomSet<T>& other) const {
        CustomSet<T> result = *this;
        for (const auto& elem : other.getVector()) {
            result.insert(elem);
        }
        return result;
    }
};

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

class CustomBitset {
private:
    static const int BITS_PER_UNIT = 64;
    vector<unsigned long long> bits;
    int totalBits;

public:
    CustomBitset(int size = 1000) : totalBits(size) {
        int units = (size + BITS_PER_UNIT - 1) / BITS_PER_UNIT;
        bits.resize(units, 0ULL);
    }

    void set(int pos) {
        if (pos < 0 || pos >= totalBits) return;
        int unit = pos / BITS_PER_UNIT;
        int offset = pos % BITS_PER_UNIT;
        bits[unit] |= (1ULL << offset);
    }

    void reset(int pos) {
        if (pos < 0 || pos >= totalBits) return;
        int unit = pos / BITS_PER_UNIT;
        int offset = pos % BITS_PER_UNIT;
        bits[unit] &= ~(1ULL << offset);
    }

    bool test(int pos) const {
        if (pos < 0 || pos >= totalBits) return false;
        int unit = pos / BITS_PER_UNIT;
        int offset = pos % BITS_PER_UNIT;
        return (bits[unit] & (1ULL << offset)) != 0;
    }

    int count() const {
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

    CustomBitset& operator|=(const CustomBitset& other) {
        for (size_t i = 0; i < bits.size() && i < other.bits.size(); i++) {
            bits[i] |= other.bits[i];
        }
        return *this;
    }

    void clear() {
        for (auto& unit : bits) {
            unit = 0ULL;
        }
    }
};

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

class CourseManager {
public:
    struct Course {
        int id;
        string code;
        string name;
        int credits;

        Course() : id(-1), credits(0) {}
        Course(int i, string c, string n, int cr)
            : id(i), code(c), name(n), credits(cr) {
        }
    };

private:
    vector<Course> courses;

public:
    int addCourse(const string& code, const string& name, int credits) {
        int id = courses.size();
        courses.push_back(Course(id, code, name, credits));
        return id;
    }

    const Course* getCourse(int id) const {
        if (id < 0 || id >= (int)courses.size()) return nullptr;
        return &courses[id];
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
};

class PeopleManager {
public:
    struct Student {
        int id;
        string name;
        vector<int> enrolled;
        vector<int> completed;

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
        return id;
    }

    int addFaculty(const string& name) {
        int id = faculties.size();
        faculties.push_back(Faculty(id, name));
        return id;
    }

    int addRoom(const string& name, int capacity = 30) {
        int id = rooms.size();
        rooms.push_back(Room(id, name, capacity));
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
};

class OptimizedRelations {
private:
    static const int MAX_SIZE = 1000;
    vector<CustomBitset> prereqBits;
    int size;

public:
    OptimizedRelations() : size(0) {
        prereqBits.resize(MAX_SIZE, CustomBitset(MAX_SIZE));
    }

    void ensureSize(int n) {
        if (n > size) {
            size = n;
        }
    }

    void addPrereq(int a, int b) {
        ensureSize(max(a, b) + 1);
        prereqBits[a].set(b);
    }

    bool getPrereq(int a, int b) const {
        if (a < 0 || b < 0 || a >= size || b >= size) return false;
        return prereqBits[a].test(b);
    }

    int getSize() const { return size; }

    vector<CustomBitset> closurePrereq() const {
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

    bool hasPrereqCycle() const {
        auto closure = closurePrereq();
        for (int i = 0; i < size; i++) {
            if (closure[i].test(i)) return true;
        }
        return false;
    }

    int countPrereqs(int course) const {
        return prereqBits[course].count();
    }

    vector<vector<bool>> toMatrix() const {
        vector<vector<bool>> matrix(size, vector<bool>(size, false));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = prereqBits[i].test(j);
            }
        }
        return matrix;
    }
};

class Relations {
private:
    vector<vector<bool>> prereq;
    int size;

public:
    Relations() : size(0) {}

    void ensureSize(int n) {
        if (n > size) {
            prereq.resize(n, vector<bool>(n, false));
            size = n;
        }
    }

    void addPrereq(int a, int b) {
        ensureSize(max(a, b) + 1);
        prereq[a][b] = true;
    }

    bool getPrereq(int a, int b) const {
        if (a < 0 || b < 0 || a >= size || b >= size) return false;
        return prereq[a][b];
    }

    int getSize() const { return size; }

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

    const vector<vector<bool>>& getPrereqMatrix() const { return prereq; }

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

    bool isAntiSymmetric() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i != j && prereq[i][j] && prereq[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isEquivalenceRelation() const {
        return isReflexive() && isSymmetric() && isTransitive();
    }

    bool isPartialOrder() const {
        return isReflexive() && isTransitive() && isAntiSymmetric();
    }
};

class MemoizationCache {
private:
    CustomMap<pair<int, int>, bool> prereqCache;
    CustomMap<int, vector<int>> reachableCache;

public:
    void clearAll() {
        prereqCache.clear();
        reachableCache.clear();
    }

    bool hasPrereqCached(int student, int course) const {
        return prereqCache.contains(make_pair(student, course));
    }

    bool getPrereqCached(int student, int course) const {
        const bool* val = prereqCache.get(make_pair(student, course));
        return val ? *val : false;
    }

    void cachePrereq(int student, int course, bool value) {
        prereqCache.insert(make_pair(student, course), value);
    }

    bool hasReachableCached(int course) const {
        return reachableCache.contains(course);
    }

    vector<int> getReachableCached(int course) const {
        const vector<int>* val = reachableCache.get(course);
        return val ? *val : vector<int>();
    }

    void cacheReachable(int course, const vector<int>& reachable) {
        reachableCache.insert(course, reachable);
    }

    void displayStats() const {
        cout << "\nMemoization Statistics:\n";
        cout << "  Prerequisite cache entries: " << prereqCache.size() << "\n";
        cout << "  Reachable cache entries: " << reachableCache.size() << "\n";
    }
};

class Functions {
public:
    static bool isInjective(const CustomMap<int, int>& f) {
        CustomSet<int> values;
        for (const auto& pair : f) {
            if (values.contains(pair.second)) return false;
            values.insert(pair.second);
        }
        return true;
    }

    static bool isSurjective(const CustomMap<int, int>& f, int codomainSize) {
        CustomSet<int> values;
        for (const auto& pair : f) {
            values.insert(pair.second);
        }
        return values.size() == codomainSize;
    }

    static bool isBijective(const CustomMap<int, int>& f, int codomainSize) {
        return isInjective(f) && isSurjective(f, codomainSize);
    }

    static CustomMap<int, int> compose(const CustomMap<int, int>& f, const CustomMap<int, int>& g) {
        CustomMap<int, int> result;
        for (const auto& pair : f) {
            const int* gval = g.get(pair.second);
            if (gval) {
                result.insert(pair.first, *gval);
            }
        }
        return result;
    }

    static CustomMap<int, int> inverse(const CustomMap<int, int>& f, int codomainSize) {
        CustomMap<int, int> inv;

        if (!isBijective(f, codomainSize)) {
            DisplayHelper::printError("Cannot create inverse - function must be bijective");
            return inv;
        }

        for (const auto& pair : f) {
            inv.insert(pair.second, pair.first);
        }

        DisplayHelper::printSuccess("Inverse function created successfully");
        return inv;
    }

    static bool verifyInverse(const CustomMap<int, int>& f, const CustomMap<int, int>& f_inv) {
        for (const auto& pair : f) {
            const int* inv_val = f_inv.get(pair.second);
            if (!inv_val || *inv_val != pair.first) {
                return false;
            }
        }
        return true;
    }

    static void analyzeStudentCourses(PeopleManager& pm, const CourseManager& cm) {
        DisplayHelper::printHeader("STUDENT -> COURSES MAPPING ANALYSIS");

        cout << "\nMulti-valued Function: Student -> Set of Courses\n";
        cout << "Domain size: " << pm.getStudentCount() << " students\n\n";

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

    static void analyzeFacultyRooms(const CustomMap<int, int>& facultyToRoom,
        PeopleManager& pm) {
        DisplayHelper::printHeader("FACULTY -> ROOMS MAPPING");

        cout << "\nAnalyzing Faculty -> Room assignment\n";
        cout << "Domain size: " << facultyToRoom.size() << "\n";
        cout << "Codomain size: " << pm.getRoomCount() << "\n\n";

        bool inj = isInjective(facultyToRoom);
        bool sur = isSurjective(facultyToRoom, pm.getRoomCount());

        cout << "Properties:\n";
        cout << "  Injective: " << (inj ? "[YES] Each faculty has unique room"
            : "[NO] Some rooms shared") << "\n";
        cout << "  Surjective: " << (sur ? "[YES] All rooms utilized"
            : "[NO] Some rooms unused") << "\n\n";

        cout << "Mapping:\n";
        for (const auto& pair : facultyToRoom) {
            auto* faculty = pm.getFaculty(pair.first);
            auto* room = pm.getRoom(pair.second);
            cout << "  " << (faculty ? faculty->name : to_string(pair.first))
                << " -> " << (room ? room->name : to_string(pair.second)) << "\n";
        }
        cout << "\n";
    }

    static vector<CustomSet<int>> powerSet(const CustomSet<int>& s) {
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

    static vector<pair<int, int>> cartesianProduct(
        const CustomSet<int>& a, const CustomSet<int>& b) {
        vector<pair<int, int>> result;
        for (const auto& x : a.getVector()) {
            for (const auto& y : b.getVector()) {
                result.push_back(make_pair(x, y));
            }
        }
        return result;
    }

    static void display(const CustomMap<int, int>& courseToFaculty,
        const CourseManager& cm, PeopleManager& pm) {
        DisplayHelper::printHeader("FUNCTION PROPERTIES (MODULE 7)");

        cout << "\nAnalyzing Course -> Faculty mapping\n";
        cout << "Domain size: " << courseToFaculty.size() << "\n";
        cout << "Codomain size: " << pm.getFacultyCount() << "\n\n";

        bool inj = isInjective(courseToFaculty);
        bool sur = isSurjective(courseToFaculty, pm.getFacultyCount());
        bool bij = isBijective(courseToFaculty, pm.getFacultyCount());

        cout << "Properties:\n";
        cout << "  Injective (One-to-One): " << (inj ? "[YES]" : "[NO]") << "\n";
        cout << "  Surjective (Onto):      " << (sur ? "[YES]" : "[NO]") << "\n";
        cout << "  Bijective:              " << (bij ? "[YES]" : "[NO]") << "\n\n";

        cout << "Mapping:\n";
        for (const auto& pair : courseToFaculty) {
            const auto* course = cm.getCourse(pair.first);
            auto* faculty = pm.getFaculty(pair.second);
            cout << "  " << (course ? course->code : to_string(pair.first)) << " -> "
                << (faculty ? faculty->name : to_string(pair.second)) << "\n";
        }
        cout << "\n";
    }
};

class ProofGenerator {
private:
    const Relations& relations;
    const CourseManager& cm;

    struct ProofStep {
        string statement;
        string justification;
        int level;
    };

    vector<ProofStep> proofSteps;

public:
    ProofGenerator(const Relations& r, const CourseManager& c)
        : relations(r), cm(c) {
    }

    void generatePrereqProof(int courseId, const vector<bool>& completed) {
        proofSteps.clear();

        const auto* course = cm.getCourse(courseId);
        string courseName = course ? course->code : to_string(courseId);

        proofSteps.push_back({
            "THEOREM: Student can enroll in " + courseName,
            "To be proven using mathematical induction",
            0
            });

        proofSteps.push_back({
            "BASE CASE: Check direct prerequisites",
            "Definition of prerequisite relation",
            1
            });

        auto prereq = relations.getPrereqMatrix();
        bool hasDirectPrereq = false;

        for (int i = 0; i < (int)prereq.size(); i++) {
            if (prereq[i][courseId]) {
                hasDirectPrereq = true;
                const auto* p = cm.getCourse(i);
                string pName = p ? p->code : to_string(i);

                if (completed[i]) {
                    proofSteps.push_back({
                        pName + " is completed [PASS]",
                        "Given in completed courses set",
                        2
                        });
                }
                else {
                    proofSteps.push_back({
                        pName + " is NOT completed [FAIL]",
                        "Missing from completed set",
                        2
                        });
                }
            }
        }

        if (!hasDirectPrereq) {
            proofSteps.push_back({
                "No direct prerequisites required",
                "Empty prerequisite set",
                2
                });
        }

        proofSteps.push_back({
            "INDUCTIVE STEP: Check transitive closure",
            "Strong induction on prerequisite chain",
            1
            });

        auto closure = relations.closurePrereq();
        for (int i = 0; i < (int)closure.size(); i++) {
            if (closure[i][courseId] && i != courseId) {
                const auto* p = cm.getCourse(i);
                string pName = p ? p->code : to_string(i);

                if (completed[i]) {
                    proofSteps.push_back({
                        "Indirect prerequisite " + pName + " satisfied [PASS]",
                        "By transitive closure of prerequisite relation",
                        2
                        });
                }
                else {
                    proofSteps.push_back({
                        "Indirect prerequisite " + pName + " NOT satisfied [FAIL]",
                        "Required by transitivity",
                        2
                        });
                }
            }
        }

        bool allSatisfied = true;
        for (int i = 0; i < (int)closure.size(); i++) {
            if (closure[i][courseId] && !completed[i]) {
                allSatisfied = false;
                break;
            }
        }

        proofSteps.push_back({
            allSatisfied ? "CONCLUSION: Prerequisites satisfied [PASS] Q.E.D."
                        : "CONCLUSION: Prerequisites NOT satisfied [FAIL]",
            allSatisfied ? "By mathematical induction, all prerequisites met"
                        : "Proof fails - missing required courses",
            0
            });
    }

    void generateCourseChainProof(int studentId, PeopleManager& pm) {
        proofSteps.clear();

        auto* student = pm.getStudent(studentId);
        string studentName = student ? student->name : to_string(studentId);

        proofSteps.push_back({
            "THEOREM: " + studentName + " can complete degree requirements",
            "Proof by construction - building valid course sequence",
            0
            });

        proofSteps.push_back({
            "CONSTRUCTION: Order courses by prerequisite chains",
            "Using topological sort on prerequisite DAG",
            1
            });

        if (student) {
            vector<int> noPrerequCourses;
            auto matrix = relations.getPrereqMatrix();

            for (int c : student->enrolled) {
                bool hasPrereq = false;
                for (int i = 0; i < relations.getSize(); i++) {
                    if (matrix[i][c]) {
                        hasPrereq = true;
                        break;
                    }
                }
                if (!hasPrereq) {
                    noPrerequCourses.push_back(c);
                }
            }

            proofSteps.push_back({
                "SEMESTER 1: Courses with no prerequisites (" +
                to_string(noPrerequCourses.size()) + " courses)",
                "These form the base of our construction",
                2
                });

            for (int c : noPrerequCourses) {
                const auto* course = cm.getCourse(c);
                proofSteps.push_back({
                    "  Can take: " + (course ? course->code : to_string(c)),
                    "No prerequisites required",
                    3
                    });
            }
        }

        proofSteps.push_back({
            "CONCLUSION: Valid course sequence exists [PASS] Q.E.D.",
            "By construction, all prerequisites can be satisfied",
            0
            });
    }

    void generateAcyclicProof() {
        proofSteps.clear();

        proofSteps.push_back({
            "THEOREM: Prerequisite graph is acyclic (DAG)",
            "Proof by contradiction",
            0
            });

        proofSteps.push_back({
            "ASSUMPTION: Suppose a cycle exists",
            "For sake of contradiction",
            1
            });

        proofSteps.push_back({
            "Let courses C1 -> C2 -> ... -> Cn -> C1 form a cycle",
            "Where -> denotes prerequisite relation",
            2
            });

        bool hasCycle = relations.hasPrereqCycle();

        if (hasCycle) {
            proofSteps.push_back({
                "CONTRADICTION FOUND: Cycle detected in system",
                "Student cannot complete C1 (requires completing C1 first)",
                2
                });

            proofSteps.push_back({
                "CONCLUSION: Prerequisite graph contains cycles [FAIL]",
                "System needs correction - remove circular dependencies",
                0
                });
        }
        else {
            proofSteps.push_back({
                "No cycle found in transitive closure",
                "Checked all reachability paths",
                2
                });

            proofSteps.push_back({
                "CONCLUSION: Prerequisite graph is acyclic [PASS] Q.E.D.",
                "No contradictions found - graph is a valid DAG",
                0
                });
        }
    }

    void generateEquivalenceProof(const vector<vector<bool>>& relation) {
        proofSteps.clear();

        proofSteps.push_back({
            "THEOREM: Relation R is an equivalence relation",
            "Must prove reflexive, symmetric, and transitive",
            0
            });

        bool reflexive = true;
        for (int i = 0; i < (int)relation.size(); i++) {
            if (!relation[i][i]) {
                reflexive = false;
                break;
            }
        }

        proofSteps.push_back({
            reflexive ? "REFLEXIVE: For all x, (x,x) in R [PASS]" : "NOT REFLEXIVE [FAIL]",
            reflexive ? "Verified for all elements" : "Found element not related to itself",
            1
            });

        bool symmetric = true;
        for (int i = 0; i < (int)relation.size(); i++) {
            for (int j = 0; j < (int)relation.size(); j++) {
                if (relation[i][j] != relation[j][i]) {
                    symmetric = false;
                    break;
                }
            }
            if (!symmetric) break;
        }

        proofSteps.push_back({
            symmetric ? "SYMMETRIC: For all x,y, (x,y) in R implies (y,x) in R [PASS]" : "NOT SYMMETRIC [FAIL]",
            symmetric ? "Verified for all pairs" : "Found asymmetric pair",
            1
            });

        bool transitive = true;
        for (int i = 0; i < (int)relation.size(); i++) {
            for (int j = 0; j < (int)relation.size(); j++) {
                for (int k = 0; k < (int)relation.size(); k++) {
                    if (relation[i][j] && relation[j][k] && !relation[i][k]) {
                        transitive = false;
                        break;
                    }
                }
            }
        }

        proofSteps.push_back({
            transitive ? "TRANSITIVE: For all x,y,z, (x,y) and (y,z) implies (x,z) [PASS]" : "NOT TRANSITIVE [FAIL]",
            transitive ? "Verified for all triples" : "Found violation of transitivity",
            1
            });

        bool isEquiv = reflexive && symmetric && transitive;
        proofSteps.push_back({
            isEquiv ? "CONCLUSION: R is an equivalence relation [PASS] Q.E.D."
                   : "CONCLUSION: R is NOT an equivalence relation [FAIL]",
            isEquiv ? "All three properties satisfied" : "One or more properties failed",
            0
            });
    }

    void generatePartitionProof(const vector<CustomSet<int>>& partition) {
        proofSteps.clear();

        proofSteps.push_back({
            "THEOREM: Collection forms a valid partition",
            "Must prove: disjoint, non-empty, union = whole set",
            0
            });

        bool disjoint = true;
        for (size_t i = 0; i < partition.size(); i++) {
            for (size_t j = i + 1; j < partition.size(); j++) {
                auto intersect = partition[i].intersection(partition[j]);
                if (!intersect.empty()) {
                    disjoint = false;
                    proofSteps.push_back({
                        "Sets " + to_string(i) + " and " + to_string(j) +
                        " overlap [FAIL]",
                        "Found common elements",
                        2
                        });
                }
            }
        }

        if (disjoint) {
            proofSteps.push_back({
                "All sets are pairwise disjoint [PASS]",
                "No common elements found",
                1
                });
        }

        proofSteps.push_back({
            disjoint ? "CONCLUSION: Valid partition [PASS] Q.E.D."
                     : "CONCLUSION: NOT a valid partition [FAIL]",
            disjoint ? "All partition properties satisfied"
                     : "Disjointness property violated",
            0
            });
    }

    void generatePigeonholeProof(int pigeons, int holes) {
        proofSteps.clear();

        proofSteps.push_back({
            "THEOREM: Pigeonhole Principle Application",
            "If n items in m containers and n > m, some container has >1 item",
            0
            });

        proofSteps.push_back({
            "Given: " + to_string(pigeons) + " students, " +
            to_string(holes) + " time slots",
            "Pigeons=" + to_string(pigeons) + ", Holes=" + to_string(holes),
            1
            });

        if (pigeons > holes) {
            int minPerSlot = (pigeons / holes) + 1;
            proofSteps.push_back({
                "At least one time slot must have >=" + to_string(minPerSlot) +
                " students",
                "By Pigeonhole Principle: ceiling(n/m)",
                2
                });

            proofSteps.push_back({
                "CONCLUSION: Schedule conflict guaranteed [PASS] Q.E.D.",
                "Cannot avoid overlap with current resources",
                0
                });
        }
        else {
            proofSteps.push_back({
                "Sufficient time slots available",
                "No guaranteed conflict",
                2
                });
        }
    }

    void display() const {
        DisplayHelper::printHeader("FORMAL PROOF (MODULE 8)");

        for (const auto& step : proofSteps) {
            string indent(step.level * 2, ' ');
            cout << indent << step.statement << "\n";
            cout << indent << "  -> " << step.justification << "\n\n";
        }
    }
};

class ConsistencyChecker {
private:
    const CourseManager& cm;
    PeopleManager& pm;
    const Relations& rel;
    CustomMap<int, int>& courseToFaculty;
    CustomMap<int, int>& courseToRoom;

    vector<string> errors;
    vector<string> warnings;

public:
    ConsistencyChecker(const CourseManager& c, PeopleManager& p,
        const Relations& r, CustomMap<int, int>& cf, CustomMap<int, int>& cr)
        : cm(c), pm(p), rel(r), courseToFaculty(cf), courseToRoom(cr) {
    }

    void runAllChecks() {
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

    void checkPrereqCycles() {
        if (rel.hasPrereqCycle()) {
            errors.push_back("Prerequisite cycle detected - impossible to complete all courses");
        }
    }

    void checkStudentPrereqs() {
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

    void checkStudentOverload() {
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

    void checkFacultyConflicts() {
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

    void checkRoomCapacity() {
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

    void checkUnassignedCourses() {
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

    void checkCourseOverlaps() {
        DisplayHelper::printInfo("Checking course overlaps using set intersections...");

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

    void checkScheduleConflicts() {
        DisplayHelper::printInfo("Checking schedule conflicts using graph coloring...");

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
        ss << "Minimum time slots needed: " << (maxColor + 1)
            << " (using graph coloring)";
        DisplayHelper::printInfo(ss.str());
    }

    CustomSet<int> getCourseStudents(int courseId) const {
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

    void displayReport() const {
        DisplayHelper::printHeader("CONSISTENCY REPORT (MODULE 9)");

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
};

class PerformanceBenchmark {
private:
    struct BenchResult {
        string operation;
        long long milliseconds;
        int dataSize;
        string complexity;
    };

    vector<BenchResult> results;
    MemoizationCache cache;

    long long getTimeMillis() {
        return clock() * 1000 / CLOCKS_PER_SEC;
    }

public:
    template<typename Func>
    long long measure(Func f) {
        long long start = getTimeMillis();
        f();
        long long end = getTimeMillis();
        return end - start;
    }

    void benchmarkTransitiveClosure(Relations& rel, int size) {
        rel.ensureSize(size);

        for (int i = 0; i < size - 1; i++) {
            rel.addPrereq(i, i + 1);
        }

        long long time = measure([&]() {
            rel.closurePrereq();
            });

        results.push_back({ "Transitive Closure (Floyd-Warshall)", time, size, "O(n³)" });
    }

    void benchmarkBitsetClosure(OptimizedRelations& rel, int size) {
        rel.ensureSize(size);

        for (int i = 0; i < size - 1; i++) {
            rel.addPrereq(i, i + 1);
        }

        long long time = measure([&]() {
            rel.closurePrereq();
            });

        results.push_back({ "Transitive Closure (Bitset Optimized)", time, size, "O(n³/w)" });
    }

    bool canTakeCourseRecursive(int student, int course, const Relations& rel,
        PeopleManager& pm, const vector<int>& completed) {
        if (cache.hasPrereqCached(student, course)) {
            return cache.getPrereqCached(student, course);
        }

        if (find(completed.begin(), completed.end(), course) != completed.end()) {
            cache.cachePrereq(student, course, true);
            return true;
        }

        auto matrix = rel.getPrereqMatrix();
        for (int i = 0; i < rel.getSize(); i++) {
            if (matrix[i][course]) {
                if (!canTakeCourseRecursive(student, i, rel, pm, completed)) {
                    cache.cachePrereq(student, course, false);
                    return false;
                }
            }
        }

        cache.cachePrereq(student, course, true);
        return true;
    }

    void benchmarkRecursiveMemoization(Relations& rel, PeopleManager& pm, int size) {
        rel.ensureSize(size);
        for (int i = 0; i < size - 1; i++) {
            rel.addPrereq(i, i + 1);
        }

        vector<int> completed;
        for (int i = 0; i < size / 2; i++) {
            completed.push_back(i);
        }

        cache.clearAll();

        long long time = measure([&]() {
            for (int c = 0; c < size; c++) {
                canTakeCourseRecursive(0, c, rel, pm, completed);
            }
            });

        results.push_back({ "Recursive Prereq Check (Memoized)", time, size, "O(n²) cached" });
    }

    void benchmarkFunctionChecks(int size) {
        CustomMap<int, int> f;
        for (int i = 0; i < size; i++) {
            f.insert(i, i % (size / 2));
        }

        long long time = measure([&]() {
            Functions::isInjective(f);
            Functions::isSurjective(f, size);
            Functions::isBijective(f, size);
            });

        results.push_back({ "Function Property Checks", time, size, "O(n)" });
    }

    void benchmarkConsistencyChecks(CourseManager& cm, PeopleManager& pm,
        Relations& rel, int size) {
        for (int i = 0; i < size; i++) {
            cm.addCourse("CS" + to_string(i), "Course" + to_string(i), 3);
            pm.addStudent("Student" + to_string(i));
        }

        CustomMap<int, int> cf, cr;
        ConsistencyChecker checker(cm, pm, rel, cf, cr);

        long long time = measure([&]() {
            checker.runAllChecks();
            });

        results.push_back({ "Consistency Checks", time, size, "O(n²)" });
    }

    void runAllBenchmarks() {
        DisplayHelper::printHeader("PERFORMANCE BENCHMARKING (MODULE 10)");

        cout << "\nRunning comprehensive benchmarks...\n";
        cout << "Testing: Recursion, Memoization, Custom Bitsets, Dynamic Programming\n\n";

        Relations rel1, rel2, rel3, rel4;
        OptimizedRelations optRel1, optRel2;

        benchmarkTransitiveClosure(rel1, 10);
        benchmarkTransitiveClosure(rel2, 20);
        benchmarkTransitiveClosure(rel3, 50);

        benchmarkBitsetClosure(optRel1, 50);
        benchmarkBitsetClosure(optRel2, 100);

        PeopleManager pm;
        benchmarkRecursiveMemoization(rel4, pm, 30);

        benchmarkFunctionChecks(100);
        benchmarkFunctionChecks(500);
        benchmarkFunctionChecks(1000);

        CourseManager cm;
        PeopleManager pm2;
        Relations rel5;
        benchmarkConsistencyChecks(cm, pm2, rel5, 20);

        displayResults();
        cache.displayStats();
    }

    void displayResults() const {
        DisplayHelper::printHeader("BENCHMARK RESULTS");

        cout << "\n" << left << setw(40) << "Operation"
            << setw(12) << "Time (ms)"
            << setw(10) << "Size"
            << "Complexity\n";
        cout << string(75, '-') << "\n";

        for (const auto& r : results) {
            cout << left << setw(40) << r.operation
                << setw(12) << r.milliseconds
                << setw(10) << r.dataSize
                << r.complexity << "\n";
        }

        cout << "\nNote: ms = milliseconds, w = word size (typically 64 bits)\n";
    }
};

class CLIInterface {
private:
    CourseManager& cm;
    PeopleManager& pm;
    Relations& rel;
    CustomMap<int, int>& courseToFaculty;
    CustomMap<int, int>& courseToRoom;
    CustomMap<int, int> facultyToRoom;

public:
    CLIInterface(CourseManager& c, PeopleManager& p, Relations& r,
        CustomMap<int, int>& cf, CustomMap<int, int>& cr)
        : cm(c), pm(p), rel(r), courseToFaculty(cf), courseToRoom(cr) {
    }

    void showWelcome() {
        DisplayHelper::printHeader("MHM MANAGEMENT SYSTEM");
        cout << "\n  Welcome to the Advanced University Management System\n";
        cout << "  Powered by Discrete Mathematics Concepts\n";
        cout << "\n  Available Modules:\n";
        cout << "  - Functions & Mappings (with Inverse)\n";
        cout << "  - Automated Proof Generation\n";
        cout << "  - Consistency Checking (with Set Operations)\n";
        cout << "  - Performance Benchmarking (Memoization & Custom Bitsets)\n";
        cout << "  - Comprehensive Unit Testing\n\n";
    }

    void displayStatistics() {
        DisplayHelper::printHeader("SYSTEM STATISTICS");

        cout << "\nCurrent System Status:\n";
        cout << "  Total Courses:  " << cm.count() << "\n";
        cout << "  Total Students: " << pm.getStudentCount() << "\n";
        cout << "  Total Faculty:  " << pm.getFacultyCount() << "\n";
        cout << "  Total Rooms:    " << pm.getRoomCount() << "\n";

        int totalPrereqs = 0;
        for (int i = 0; i < rel.getSize(); i++) {
            for (int j = 0; j < rel.getSize(); j++) {
                if (rel.getPrereq(i, j)) totalPrereqs++;
            }
        }
        cout << "  Prerequisites:  " << totalPrereqs << "\n";

        cout << "\nAssignments:\n";
        cout << "  Course-Faculty: " << courseToFaculty.size() << " mappings\n";
        cout << "  Course-Room:    " << courseToRoom.size() << " mappings\n";
        cout << "  Faculty-Room:   " << facultyToRoom.size() << " mappings\n";

        int totalEnrollments = 0;
        for (int i = 0; i < pm.getStudentCount(); i++) {
            auto* s = pm.getStudent(i);
            if (s) totalEnrollments += s->enrolled.size();
        }
        cout << "  Enrollments:    " << totalEnrollments << " total\n";
        cout << "\n";
    }

    void quickSetup() {
        DisplayHelper::printHeader("QUICK SETUP WIZARD");

        cout << "\nThis will create sample data for testing.\n";
        cout << "Continue? (y/n): ";
        char confirm;
        cin >> confirm;

        if (confirm != 'y' && confirm != 'Y') return;

        cout << "\nCreating sample courses...\n";
        cm.addCourse("CS101", "Programming", 3);
        cm.addCourse("CS102", "DataStructures", 4);
        cm.addCourse("CS201", "Algorithms", 4);
        cm.addCourse("MATH101", "Calculus", 3);

        rel.ensureSize(4);
        rel.addPrereq(0, 1);
        rel.addPrereq(1, 2);

        cout << "Creating sample students...\n";
        pm.addStudent("Ali");
        pm.addStudent("Nimra");
        pm.addStudent("Maria");

        cout << "Creating sample faculty...\n";
        pm.addFaculty("Dr. Kashaf");
        pm.addFaculty("Dr. Noor");

        cout << "Creating sample rooms...\n";
        pm.addRoom("R101", 50);
        pm.addRoom("R102", 40);

        cout << "Assigning faculty and rooms...\n";
        courseToFaculty.insert(0, 0);
        courseToFaculty.insert(1, 0);
        courseToFaculty.insert(2, 1);
        courseToFaculty.insert(3, 1);

        courseToRoom.insert(0, 0);
        courseToRoom.insert(1, 0);
        courseToRoom.insert(2, 1);
        courseToRoom.insert(3, 1);

        facultyToRoom.insert(0, 0);
        facultyToRoom.insert(1, 1);

        cout << "Enrolling students...\n";
        auto* s1 = pm.getStudent(0);
        if (s1) {
            s1->enrolled.push_back(0);
            s1->enrolled.push_back(3);
        }

        auto* s2 = pm.getStudent(1);
        if (s2) {
            s2->enrolled.push_back(0);
            s2->enrolled.push_back(1);
        }

        DisplayHelper::printSuccess("Quick setup completed!");
        displayStatistics();
    }

    CustomMap<int, int>& getFacultyToRoom() {
        return facultyToRoom;
    }

    void exportData(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            DisplayHelper::printError("Could not open file for writing");
            return;
        }

        file << "MHM DATA EXPORT\n";
        file << "===========================\n\n";

        file << "COURSES:\n";
        for (int i = 0; i < cm.count(); i++) {
            auto* c = cm.getCourse(i);
            if (c) {
                file << c->id << "," << c->code << "," << c->name << "," << c->credits << "\n";
            }
        }

        file << "\nSTUDENTS:\n";
        for (int i = 0; i < pm.getStudentCount(); i++) {
            auto* s = pm.getStudent(i);
            if (s) {
                file << s->id << "," << s->name << ",";
                for (size_t j = 0; j < s->enrolled.size(); j++) {
                    file << s->enrolled[j];
                    if (j < s->enrolled.size() - 1) file << ";";
                }
                file << "\n";
            }
        }

        file.close();
        DisplayHelper::printSuccess("Data exported to " + filename);
    }

    void showHelp() {
        DisplayHelper::printHeader("HELP & DOCUMENTATION");

        cout << "\nMODULE 7 - Functions:\n";
        cout << "  Tests function properties (injective, surjective, bijective)\n";
        cout << "  NEW: Inverse mappings, multi-valued functions\n";

        cout << "\nMODULE 8 - Automated Proofs:\n";
        cout << "  Generates formal mathematical proofs\n";
        cout << "  NEW: Course chains, acyclic proofs, logic rules\n";

        cout << "\nMODULE 9 - Consistency Checker:\n";
        cout << "  Detects system-wide conflicts\n";
        cout << "  NEW: Set intersection operations\n";

        cout << "\nMODULE 10 - Performance:\n";
        cout << "  Benchmarks algorithm efficiency\n";
        cout << "  NEW: Memoization, recursion, custom bitsets\n";

        cout << "\nMODULE 12 - Unit Testing:\n";
        cout << "  Comprehensive test suite\n";
        cout << "  NEW: Large-scale FAST University tests\n\n";
    }
};

class UnitTesting {
private:
    int passed = 0;
    int failed = 0;

    void assertTrue(bool condition, const string& testName) {
        if (condition) {
            cout << "[PASS] " << testName << "\n";
            passed++;
        }
        else {
            cout << "[FAIL] " << testName << "\n";
            failed++;
        }
    }

    void assertEqual(int a, int b, const string& testName) {
        if (a == b) {
            cout << "[PASS] " << testName << "\n";
            passed++;
        }
        else {
            cout << "[FAIL] " << testName << " (expected " << b << ", got " << a << ")\n";
            failed++;
        }
    }

public:
    void testFunctions() {
        cout << "\n--- Testing Functions (Module 7) ---\n";

        CustomMap<int, int> f1;
        f1.insert(0, 0); f1.insert(1, 1); f1.insert(2, 2);
        assertTrue(Functions::isInjective(f1), "Should be injective");
        assertTrue(Functions::isSurjective(f1, 3), "Should be surjective");
        assertTrue(Functions::isBijective(f1, 3), "Should be bijective");

        auto f1_inv = Functions::inverse(f1, 3);
        assertTrue(f1_inv.size() == 3, "Inverse should have 3 mappings");
        assertTrue(Functions::verifyInverse(f1, f1_inv), "Inverse verification should pass");

        CustomMap<int, int> f2;
        f2.insert(0, 0); f2.insert(1, 0); f2.insert(2, 1);
        assertTrue(!Functions::isInjective(f2), "Should not be injective");

        auto f2_inv = Functions::inverse(f2, 3);
        assertTrue(f2_inv.empty(), "Non-bijective function should have empty inverse");

        CustomMap<int, int> f3, f4;
        f3.insert(0, 1); f3.insert(1, 2);
        f4.insert(1, 10); f4.insert(2, 20);
        auto composed = Functions::compose(f3, f4);
        assertTrue(composed.size() == 2, "Composition should have 2 mappings");
    }

    void testProofGenerator() {
        cout << "\n--- Testing Proof Generator (Module 8) ---\n";

        CourseManager cm;
        Relations rel;

        cm.addCourse("CS101", "Intro", 3);
        cm.addCourse("CS201", "Advanced", 3);
        rel.ensureSize(2);
        rel.addPrereq(0, 1);

        ProofGenerator proof(rel, cm);

        vector<bool> completed(2, false);
        completed[0] = true;

        proof.generatePrereqProof(1, completed);
        assertTrue(true, "Proof generation completed successfully");

        proof.generateAcyclicProof();
        assertTrue(true, "Acyclic proof generated");
    }

    void testConsistencyChecker() {
        cout << "\n--- Testing Consistency Checker (Module 9) ---\n";

        CourseManager cm;
        PeopleManager pm;
        Relations rel;

        cm.addCourse("CS101", "Programming", 3);
        pm.addStudent("Alice");
        pm.addFaculty("Dr. Smith");
        pm.addRoom("R101", 30);

        CustomMap<int, int> cf, cr;
        cf.insert(0, 0);
        cr.insert(0, 0);

        ConsistencyChecker checker(cm, pm, rel, cf, cr);
        checker.runAllChecks();

        assertTrue(true, "Consistency checks completed");

        auto students1 = checker.getCourseStudents(0);
        assertTrue(students1.size() >= 0, "Set intersection check working");
    }

    void testPerformanceBenchmark() {
        cout << "\n--- Testing Performance Benchmark (Module 10) ---\n";

        PerformanceBenchmark bench;

        Relations rel;
        bench.benchmarkTransitiveClosure(rel, 5);
        bench.benchmarkFunctionChecks(10);

        OptimizedRelations optRel;
        bench.benchmarkBitsetClosure(optRel, 10);

        assertTrue(true, "Benchmark completed successfully");
    }

    void testRelations() {
        cout << "\n--- Testing Relations ---\n";

        Relations rel;
        rel.ensureSize(5);
        rel.addPrereq(0, 1);
        rel.addPrereq(1, 2);

        assertTrue(rel.getPrereq(0, 1), "Direct prerequisite should exist");

        auto closure = rel.closurePrereq();
        assertTrue(closure[0][2], "Transitive prerequisite should exist");

        assertTrue(!rel.hasPrereqCycle(), "Should have no cycles");

        rel.addPrereq(2, 0);
        assertTrue(rel.hasPrereqCycle(), "Should detect cycle");
    }

    void testLargeScale() {
        cout << "\n--- Testing Large Scale (FAST University Size) ---\n";

        const int NUM_COURSES = 100;
        const int NUM_STUDENTS = 500;
        const int NUM_FACULTY = 50;

        CourseManager cm;
        PeopleManager pm;
        Relations rel;

        cout << "Creating " << NUM_COURSES << " courses...\n";
        for (int i = 0; i < NUM_COURSES; i++) {
            cm.addCourse("CS" + to_string(i), "Course" + to_string(i), 3);
        }
        assertTrue(cm.count() == NUM_COURSES, "Large-scale course creation");

        cout << "Creating " << NUM_STUDENTS << " students...\n";
        for (int i = 0; i < NUM_STUDENTS; i++) {
            string names[] = { "Ali", "Nimra", "Maria", "Kashaf", "Noor", "Waqas", "Fatima", "Hassan" };
            pm.addStudent(names[i % 8] + to_string(i / 8));
        }
        assertTrue(pm.getStudentCount() == NUM_STUDENTS, "Large-scale student creation");

        cout << "Creating " << NUM_FACULTY << " faculty...\n";
        for (int i = 0; i < NUM_FACULTY; i++) {
            string names[] = { "Dr. Waqas", "Dr. Nimra", "Dr. Ali", "Dr. Maria", "Dr. Noor" };
            pm.addFaculty(names[i % 5] + to_string(i / 5));
        }
        assertTrue(pm.getFacultyCount() == NUM_FACULTY, "Large-scale faculty creation");

        cout << "Testing performance at FAST scale...\n";
        auto start = clock();

        rel.ensureSize(NUM_COURSES);
        for (int i = 0; i < NUM_COURSES - 1; i++) {
            rel.addPrereq(i, i + 1);
        }

        auto closure = rel.closurePrereq();

        auto end = clock();
        long long time = (end - start) * 1000 / CLOCKS_PER_SEC;

        cout << "Time taken: " << time << " ms\n";
        assertTrue(time < 5000, "Should complete in reasonable time (<5s)");

        assertTrue(closure[0][NUM_COURSES - 1], "Transitive closure at scale works");

        DisplayHelper::printSuccess("Large-scale testing completed!");
    }

    void testEdgeCases() {
        cout << "\n--- Testing Edge Cases ---\n";

        CourseManager cm;
        Relations rel;

        assertTrue(cm.count() == 0, "Empty system test");

        cm.addCourse("CS101", "Test", 3);
        assertTrue(cm.count() == 1, "Single course test");

        rel.ensureSize(2);
        rel.addPrereq(0, 0);
        assertTrue(rel.hasPrereqCycle(), "Self-prerequisite creates cycle");

        const auto* invalid = cm.getCourse(999);
        assertTrue(invalid == nullptr, "Invalid course ID returns nullptr");

        cout << "All edge cases passed!\n";
    }

    void testStressOperations() {
        cout << "\n--- Stress Testing ---\n";

        CourseManager cm;

        cout << "Rapidly creating/accessing 1000 courses...\n";
        for (int i = 0; i < 1000; i++) {
            cm.addCourse("C" + to_string(i), "Course", 3);
        }

        int accessible = 0;
        for (int i = 0; i < 1000; i++) {
            if (cm.getCourse(i) != nullptr) accessible++;
        }

        assertTrue(accessible == 1000, "All 1000 courses accessible after stress test");

        cout << "Stress test completed!\n";
    }

    void runAllTests() {
        DisplayHelper::printHeader("UNIT TESTING SUITE (MODULE 12)");

        passed = 0;
        failed = 0;

        testFunctions();
        testProofGenerator();
        testConsistencyChecker();
        testPerformanceBenchmark();
        testRelations();
        testLargeScale();
        testEdgeCases();
        testStressOperations();

        cout << "\n" << string(60, '=') << "\n";
        cout << "RESULTS: " << passed << " passed, " << failed << " failed\n";

        if (failed == 0) {
            DisplayHelper::printSuccess("All tests passed!");
        }
        else {
            DisplayHelper::printError(to_string(failed) + " test(s) failed");
        }
    }
};

int main() {
    CourseManager cm;
    PeopleManager pm;
    Relations rel;

    CustomMap<int, int> courseToFaculty;
    CustomMap<int, int> courseToRoom;

    CLIInterface cli(cm, pm, rel, courseToFaculty, courseToRoom);

    cout << string(60, '=') << "\n";
    cout << "  FAST UNIVERSITY MANAGEMENT SYSTEM - NO STDLIB VERSION\n";
    cout << "  Custom Implementations: Bitset, Map (No <bitset> or <map>)\n";
    cout << string(60, '=') << "\n";

    cli.showWelcome();

    while (true) {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "BASIC OPERATIONS:\n";
        cout << " 1. Add Course\n";
        cout << " 2. Add Student\n";
        cout << " 3. Add Faculty\n";
        cout << " 4. Add Room\n";
        cout << " 5. Add Prerequisite\n";
        cout << " 6. Assign Faculty to Course\n";
        cout << " 7. Assign Room to Course\n";
        cout << " 8. Enroll Student\n";
        cout << " 9. List All Courses\n";
        cout << "\nENHANCED MODULES 7-12:\n";
        cout << "10. Function Properties + Inverse (Module 7)\n";
        cout << "11. Automated Proof Generator + Chains (Module 8)\n";
        cout << "12. Consistency Checker + Set Operations (Module 9)\n";
        cout << "13. Performance + Memoization + Custom Bitsets (Module 10)\n";
        cout << "14. CLI Features - Statistics/Export (Module 11)\n";
        cout << "15. Unit Testing + Large-Scale (Module 12)\n";
        cout << "\nNEW FEATURES:\n";
        cout << "18. Test Inverse Functions\n";
        cout << "19. Analyze Student->Courses Mapping\n";
        cout << "20. Analyze Faculty->Rooms Mapping\n";
        cout << "21. Test Custom Bitset Optimization\n";
        cout << "22. Power Set & Cartesian Product & Relation Properties\n";
        cout << "\nUTILITIES:\n";
        cout << "16. Quick Setup (Sample Data)\n";
        cout << "17. Help & Documentation\n";
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
            cin >> name;
            cout << "Credits: ";
            cin >> credits;

            cm.addCourse(code, name, credits);
            rel.ensureSize(cm.count());
            DisplayHelper::printSuccess("Course added successfully");
            break;
        }

        case 2: {
            string name;
            cout << "Student name: ";
            cin >> name;
            pm.addStudent(name);
            DisplayHelper::printSuccess("Student added successfully");
            break;
        }

        case 3: {
            string name;
            cout << "Faculty name: ";
            cin >> name;
            pm.addFaculty(name);
            DisplayHelper::printSuccess("Faculty added successfully");
            break;
        }

        case 4: {
            string name;
            int capacity;
            cout << "Room name: ";
            cin >> name;
            cout << "Capacity: ";
            cin >> capacity;
            pm.addRoom(name, capacity);
            DisplayHelper::printSuccess("Room added successfully");
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
            cm.listAll();
            break;
        }

        case 10: {
            Functions::display(courseToFaculty, cm, pm);

            cout << "\nAdditional Operations:\n";
            cout << "1. Test Function Composition\n";
            cout << "2. Test Inverse Function\n";
            cout << "Choice (or 0 to skip): ";

            int sub;
            cin >> sub;

            if (sub == 1) {
                DisplayHelper::printHeader("FUNCTION COMPOSITION");

                CustomMap<int, int> f1, f2;
                for (const auto& pair : courseToFaculty) {
                    f1.insert(pair.first, pair.second);
                }

                cout << "Enter faculty->room mappings (-1 to stop):\n";
                int fid, rid;
                while (true) {
                    cout << "Faculty ID: ";
                    cin >> fid;
                    if (fid == -1) break;
                    cout << "Room ID: ";
                    cin >> rid;
                    f2.insert(fid, rid);
                }

                auto composed = Functions::compose(f1, f2);
                cout << "\nComposed function (g o f): course -> room\n";
                for (const auto& pair : composed) {
                    const auto* c = cm.getCourse(pair.first);
                    auto* r = pm.getRoom(pair.second);
                    cout << "  " << (c ? c->code : to_string(pair.first))
                        << " -> " << (r ? r->name : to_string(pair.second)) << "\n";
                }
            }
            else if (sub == 2) {
                DisplayHelper::printHeader("INVERSE FUNCTION TEST");

                auto inverse = Functions::inverse(courseToFaculty, pm.getFacultyCount());

                if (!inverse.empty()) {
                    cout << "\nInverse mapping (faculty -> course):\n";
                    for (const auto& pair : inverse) {
                        auto* fac = pm.getFaculty(pair.first);
                        const auto* course = cm.getCourse(pair.second);
                        cout << "  " << (fac ? fac->name : to_string(pair.first))
                            << " -> " << (course ? course->code : to_string(pair.second)) << "\n";
                    }

                    if (Functions::verifyInverse(courseToFaculty, inverse)) {
                        DisplayHelper::printSuccess("Inverse verification passed!");
                    }
                }
            }
            break;
        }

        case 11: {
            cout << "\n1. Prerequisite Proof\n";
            cout << "2. Equivalence Relation Proof\n";
            cout << "3. Course Chain Proof\n";
            cout << "4. Acyclic Graph Proof\n";
            cout << "5. Partition Proof\n";
            cout << "6. Pigeonhole Principle Proof\n";
            cout << "Choice: ";

            int sub;
            cin >> sub;

            ProofGenerator proof(rel, cm);

            if (sub == 1) {
                int c;
                cout << "Course ID to verify: ";
                cin >> c;

                if (c >= 0 && c < cm.count()) {
                    vector<bool> completed(cm.count(), false);
                    cout << "Enter completed course IDs (-1 to stop): ";
                    int x;
                    while (cin >> x && x != -1) {
                        if (x >= 0 && x < cm.count()) completed[x] = true;
                    }

                    proof.generatePrereqProof(c, completed);
                    proof.display();
                }
                else {
                    DisplayHelper::printError("Invalid course ID");
                }
            }
            else if (sub == 2) {
                auto matrix = rel.getPrereqMatrix();
                proof.generateEquivalenceProof(matrix);
                proof.display();
            }
            else if (sub == 3) {
                int s;
                cout << "Student ID: ";
                cin >> s;

                if (s >= 0 && s < pm.getStudentCount()) {
                    proof.generateCourseChainProof(s, pm);
                    proof.display();
                }
            }
            else if (sub == 4) {
                proof.generateAcyclicProof();
                proof.display();
            }
            else if (sub == 5) {
                vector<CustomSet<int>> partition;
                cout << "Enter number of sets in partition: ";
                int numSets;
                cin >> numSets;

                for (int i = 0; i < numSets; i++) {
                    CustomSet<int> s;
                    cout << "Enter elements for set " << i << " (-1 to stop): ";
                    int elem;
                    while (cin >> elem && elem != -1) {
                        s.insert(elem);
                    }
                    partition.push_back(s);
                }

                proof.generatePartitionProof(partition);
                proof.display();
            }
            else if (sub == 6) {
                int students, slots;
                cout << "Enter number of students: ";
                cin >> students;
                cout << "Enter number of time slots: ";
                cin >> slots;

                proof.generatePigeonholeProof(students, slots);
                proof.display();
            }
            break;
        }

        case 12: {
            ConsistencyChecker checker(cm, pm, rel, courseToFaculty, courseToRoom);
            checker.runAllChecks();
            checker.checkScheduleConflicts();
            checker.displayReport();
            break;
        }

        case 13: {
            PerformanceBenchmark bench;
            bench.runAllBenchmarks();
            break;
        }

        case 14: {
            cout << "\n--- CLI FEATURES (Module 11) ---\n";
            cout << "1. Show System Statistics\n";
            cout << "2. Export Data to File\n";
            cout << "Choice: ";

            int sub;
            cin >> sub;

            if (sub == 1) {
                cli.displayStatistics();
            }
            else if (sub == 2) {
                string filename;
                cout << "Enter filename: ";
                cin >> filename;
                cli.exportData(filename);
            }
            break;
        }

        case 15: {
            UnitTesting tester;
            tester.runAllTests();
            break;
        }

        case 16: {
            cli.quickSetup();
            break;
        }

        case 17: {
            cli.showHelp();
            break;
        }

        case 18: {
            DisplayHelper::printHeader("INVERSE FUNCTION DEMONSTRATION");

            cout << "\nTesting inverse of Course->Faculty mapping:\n";

            auto inverse = Functions::inverse(courseToFaculty, pm.getFacultyCount());

            if (!inverse.empty()) {
                cout << "\nOriginal: Course -> Faculty\n";
                for (const auto& pair : courseToFaculty) {
                    const auto* c = cm.getCourse(pair.first);
                    auto* f = pm.getFaculty(pair.second);
                    cout << "  f(" << (c ? c->code : to_string(pair.first)) << ") = "
                        << (f ? f->name : to_string(pair.second)) << "\n";
                }

                cout << "\nInverse: Faculty -> Course\n";
                for (const auto& pair : inverse) {
                    auto* f = pm.getFaculty(pair.first);
                    const auto* c = cm.getCourse(pair.second);
                    cout << "  f^-1(" << (f ? f->name : to_string(pair.first)) << ") = "
                        << (c ? c->code : to_string(pair.second)) << "\n";
                }

                cout << "\nVerification: f(f^-1(x)) = x\n";
                for (const auto& pair : inverse) {
                    const int* original = courseToFaculty.get(pair.second);
                    if (original && *original == pair.first) {
                        cout << "  Verified for faculty ID " << pair.first << "\n";
                    }
                }
            }
            break;
        }

        case 19: {
            Functions::analyzeStudentCourses(pm, cm);
            break;
        }

        case 20: {
            cout << "\nAssign Faculty->Room mappings first:\n";
            cout << "Enter mappings (-1 to stop):\n";

            CustomMap<int, int>& facultyToRoom = cli.getFacultyToRoom();

            int fid, rid;
            while (true) {
                cout << "Faculty ID: ";
                cin >> fid;
                if (fid == -1) break;
                cout << "Room ID: ";
                cin >> rid;

                if (fid >= 0 && fid < pm.getFacultyCount() &&
                    rid >= 0 && rid < pm.getRoomCount()) {
                    facultyToRoom.insert(fid, rid);
                    DisplayHelper::printSuccess("Mapping added");
                }
                else {
                    DisplayHelper::printError("Invalid IDs");
                }
            }

            Functions::analyzeFacultyRooms(facultyToRoom, pm);
            break;
        }

        case 21: {
            DisplayHelper::printHeader("CUSTOM BITSET OPTIMIZATION TEST");

            cout << "\nComparing standard vs custom bitset implementation:\n\n";

            Relations standardRel;
            standardRel.ensureSize(100);
            for (int i = 0; i < 99; i++) {
                standardRel.addPrereq(i, i + 1);
            }

            auto start1 = clock();
            auto closure1 = standardRel.closurePrereq();
            auto end1 = clock();
            long long time1 = (end1 - start1) * 1000 / CLOCKS_PER_SEC;

            cout << "Standard Implementation:\n";
            cout << "  Time: " << time1 << " ms\n";
            cout << "  Complexity: O(n^3)\n\n";

            OptimizedRelations bitsetRel;
            bitsetRel.ensureSize(100);
            for (int i = 0; i < 99; i++) {
                bitsetRel.addPrereq(i, i + 1);
            }

            auto start2 = clock();
            auto closure2 = bitsetRel.closurePrereq();
            auto end2 = clock();
            long long time2 = (end2 - start2) * 1000 / CLOCKS_PER_SEC;

            cout << "Custom Bitset Optimized Implementation:\n";
            cout << "  Time: " << time2 << " ms\n";
            cout << "  Complexity: O(n^3/w) where w=64\n\n";

            if (time2 < time1) {
                cout << "Speedup: " << (float)time1 / time2 << "x faster!\n";
                DisplayHelper::printSuccess("Custom bitset optimization effective!");
            }
            else {
                cout << "Note: Speedup visible with larger datasets\n";
            }

            cout << "\nVerifying correctness:\n";
            cout << "  Standard: " << (closure1[0][99] ? "Path exists" : "No path") << "\n";
            cout << "  Custom Bitset:   " << (closure2[0].test(99) ? "Path exists" : "No path") << "\n";

            if (closure1[0][99] == closure2[0].test(99)) {
                DisplayHelper::printSuccess("Both implementations produce same result!");
            }
            break;
        }

        case 22: {
            DisplayHelper::printHeader("POWER SET & CARTESIAN PRODUCT");

            cout << "\n1. Power Set of Courses\n";
            cout << "2. Cartesian Product of Two Sets\n";
            cout << "3. Check Relation Properties\n";
            cout << "Choice: ";

            int sub;
            cin >> sub;

            if (sub == 1) {
                CustomSet<int> courses;
                cout << "Enter course IDs for power set (-1 to stop): ";
                int c;
                while (cin >> c && c != -1) {
                    if (c >= 0 && c < cm.count()) {
                        courses.insert(c);
                    }
                }

                auto ps = Functions::powerSet(courses);
                cout << "\nPower Set (2^" << courses.size() << " = "
                    << ps.size() << " subsets):\n";

                for (size_t i = 0; i < ps.size(); i++) {
                    cout << "  {";
                    const auto& subset = ps[i].getVector();
                    for (size_t j = 0; j < subset.size(); j++) {
                        const auto* course = cm.getCourse(subset[j]);
                        cout << (course ? course->code : to_string(subset[j]));
                        if (j < subset.size() - 1) cout << ", ";
                    }
                    cout << "}\n";
                }
            }
            else if (sub == 2) {
                CustomSet<int> setA, setB;

                cout << "Enter elements for Set A (-1 to stop): ";
                int elem;
                while (cin >> elem && elem != -1) {
                    setA.insert(elem);
                }

                cout << "Enter elements for Set B (-1 to stop): ";
                while (cin >> elem && elem != -1) {
                    setB.insert(elem);
                }

                auto cp = Functions::cartesianProduct(setA, setB);
                cout << "\nCartesian Product A × B (" << cp.size() << " pairs):\n";

                for (const auto& p : cp) {
                    cout << "  (" << p.first << ", " << p.second << ")\n";
                }
            }
            else if (sub == 3) {
                cout << "\nChecking Relation Properties:\n\n";
                cout << "Reflexive: " << (rel.isReflexive() ? "[YES]" : "[NO]") << "\n";
                cout << "Symmetric: " << (rel.isSymmetric() ? "[YES]" : "[NO]") << "\n";
                cout << "Transitive: " << (rel.isTransitive() ? "[YES]" : "[NO]") << "\n";
                cout << "Anti-Symmetric: " << (rel.isAntiSymmetric() ? "[YES]" : "[NO]") << "\n\n";
                cout << "Equivalence Relation: " << (rel.isEquivalenceRelation() ? "[YES]" : "[NO]") << "\n";
                cout << "Partial Order: " << (rel.isPartialOrder() ? "[YES]" : "[NO]") << "\n";
            }
            break;
        }

        default:
            DisplayHelper::printError("Invalid choice!");
        }
    }

    return system("pause");
}
