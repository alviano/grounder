/*
 * StandardLiteral.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "StandardLiteral.h"
#include "Component.h"
#include "Variable.h"

StandardLiteral::StandardLiteral(
        const Atom& atom_)
: atom(atom_){

}

StandardLiteral::~StandardLiteral() {
}

void
StandardLiteral::addDependencies(
        DependenciesGraph& graph,
        const Atom& head,
        bool onlyPositive) const {
    graph.addDependency(head.getPredicate(), getAtom().getPredicate());
}

int
StandardLiteral::getPriority(
        int componentIndex) const {
    if(getAtom().getPredicate().getComponent().getIndex() > componentIndex)
        return 0;

    unordered_map<string, int> variableFirstOccurrence;
    if(addVariables(variableFirstOccurrence, -1) == 0)
        return 999;

    return 111;
}

bool
StandardLiteral::isRecursiveWith(
        const Predicate& predicate) const {
    return atom.getPredicate().getComponent().getIndex() == predicate.getComponent().getIndex();
}

const Indices::Tuples*
StandardLiteral::instantiate(
        const unordered_map<string, Term*>& variables) {
    return atom.instantiate(variables);
}

void
StandardLiteral::bind(
        unordered_map<string, Term*>& variables,
        const Terms& tuple) const {
    atom.bind(variables, tuple);
}
