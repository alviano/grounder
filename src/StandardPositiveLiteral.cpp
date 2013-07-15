/*
 * StandardPositiveLiteral.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "StandardPositiveLiteral.h"
#include "Component.h"

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
