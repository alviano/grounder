/*
 * Rule.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef RULE_H_
#define RULE_H_

#include "common.h"
#include "DependenciesGraph.h"
#include "Variable.h"

class Rule {
    friend ostream& operator<<(ostream& out, const Rule& rule);
public:
    Rule();
    virtual ~Rule();

    virtual void print(ostream& out) const = 0;
    virtual void addDependencies(DependenciesGraph& graph, bool onlyPositive) const = 0;
    virtual void sort() = 0;
    virtual void indexPredicates() = 0;
    virtual bool isRecursive() const = 0;
    virtual void instantiate() = 0;

protected:
    unordered_map<string, int> variableFirstOccurrence;
    unordered_map<string, Term*> variableSubstitutions;
};

#endif /* RULE_H_ */
