#ifndef DISCRETE_STRUCTURES_H
#define DISCRETE_STRUCTURES_H

#include <vector>
#include <string>
#include <algorithm>
#include <utility>

// ============================================================================
// BASIC DATA STRUCTURES - Sets and Maps
// ============================================================================

template<typename T>
class CustomSet {
private:
    std::vector<T> data;
public:
    void insert(const T& val);
    bool contains(const T& val) const;
    void erase(const T& val);
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
    void insert(const K& key, const V& val);
    bool contains(const K& key) const;
    V* get(const K& key);
    const V* get(const K& key) const;
    V get(const K& key, const V& defaultValue) const;
    V& operator[](const K& key);
    void erase(const K& key);
    int size() const;
    bool empty() const;
    void clear();
    typename std::vector<std::pair<K, V>>::iterator begin();
    typename std::vector<std::pair<K, V>>::iterator end();
    typename std::vector<std::pair<K, V>>::const_iterator begin() const;
    typename std::vector<std::pair<K, V>>::const_iterator end() const;
};

// ============================================================================
// RELATIONS
// ============================================================================

class Relations {
private:
    std::vector<std::vector<bool>> prereq;
    int size;
public:
    Relations();
    void ensureSize(int n);
    void addPrereq(int a, int b);
    bool getPrereq(int a, int b) const;
    int getSize() const;
    std::vector<std::vector<bool>> closurePrereq() const;
    bool hasPrereqCycle() const;
    bool isReflexive() const;
    bool isSymmetric() const;
    bool isTransitive() const;
    bool isAntiSymmetric() const;
    bool isEquivalenceRelation() const;
    bool isPartialOrder() const;
    const std::vector<std::vector<bool>>& getPrereqMatrix() const;
};

// ============================================================================
// FUNCTIONS - Analysis and Properties
// ============================================================================

class Functions {
public:
    static bool isInjective(const CustomMap<int, int>& f);
    static bool isSurjective(const CustomMap<int, int>& f, int codomainSize);
    static bool isBijective(const CustomMap<int, int>& f, int codomainSize);
    static CustomMap<int, int> compose(const CustomMap<int, int>& f, const CustomMap<int, int>& g);
    static CustomMap<int, int> inverse(const CustomMap<int, int>& f, int codomainSize);
    static bool verifyInverse(const CustomMap<int, int>& f, const CustomMap<int, int>& f_inv);
    static std::vector<CustomSet<int>> powerSet(const CustomSet<int>& s);
    static std::vector<std::pair<int, int>> cartesianProduct(const CustomSet<int>& a, const CustomSet<int>& b);
};

// ============================================================================
// SET OPERATIONS
// ============================================================================

class SetOps {
public:
    static CustomSet<int> setIntersection(const CustomSet<int>& a, const CustomSet<int>& b);
    static CustomSet<int> setUnion(const CustomSet<int>& a, const CustomSet<int>& b);
    static CustomSet<int> setDifference(const CustomSet<int>& a, const CustomSet<int>& b);
    static CustomSet<int> symmetricDifference(const CustomSet<int>& a, const CustomSet<int>& b);
    static bool isSubset(const CustomSet<int>& a, const CustomSet<int>& b);
    static bool isSuperset(const CustomSet<int>& a, const CustomSet<int>& b);
    static bool areDisjoint(const CustomSet<int>& a, const CustomSet<int>& b);
};

// ============================================================================
// LOGIC ENGINE
// ============================================================================

class LogicEngine {
public:
    struct Rule {
        std::string premise;
        std::string conclusion;
        std::string name;
    };

private:
    std::vector<Rule> rules;

public:
    void addRule(const std::string& premise, const std::string& conclusion, const std::string& name);
    bool applyModusPonens(const std::string& p, const std::string& pImpliesQ, std::string& result);
    bool applyModusTollens(const std::string& notQ, const std::string& pImpliesQ, std::string& result);
    void listRules() const;
};

// ============================================================================
// INDUCTION PROOFS
// ============================================================================

class Induction {
public:
    static bool provePrereqDepth(const Relations& rel, int maxDepth);
    static void displayProof();
};

#endif // DISCRETE_STRUCTURES_H
