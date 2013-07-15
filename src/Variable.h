/*
 * Variable.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include "common.h"
#include "Term.h"

class Variable : public Term {
public:
    Variable(const string& name);
    virtual ~Variable();

    const string& getName() const { return name; }

    virtual Clonable* clone() const { return new Variable(*this); }
    virtual void print(ostream& out) const { out << this->name; }

    virtual int addVariables(unordered_map<string, int>& variableFirstOccurrence, int indexInRule) const;
    virtual Term* replace(const unordered_map<string, Term*>& variables) const;

private:
    string name;
};

#endif /* VARIABLE_H_ */
