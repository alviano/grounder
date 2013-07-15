/*
 * StandardNegativeLiteral.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "StandardNegativeLiteral.h"

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
