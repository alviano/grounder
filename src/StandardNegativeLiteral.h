/*
 * StandardNegativeLiteral.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef STANDARDNEGATIVELITERAL_H_
#define STANDARDNEGATIVELITERAL_H_

#include "StandardLiteral.h"

class StandardNegativeLiteral : public StandardLiteral {
public:
    StandardNegativeLiteral(const Atom& atom);
    virtual ~StandardNegativeLiteral();

    virtual void print(ostream& out) const { out << "not "; StandardLiteral::print(out); }
    virtual Clonable* clone() const { return new StandardNegativeLiteral(*this); }

    virtual void output(Output& builder, const unordered_map<string, Term*>& variables, const Atom& head) const;

    virtual bool instantiate(const unordered_map<string, Term*>& variables, const Indices::Tuples*& tuples);

    virtual void addDependencies(DependenciesGraph& graph, const Atom& head, bool onlyPositive) const;

    virtual void bind(unordered_map<string, Term*>& variables, const Terms& tuple) const { assert(0); }
};

#endif /* STANDARDNEGATIVELITERAL_H_ */
