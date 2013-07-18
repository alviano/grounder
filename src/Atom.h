/*
 * Atom.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef ATOM_H_
#define ATOM_H_

#include "common.h"

#include "Predicate.h"
#include "Term.h"
#include "Variable.h"

class Atom {
    friend ostream& operator<<(ostream& out, const Atom& atom);
public:
    Atom(const Predicate& predicate, const Terms& terms = Terms());
    virtual ~Atom();

    const Predicate& getPredicate() const { return predicate; }
    int getArity() const { return predicate.getArity(); }
    const Terms& getTerms() const { return terms; }

    void addHeadOccurrence(Rule& rule) { this->predicate.addHeadOccurrence(rule); }
    int addVariables(unordered_map<string, int>& variableFirstOccurrence, int indexInRule) const;

    void indexPredicate(unordered_map<string, int>& variableFirstOccurrence, int indexInRule);
    const Indices::Tuples* instantiate(const unordered_map<string, Term*>& variables) { return predicate.instantiate(*this, variables); }
    const list<int>& getBoundArguments() const { return boundArguments; }

    void addInstance(const unordered_map<string, Term*>& variables);
    void bind(unordered_map<string, Term*>& variables, const Terms& tuple) const;

    bool print(ostream& out, const unordered_map<string, Term*>& variables) const;

private:
    Predicate predicate;
    Terms terms;
    list<int> boundArguments;
};

#endif /* ATOM_H_ */
