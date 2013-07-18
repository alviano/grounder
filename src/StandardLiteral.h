/*
 * StandardLiteral.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef STANDARDLITERAL_H_
#define STANDARDLITERAL_H_

#include "common.h"

#include "Atom.h"
#include "Literal.h"

class StandardLiteral : public Literal {
public:
    StandardLiteral(const Atom& atom);
    virtual ~StandardLiteral();

    virtual void print(ostream& out) const { out << this->getAtom(); }

    const Atom& getAtom() const { return this->atom; }

    virtual void addDependencies(DependenciesGraph& graph, const Atom& head, bool onlyPositive) const;
    virtual int getPriority(int componentIndex) const;
    virtual int addVariables(unordered_map<string, int>& variableFirstOccurrence, int indexInRule) const { return atom.addVariables(variableFirstOccurrence, indexInRule); }
    virtual void indexPredicate(unordered_map<string, int>& variableFirstOccurrence, int indexInRule) { atom.indexPredicate(variableFirstOccurrence, indexInRule); }
    virtual bool isRecursiveWith(const Predicate& predicate) const;

protected:
    Atom atom;
};

#endif /* STANDARDLITERAL_H_ */
