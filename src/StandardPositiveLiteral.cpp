/*
 * StandardPositiveLiteral.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "StandardPositiveLiteral.h"
#include "Component.h"
#include "Output.h"

StandardPositiveLiteral::StandardPositiveLiteral(
        const Atom& atom)
: StandardLiteral(atom) {
}

StandardPositiveLiteral::~StandardPositiveLiteral() {
}

int
StandardPositiveLiteral::getPriority(
        int componentIndex) const {
    int res = StandardLiteral::getPriority(componentIndex);
    if(res != 111)
        return res;

    return componentIndex == getAtom().getPredicate().getComponent().getIndex() ? 666 : 333;
}

void
StandardPositiveLiteral::output(
        Output& builder,
        const unordered_map<string, Term*>& variables,
        const Atom& head) const {
    stringstream ss;
    if(!atom.print(ss, variables))
        builder.positiveLiteral(ss.str());
}

void
StandardPositiveLiteral::bind(
        unordered_map<string, Term*>& variables,
        const Terms& tuple) const {
    atom.bind(variables, tuple);
}

bool
StandardPositiveLiteral::instantiate(
        const unordered_map<string, Term*>& variables,
        const Indices::Tuples*& tuples) {
    tuples = atom.instantiate(variables);
    return tuples != NULL;
}

