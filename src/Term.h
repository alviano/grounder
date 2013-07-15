/*
 * Term.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef TERM_H_
#define TERM_H_

#include "common.h"
#include "Clonable.h"

class Variable;

class Term : public Clonable {
    friend ostream& operator<<(ostream& out, const Term& term);
public:
    Term();
    virtual ~Term();

    virtual void print(ostream& out) const = 0;
    virtual int addVariables(unordered_map<string, int>& variableFirstOccurrence, int indexInRule) const = 0;

    virtual Term* replace(const unordered_map<string, Term*>& variables) const { return static_cast<Term*>(this->clone()); }
};

class Terms : public ClonableVector<Term> {

};

#endif /* TERM_H_ */
