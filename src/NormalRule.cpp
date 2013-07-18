/*
 * NormalRule.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "NormalRule.h"
#include "Component.h"
#include "Variable.h"
#include "Output.h"

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
    graph.notifyHeadPredicate(head.getPredicate());
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
    /*
    cout << "NormalRule::instantiateLiteral() " << index << endl;
    for(unordered_map<string, Term*>::const_iterator it = variableSubstitutions.begin(); it != variableSubstitutions.end(); ++it)
        cout << it->first << "=>" << *it->second << endl;
        */
    if(index >= body.size()) {
        head.addInstance(variableSubstitutions);

        Output& builder = head.getPredicate().getProgram().getOutputBuilder();
        stringstream headSS;
        head.print(headSS, variableSubstitutions);
        builder.normalRuleStart(headSS.str());
        for(unsigned i = 0; i < body.size(); ++i)
            body[i].output(builder, variableSubstitutions, head);
        builder.normalRuleEnd();

        return;
    }
    const Indices::Tuples* tuples = NULL;
    if(body[index].instantiate(variableSubstitutions, tuples)) {
        if(tuples != NULL) {
            for(Indices::Tuples::const_iterator it = tuples->begin(); it != tuples->end(); ++it) {
                body[index].bind(variableSubstitutions, *it->second);
                instantiateLiteral(index + 1);
            }
        }
        else
            instantiateLiteral(index + 1);
    }
}
