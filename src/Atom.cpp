/*
 * Atom.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "Atom.h"

ostream& operator<<(ostream& out, const Atom& atom) {
    if(atom.getPredicate().getArity() == 0)
        return out << atom.getPredicate();
    return out << atom.predicate << "(" << atom.getTerms() << ")";
}

Atom::Atom(
        const Predicate& predicate_,
        const Terms& terms_)
: predicate(predicate_),
  terms(terms_) {
    this->predicate.setArity(terms.size());
}

Atom::~Atom() {
}

int
Atom::addVariables(
        unordered_map<string, int>& variableFirstOccurrence,
        int indexInRule) const {
    int res = 0;
    for(unsigned i = 0; i < terms.size(); ++i)
        res += terms[i].addVariables(variableFirstOccurrence, indexInRule);
    return res;
}

void
Atom::indexPredicate(
        unordered_map<string, int>& variableFirstOccurrence,
        int indexInRule) {
    assert(boundArguments.empty());
    vector<list<int>::iterator> positions;
    list<int>::iterator last = boundArguments.begin();
    for(int i = 0; i <= indexInRule; ++i) {
        boundArguments.insert(last, -1);
        positions.push_back(++last);
    }

    for(unsigned i = 0; i < terms.size(); ++i) {
        unordered_map<string, int> variables;
        terms[i].addVariables(variables, indexInRule);

        bool isConstant = true;
        for(unordered_map<string, int>::const_iterator it = variables.begin(); it != variables.end(); ++it) {
            isConstant = false;
            pair<unordered_map<string, int>::iterator, bool> res = variableFirstOccurrence.insert(*it);
            if(!res.second) {
                boundArguments.insert(positions[res.first->second + 1], i);
            }
        }
        if(isConstant)
            boundArguments.insert(positions[0], i);
    }

    for(list<int>::iterator it = boundArguments.begin(); it != boundArguments.end();) {
        if(*it < 0) {
            boundArguments.erase(it++);
        }
        else
            ++it;
    }

    predicate.createIndex(boundArguments);
}

void
Atom::addInstance(
        const unordered_map<string, Term*>& variables) {
    Terms* tuple = new Terms();
    for(unsigned i = 0; i < terms.size(); ++i)
        tuple->push_back(terms[i].replace(variables));
    predicate.addInstance(tuple);
    cout << "Atom::addInstance(): " << *this << endl;
}

void
Atom::bind(
        unordered_map<string, Term*>& variables,
        const Terms& tuple) const {
    assert(static_cast<unsigned>(getArity()) == tuple.size());
    list<int>::const_iterator it = boundArguments.begin();
    int lastBound = -1;
    for(int i = 0; i < getArity(); ++i) {
        while(it != boundArguments.end() && *it <= i) {
            ++it;
            lastBound = *it;
        }
        if(i != lastBound) {
            unordered_map<string, int> vars;
            terms[i].addVariables(vars, -1);

            // TODO: manage functions
            assert(vars.size() == 1);
            pair<unordered_map<string, Term*>::iterator, bool> res = variables.insert(unordered_map<string, Term*>::value_type(vars.begin()->first, NULL));
            if(!res.second)
                delete res.first->second;
            res.first->second = static_cast<Term*>(tuple[i].clone());
        }
    }
}
