/*
 * StringTerm.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef STRINGTERM_H_
#define STRINGTERM_H_

#include "Term.h"
#include "Variable.h"

class StringTerm : public Term {
    friend class Program;
public:
    virtual ~StringTerm();

    virtual void print(ostream& out) const { out << this->data->name; }
    virtual Clonable* clone() const { return new StringTerm(*this); }

    virtual int addVariables(unordered_map<string, int>& variableFirstOccurrence, int indexInRule) const { return 0; }

    const string& getName() const { return this->data->name; }

private:
    StringTerm(const string& name);

    struct Data {
        string name;
    };
    Data* data;
};

#endif /* STRINGTERM_H_ */
