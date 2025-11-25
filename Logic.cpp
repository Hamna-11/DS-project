#include "Logic.h"
#include <iostream>

void LogicEngine::addRule(const std::string& name, const std::vector<int>& ant,
    const std::vector<int>& cons, const std::string& desc) {
    Rule r;
    r.name = name;
    r.antecedent = ant;
    r.consequent = cons;
    r.description = desc;
    rules.push_back(r);
}

void LogicEngine::addFact(const std::string& fact, bool value) {
    facts.insert(fact, value);
}

bool LogicEngine::checkRule(const Rule& r) const {
    for (int id : r.antecedent) {
        std::string key = "course_" + std::to_string(id);
        const bool* val = facts.get(key);
        if (!val || !(*val)) return false;
    }
    return true;
}

std::vector<std::string> LogicEngine::inferConsequences() {
    std::vector<std::string> inferred;

    for (const auto& rule : rules) {
        if (checkRule(rule)) {
            for (int id : rule.consequent) {
                std::string key = "course_" + std::to_string(id);
                if (!facts.contains(key)) {
                    facts.insert(key, true);
                    inferred.push_back("Inferred: " + key + " from rule " + rule.name);
                }
            }
        }
    }

    return inferred;
}

void LogicEngine::displayRules() const {
    std::cout << "\n=== LOGIC RULES ===\n";
    for (const auto& rule : rules) {
        std::cout << "Rule: " << rule.name << "\n";
        std::cout << "  Description: " << rule.description << "\n";
        std::cout << "  Antecedent: ";
        for (int id : rule.antecedent) std::cout << id << " ";
        std::cout << "\n  Consequent: ";
        for (int id : rule.consequent) std::cout << id << " ";
        std::cout << "\n\n";
    }
}

void LogicEngine::displayFacts() const {
    std::cout << "\n=== KNOWN FACTS ===\n";
    for (const auto& pair : facts) {
        std::cout << pair.first << " = " << (pair.second ? "TRUE" : "FALSE") << "\n";
    }
    std::cout << "\n";
}