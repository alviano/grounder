/*
 * NormalRule.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "NormalRule.h"
#include "Component.h"
#include "Variable.h"

NormalRule::NormalRule(
        const Atom& head_,
        const Body& body_)
: head(head_),
  body(body_) {
    head.addHeadOccurrence(*this);
}

NormalRule::~NormalRule() {
}

void
NormalRule::print(
        ostream& out) const {
    out << head;
    if(!body.empty())
        out << " :- " << body;
    out << ".";
}

void
NormalRule::addDependencies(
        DependenciesGraph& graph,
        bool onlyPositive) const {
    if(body.size() == 0)
        graph.notifyHeadPredicate(head.getPredicate());
    else
        for(unsigned i = 0; i < body.size(); ++i)
            body[i].addDependencies(graph, head, onlyPositive);
}

void
NormalRule::sort() {
    int headIndex = head.getPredicate().getComponent().getIndex();
    for(unsigned i = 0; i < body.size(); ++i) {
        unsigned max = i;
        int maxValue = body[i].getPriority(headIndex);

        for(unsigned j = i+1; j < body.size(); ++j) {
            int tmp = body[j].getPriority(headIndex);
            if(tmp > maxValue) {
                max = j;
                maxValue = tmp;
            }
        }

        if(max != i) {
            body.swap(i, max);
        }
    }
}

void
NormalRule::indexPredicates() {
    for(unsigned i = 0; i < body.size(); ++i) {
        body[i].indexPredicate(variableFirstOccurrence, i);
    }
}

bool
NormalRule::isRecursive() const {
    for(unsigned i = 0; i < body.size(); ++i) {
        if(body[i].isRecursiveWith(head.getPredicate()))
            return true;
    }
    return false;
}

void
NormalRule::instantiate() {
    instantiateLiteral(0);
}

void
NormalRule::instantiateLiteral(
        unsigned index) {
    cout << "NormalRule::instantiateLiteral() " << index << endl;
    for(unordered_map<string, Term*>::const_iterator it = variableSubstitutions.begin(); it != variableSubstitutions.end(); ++it)
        cout << it->first << "=>" << *it->second << endl;
    if(index >= body.size()) {
        head.addInstance(variableSubstitutions);
        return;
    }
    const Indices::Tuples* res = body[index].instantiate(variableSubstitutions);
    if(res != NULL) {
        for(Indices::Tuples::const_iterator it = res->begin(); it != res->end(); ++it) {
            body[index].bind(variableSubstitutions, *it->second);
            instantiateLiteral(index + 1);
        }
    }
}
