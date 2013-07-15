/*
 * Program.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "common.h"
#include "Predicate.h"
#include "Rule.h"
#include "StringTerm.h"
#include "Component.h"
#include "DependenciesGraph.h"

class Program {
    friend ostream& operator<<(ostream& out, const Program& program);
public:
    Program();
    virtual ~Program();

    Predicate createPredicate(const string& name);
    StringTerm createStringTerm(const string& name);

    const Predicate& getFalsePredicate() const { return *falsePredicate; }
    void addRule(Rule* rule);

    void computeComponents();
    void printComponents(ostream& out) const;

    void sortRules();
    void indexPredicates();
    void instantiate();

private:
    Program(const Program&) { assert(0); }

    Predicate* falsePredicate;
    list<Rule*> rules;

    vector<Component*> components;

    unordered_map<string, Predicate> predicates;
    unordered_map<string, StringTerm> stringTerms;
};

#endif /* PROGRAM_H_ */
