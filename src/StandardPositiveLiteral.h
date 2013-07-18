/*
 * StandardPositiveLiteral.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef STANDARDPOSITIVELITERAL_H_
#define STANDARDPOSITIVELITERAL_H_

#include "common.h"

#include "StandardLiteral.h"

class StandardPositiveLiteral : public StandardLiteral {
public:
    StandardPositiveLiteral(const Atom& atom);
    virtual ~StandardPositiveLiteral();

    virtual Clonable* clone() const { return new StandardPositiveLiteral(*this); }

    virtual bool instantiate(const unordered_map<string, Term*>& variables, const Indices::Tuples*& tuples);

    virtual void output(Output& builder, const unordered_map<string, Term*>& variables, const Atom& head) const;

    virtual int getPriority(int componentIndex) const;

    virtual void bind(unordered_map<string, Term*>& variables, const Terms& tuple) const;
};

#endif /* STANDARDPOSITIVELITERAL_H_ */
