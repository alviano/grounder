/*
 * NormalRule.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef NORMALRULE_H_
#define NORMALRULE_H_

#include "Rule.h"
#include "Atom.h"
#include "Body.h"

class NormalRule : public Rule {
public:
    NormalRule(const Atom& head, const Body& body);
    virtual ~NormalRule();

    virtual void print(ostream& out) const;

    virtual void addDependencies(DependenciesGraph& graph, bool onlyPositive) const;
    virtual void sort();
    virtual void indexPredicates();
    virtual bool isRecursive() const;
    virtual void instantiate();

private:
    Atom head;
    Body body;

    void instantiateLiteral(unsigned index);
};

#endif /* NORMALRULE_H_ */
