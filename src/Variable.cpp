/*
 * Variable.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "Variable.h"

Variable::Variable(
        const string& name_)
: name(name_) {
}

Variable::~Variable() {
}

int
Variable::addVariables(unordered_map<string, int>& variableFirstOccurrence, int indexInRule) const {
    return variableFirstOccurrence.insert(unordered_map<string, int>::value_type(this->getName(), indexInRule)).second ? 1 : 0;
}

Term*
Variable::replace(
        const unordered_map<string, Term*>& variables) const {
    unordered_map<string, Term*>::const_iterator it = variables.find(name);
    assert(it != variables.end());
    return static_cast<Term*>(it->second->clone());
}
