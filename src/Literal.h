/*
 * Literal.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef LITERAL_H_
#define LITERAL_H_

#include "common.h"
#include "Clonable.h"
#include "Atom.h"
#include "DependenciesGraph.h"

class Output;

class Literal : public Clonable {
    friend ostream& operator<<(ostream& out, const Literal& literal);
public:
    Literal();
    virtual ~Literal();

    virtual void print(ostream& out) const = 0;
    virtual void output(Output& builder, const unordered_map<string, Term*>& variables, const Atom& head) const = 0;
    virtual void addDependencies(DependenciesGraph& graph, const Atom& head, bool onlyPositive) const = 0;
    virtual int getPriority(int componentIndex) const = 0;
    virtual int addVariables(unordered_map<string, int>& variableFirstOccurrence, int indexInRule) const = 0;
    virtual void indexPredicate(unordered_map<string, int>& variableFirstOccurrence, int indexInRule) = 0;
    virtual bool isRecursiveWith(const Predicate& predicate) const = 0;
    virtual bool instantiate(const unordered_map<string, Term*>& variables, const Indices::Tuples*& tuples) = 0;
    virtual void bind(unordered_map<string, Term*>& variables, const Terms& tuple) const = 0;
};

class Literals : public ClonableVector<Literal> {

};

#endif /* LITERAL_H_ */
