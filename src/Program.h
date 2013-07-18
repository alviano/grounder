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

class Output;

class Program {
    friend ostream& operator<<(ostream& out, const Program& program);
public:
    Program(Output& outputBuilder);
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

    Output& getOutputBuilder() const { return outputBuilder; }

private:
    Program(const Program& init) : outputBuilder(init.outputBuilder) { assert(0); }

    Output& outputBuilder;
    Predicate* falsePredicate;
    list<Rule*> rules;

    vector<Component*> components;

    unordered_map<string, Predicate> predicates;
    unordered_map<string, StringTerm> stringTerms;
};

#endif /* PROGRAM_H_ */
