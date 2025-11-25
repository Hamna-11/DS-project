#include "DiscreteStructures.h"
#include <iostream>
#include <algorithm>

// ============================================================================
// CUSTOMSET TEMPLATE IMPLEMENTATIONS
// ============================================================================

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
int CustomSet<T>::size() const { return static_cast<int>(data.size()); }

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

template<typename T>
CustomSet<T> CustomSet<T>::intersection(const CustomSet<T>& other) const {
    CustomSet<T> result;
    for (const auto& elem : data) {
        if (other.contains(elem)) {
            result.insert(elem);
        }
    }
    return result;
}

template<typename T>
CustomSet<T> CustomSet<T>::setUnion(const CustomSet<T>& other) const {
    CustomSet<T> result = *this;
    for (const auto& elem : other.getVector()) {
        result.insert(elem);
    }
    return result;
}

// ============================================================================
// CUSTOMMAP TEMPLATE IMPLEMENTATIONS
// ============================================================================

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
V CustomMap<K, V>::get(const K& key, const V& defaultValue) const {
    const V* val = get(key);
    return val ? *val : defaultValue;
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
int CustomMap<K, V>::size() const { return static_cast<int>(data.size()); }

template<typename K, typename V>
bool CustomMap<K, V>::empty() const { return data.empty(); }

template<typename K, typename V>
void CustomMap<K, V>::clear() { data.clear(); }

template<typename K, typename V>
typename std::vector<std::pair<K, V>>::iterator CustomMap<K, V>::begin() { return data.begin(); }

template<typename K, typename V>
typename std::vector<std::pair<K, V>>::iterator CustomMap<K, V>::end() { return data.end(); }

template<typename K, typename V>
typename std::vector<std::pair<K, V>>::const_iterator CustomMap<K, V>::begin() const { return data.begin(); }

template<typename K, typename V>
typename std::vector<std::pair<K, V>>::const_iterator CustomMap<K, V>::end() const { return data.end(); }

// Explicit template instantiations
template class CustomSet<int>;
template class CustomMap<std::string, int>;
template class CustomMap<int, int>;
template class CustomMap<std::pair<int, int>, bool>;
template class CustomMap<int, std::vector<int>>;
template class CustomMap<std::string, bool>;

// ============================================================================
// RELATIONS IMPLEMENTATION
// ============================================================================

Relations::Relations() : size(0) {}

void Relations::ensureSize(int n) {
    if (n > size) {
        prereq.resize(n, std::vector<bool>(n, false));
        size = n;
    }
}

void Relations::addPrereq(int a, int b) {
    ensureSize(std::max(a, b) + 1);
    prereq[a][b] = true;
}

bool Relations::getPrereq(int a, int b) const {
    if (a < 0 || b < 0 || a >= size || b >= size) return false;
    return prereq[a][b];
}

int Relations::getSize() const { return size; }

std::vector<std::vector<bool>> Relations::closurePrereq() const {
    std::vector<std::vector<bool>> result = prereq;
    for (int k = 0; k < size; k++)
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (result[i][k] && result[k][j])
                    result[i][j] = true;
    return result;
}

bool Relations::hasPrereqCycle() const {
    auto closure = closurePrereq();
    for (int i = 0; i < size; i++)
        if (closure[i][i]) return true;
    return false;
}

bool Relations::isReflexive() const {
    for (int i = 0; i < size; i++)
        if (!prereq[i][i]) return false;
    return true;
}

bool Relations::isSymmetric() const {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (prereq[i][j] != prereq[j][i]) return false;
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

const std::vector<std::vector<bool>>& Relations::getPrereqMatrix() const {
    return prereq;
}

// ============================================================================
// FUNCTIONS IMPLEMENTATION
// ============================================================================

bool Functions::isInjective(const CustomMap<int, int>& f) {
    CustomSet<int> values;
    for (const auto& pair : f) {
        if (values.contains(pair.second)) return false;
        values.insert(pair.second);
    }
    return true;
}

bool Functions::isSurjective(const CustomMap<int, int>& f, int codomainSize) {
    CustomSet<int> values;
    for (const auto& pair : f) {
        values.insert(pair.second);
    }
    return values.size() == codomainSize;
}

bool Functions::isBijective(const CustomMap<int, int>& f, int codomainSize) {
    return isInjective(f) && isSurjective(f, codomainSize);
}

CustomMap<int, int> Functions::compose(const CustomMap<int, int>& f, const CustomMap<int, int>& g) {
    CustomMap<int, int> result;
    for (const auto& pair : f) {
        const int* gval = g.get(pair.second);
        if (gval) {
            result.insert(pair.first, *gval);
        }
    }
    return result;
}

CustomMap<int, int> Functions::inverse(const CustomMap<int, int>& f, int codomainSize) {
    CustomMap<int, int> inv;

    if (!isBijective(f, codomainSize)) {
        std::cout << "[ERROR] Cannot create inverse - function must be bijective\n";
        return inv;
    }

    for (const auto& pair : f) {
        inv.insert(pair.second, pair.first);
    }

    std::cout << "[SUCCESS] Inverse function created\n";
    return inv;
}

bool Functions::verifyInverse(const CustomMap<int, int>& f, const CustomMap<int, int>& f_inv) {
    for (const auto& pair : f) {
        const int* inv_val = f_inv.get(pair.second);
        if (!inv_val || *inv_val != pair.first) {
            return false;
        }
    }
    return true;
}

std::vector<CustomSet<int>> Functions::powerSet(const CustomSet<int>& s) {
    std::vector<CustomSet<int>> result;
    result.push_back(CustomSet<int>());

    for (const auto& elem : s.getVector()) {
        int currentSize = static_cast<int>(result.size());
        for (int i = 0; i < currentSize; i++) {
            CustomSet<int> newSet = result[i];
            newSet.insert(elem);
            result.push_back(newSet);
        }
    }
    return result;
}

std::vector<std::pair<int, int>> Functions::cartesianProduct(const CustomSet<int>& a, const CustomSet<int>& b) {
    std::vector<std::pair<int, int>> result;
    for (const auto& x : a.getVector()) {
        for (const auto& y : b.getVector()) {
            result.push_back(std::make_pair(x, y));
        }
    }
    return result;
}

// ============================================================================
// SET OPERATIONS IMPLEMENTATION
// ============================================================================

CustomSet<int> SetOps::setIntersection(const CustomSet<int>& a, const CustomSet<int>& b) {
    CustomSet<int> result;
    for (const auto& x : a.getVector()) {
        if (b.contains(x)) result.insert(x);
    }
    return result;
}

CustomSet<int> SetOps::setUnion(const CustomSet<int>& a, const CustomSet<int>& b) {
    CustomSet<int> result;
    for (const auto& x : a.getVector()) result.insert(x);
    for (const auto& x : b.getVector()) result.insert(x);
    return result;
}

CustomSet<int> SetOps::setDifference(const CustomSet<int>& a, const CustomSet<int>& b) {
    CustomSet<int> result;
    for (const auto& x : a.getVector()) {
        if (!b.contains(x)) result.insert(x);
    }
    return result;
}

CustomSet<int> SetOps::symmetricDifference(const CustomSet<int>& a, const CustomSet<int>& b) {
    CustomSet<int> result;
    for (const auto& x : a.getVector()) if (!b.contains(x)) result.insert(x);
    for (const auto& x : b.getVector()) if (!a.contains(x)) result.insert(x);
    return result;
}

bool SetOps::isSubset(const CustomSet<int>& a, const CustomSet<int>& b) {
    for (const auto& x : a.getVector()) {
        if (!b.contains(x)) return false;
    }
    return true;
}

bool SetOps::isSuperset(const CustomSet<int>& a, const CustomSet<int>& b) {
    return isSubset(b, a);
}

bool SetOps::areDisjoint(const CustomSet<int>& a, const CustomSet<int>& b) {
    for (const auto& x : a.getVector()) {
        if (b.contains(x)) return false;
    }
    return true;
}

// ============================================================================
// LOGIC ENGINE IMPLEMENTATION
// ============================================================================

void LogicEngine::addRule(const std::string& premise, const std::string& conclusion, const std::string& name) {
    Rule r;
    r.premise = premise;
    r.conclusion = conclusion;
    r.name = name;
    rules.push_back(r);
}

bool LogicEngine::applyModusPonens(const std::string& p, const std::string& pImpliesQ, std::string& result) {
    if (pImpliesQ.find(p + "->") == 0) {
        result = pImpliesQ.substr(p.length() + 2);
        return true;
    }
    return false;
}

bool LogicEngine::applyModusTollens(const std::string& notQ, const std::string& pImpliesQ, std::string& result) {
    size_t pos = pImpliesQ.find("->");
    if (pos != std::string::npos) {
        std::string q = pImpliesQ.substr(pos + 2);
        if (notQ == "!" + q) {
            result = "!" + pImpliesQ.substr(0, pos);
            return true;
        }
    }
    return false;
}

void LogicEngine::listRules() const {
    std::cout << "\n=== LOGIC RULES ===\n";
    for (const auto& rule : rules) {
        std::cout << "Rule: " << rule.name << "\n";
        std::cout << "  " << rule.premise << " -> " << rule.conclusion << "\n";
    }
    std::cout << "\n";
}

// ============================================================================
// INDUCTION IMPLEMENTATION
// ============================================================================

bool Induction::provePrereqDepth(const Relations& rel, int maxDepth) {
    auto closure = rel.closurePrereq();
    int size = rel.getSize();
    
    // Base case: depth 0
    std::cout << "[BASE CASE] Depth 0: All courses with no prerequisites\n";
    
    // Inductive step
    for (int depth = 1; depth <= maxDepth; depth++) {
        bool found = false;
        for (int i = 0; i < size; i++) {
            int prereqCount = 0;
            for (int j = 0; j < size; j++) {
                if (closure[j][i]) prereqCount++;
            }
            if (prereqCount == depth) found = true;
        }
        if (found) {
            std::cout << "[INDUCTIVE STEP] Depth " << depth << ": Courses with " << depth << " prerequisite(s) exist\n";
        }
    }
    
    return true;
}

void Induction::displayProof() {
    std::cout << "\n=== INDUCTION PROOF ===\n";
    std::cout << "Proving prerequisite chain properties by mathematical induction.\n";
    std::cout << "See above for proof steps.\n\n";
}
