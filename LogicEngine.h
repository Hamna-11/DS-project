#ifndef LOGICENGINE_H
#define LOGICENGINE_H

#include "CourseManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

class LogicEngine {
public:
    struct Rule {
        std::string name;
        std::vector<int> antecedent;
        std::vector<int> consequent;
        std::string description;
    };
private:
    std::vector<Rule> rules;
    CustomMap<std::string, bool> facts;
public:
    void addRule(const std::string&, const std::vector<int>&, const std::vector<int>&, const std::string&);
    void addFact(const std::string&, bool value = true);
    bool checkRule(const Rule&) const;
    std::vector<std::string> inferConsequences();
    void displayRules() const;
    void displayFacts() const;
};

#endif#pragma once
