/*
 * Rule.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "Rule.h"

ostream& operator<<(ostream& out, const Rule& rule) {
    rule.print(out);
    return out;
}

Rule::Rule() {
}

Rule::~Rule() {
    for(unordered_map<string, Term*>::iterator it = variableSubstitutions.begin(); it != variableSubstitutions.end(); ++it)
        delete it->second;
}
