#include "LogicEngine.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>

void LogicEngine::addRule(const std::string& name, const std::vector<int>& ante,
    const std::vector<int>& cons, const std::string& desc) {
    rules.push_back({ name, ante, cons, desc });
    std::cout << "[SUCCESS] Added rule: " << name << "\n";
}

void LogicEngine::addFact(const std::string& fact, bool value) {
    facts.insert(fact, value);
}

bool LogicEngine::checkRule(const Rule& rule) const {
    for (int a : rule.antecedent) {
        std::string key = "course_" + std::to_string(a);
        const bool* val = facts.get(key);
        if (!val || !(*val)) return false;
    }
    return true;
}

std::vector<std::string> LogicEngine::inferConsequences() {
    std::vector<std::string> inferred;
    bool changed = true;
    while (changed) {
        changed = false;
        for (const auto& rule : rules) {
            if (checkRule(rule)) {
                for (int c : rule.consequent) {
                    std::string key = "course_" + std::to_string(c);
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

void LogicEngine::displayRules() const {
    std::cout << "\n" << std::string(60, '=') << "\n LOGIC RULES\n" << std::string(60, '=') << "\n\n";
    for (size_t i = 0; i < rules.size(); i++) {
        std::cout << "\nRule " << (i + 1) << ": " << rules[i].name << "\n";
        std::cout << " IF: ";
        for (size_t j = 0; j < rules[i].antecedent.size(); j++) {
            std::cout << "Course(" << rules[i].antecedent[j] << ")";
            if (j < rules[i].antecedent.size() - 1) std::cout << " AND ";
        }
        std::cout << "\n THEN: ";
        for (size_t j = 0; j < rules[i].consequent.size(); j++) {
            std::cout << "Course(" << rules[i].consequent[j] << ")";
            if (j < rules[i].consequent.size() - 1) std::cout << " AND ";
        }
        std::cout << "\n Description: " << rules[i].description << "\n";
    }
}

void LogicEngine::displayFacts() const {
    std::cout << "\n" << std::string(60, '=') << "\n CURRENT FACTS\n" << std::string(60, '=') << "\n\n";
    for (const auto& pair : facts) {
        std::cout << pair.first << " = " << (pair.second ? "TRUE" : "FALSE") << "\n";
    }
}