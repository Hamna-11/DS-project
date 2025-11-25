#pragma once
#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <vector>
#include <algorithm>
#include <string>

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
    CustomBitset(int size = 1000);
    void set(int pos);
    void reset(int pos);
    bool test(int pos) const;
    int count() const;
    CustomBitset& operator|=(const CustomBitset& other);
    void clear();
};

class DisplayHelper {
public:
    static void printHeader(const string& title);
    static void printSuccess(const string& msg);
    static void printError(const string& msg);
    static void printWarning(const string& msg);
    static void printInfo(const string& msg);
};

class CourseManager {
public:
    struct Course {
        int id;
        string code;
        string name;
        int credits;

        Course();
        Course(int i, string c, string n, int cr);
    };

private:
    vector<Course> courses;

public:
    int addCourse(const string& code, const string& name, int credits);
    const Course* getCourse(int id) const;
    int count() const;
    void listAll() const;
};

class OptimizedRelations {
private:
    static const int MAX_SIZE = 1000;
    vector<CustomBitset> prereqBits;
    int size;

public:
    OptimizedRelations();
    void ensureSize(int n);
    void addPrereq(int a, int b);
    bool getPrereq(int a, int b) const;
    int getSize() const;
    vector<CustomBitset> closurePrereq() const;
    bool hasPrereqCycle() const;
    int countPrereqs(int course) const;
    vector<vector<bool>> toMatrix() const;
};

class Relations {
private:
    vector<vector<bool>> prereq;
    int size;

public:
    Relations();
    void ensureSize(int n);
    void addPrereq(int a, int b);
    bool getPrereq(int a, int b) const;
    int getSize() const;
    vector<vector<bool>> closurePrereq() const;
    bool hasPrereqCycle() const;
    const vector<vector<bool>>& getPrereqMatrix() const;
    bool isReflexive() const;
    bool isSymmetric() const;
    bool isTransitive() const;
    bool isAntiSymmetric() const;
    bool isEquivalenceRelation() const;
    bool isPartialOrder() const;
};

class MemoizationCache {
private:
    CustomMap<pair<int, int>, bool> prereqCache;
    CustomMap<int, vector<int>> reachableCache;

public:
    void clearAll();
    bool hasPrereqCached(int student, int course) const;
    bool getPrereqCached(int student, int course) const;
    void cachePrereq(int student, int course, bool value);
    bool hasReachableCached(int course) const;
    vector<int> getReachableCached(int course) const;
    void cacheReachable(int course, const vector<int>& reachable);
    void displayStats() const;
};

#endif