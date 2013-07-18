/*
 * StandardNegativeLiteral.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "StandardNegativeLiteral.h"

#include "Output.h"

StandardNegativeLiteral::StandardNegativeLiteral(
        const Atom& atom)
: StandardLiteral(atom) {

}

StandardNegativeLiteral::~StandardNegativeLiteral() {
}

void
StandardNegativeLiteral::addDependencies(
        DependenciesGraph& graph,
        const Atom& head,
        bool onlyPositive) const {
    if(!onlyPositive)
        StandardLiteral::addDependencies(graph, head, onlyPositive);
}

void
StandardNegativeLiteral::output(
        Output& builder,
        const unordered_map<string, Term*>& variables,
        const Atom& head) const {
    if(head.getPredicate().getComponent().getIndex() <= atom.getPredicate().getComponent().getIndex()) {
        stringstream ss;
        atom.print(ss, variables);
        builder.negativeLiteral(ss.str());
    }
}

bool
StandardNegativeLiteral::instantiate(
        const unordered_map<string, Term*>& variables,
        const Indices::Tuples*& tuples) {
    tuples = atom.instantiate(variables);
    return tuples == NULL;
}
