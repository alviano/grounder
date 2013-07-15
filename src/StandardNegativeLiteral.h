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

    virtual void addDependencies(DependenciesGraph& graph, const Atom& head, bool onlyPositive) const;
};

#endif /* STANDARDNEGATIVELITERAL_H_ */
