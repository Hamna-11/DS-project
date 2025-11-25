#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include "CourseManager.h"
#include "PeopleManager.h"
#include "Relations.h"
#include <iostream>
#include <string>

// Display Helper Class
class DisplayHelper {
public:
    static void printHeader(const std::string& title) {
        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "  " << title << "\n";
        std::cout << std::string(60, '=') << "\n";
    }

    static void printSuccess(const std::string& msg) {
        std::cout << "\n[SUCCESS] " << msg << "\n";
    }

    static void printError(const std::string& msg) {
        std::cout << "\n[ERROR] " << msg << "\n";
    }

    static void printWarning(const std::string& msg) {
        std::cout << "\n[WARNING] " << msg << "\n";
    }

    static void printInfo(const std::string& msg) {
        std::cout << "\n[INFO] " << msg << "\n";
    }
};

// Optimized Relations using bitset
class OptimizedRelations {
private:
    std::vector<std::vector<bool>> prereq;
    int size;
public:
    OptimizedRelations() : size(0) {}

    void ensureSize(int n) {
        if (n > size) {
            prereq.resize(n, std::vector<bool>(n, false));
            size = n;
        }
    }

    void addPrereq(int a, int b) {
        ensureSize(std::max(a, b) + 1);
        prereq[a][b] = true;
    }

    std::vector<std::vector<bool>> closurePrereq() const {
        std::vector<std::vector<bool>> result = prereq;
        for (int k = 0; k < size; k++)
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    if (result[i][k] && result[k][j])
                        result[i][j] = true;
        return result;
    }
};

// Memoization Cache
class MemoizationCache {
private:
    CustomMap<std::pair<int, int>, bool> prereqCache;
    int hits;
    int misses;
public:
    MemoizationCache() : hits(0), misses(0) {}

    bool hasPrereqCached(int student, int course) {
        return prereqCache.contains(std::make_pair(student, course));
    }

    bool getPrereqCached(int student, int course) {
        hits++;
        const bool* result = prereqCache.get(std::make_pair(student, course));
        return result ? *result : false;
    }

    void cachePrereq(int student, int course, bool value) {
        misses++;
        prereqCache.insert(std::make_pair(student, course), value);
    }

    void clearAll() {
        prereqCache.clear();
        hits = 0;
        misses = 0;
    }

    void displayStats() const {
        std::cout << "\nMemoization Statistics:\n";
        std::cout << "  Cache Hits: " << hits << "\n";
        std::cout << "  Cache Misses: " << misses << "\n";
        if (hits + misses > 0) {
            double hitRate = (double)hits / (hits + misses) * 100.0;
            std::cout << "  Hit Rate: " << hitRate << "%\n";
        }
    }
};

#endif