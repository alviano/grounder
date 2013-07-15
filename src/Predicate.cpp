/*
 * Predicate.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "Predicate.h"
#include "Rule.h"
#include "Program.h"

ostream& operator<<(ostream& out, const Predicate& predicate) {
    return out << predicate.getName();
}

Predicate::Predicate(
        Program& program,
        const string& name)
: data(new Data(program, name)),
  arity(0) {
}

Predicate::~Predicate() {
}

void
Predicate::setArity(
        int value) {
    assert(value >= 0);
    assert(this->arity == 0);
    this->arity = value;
    this->data->arity.insert(unordered_map<int, SingleData >::value_type(this->arity, SingleData()));
}

void
Predicate::addToComponents(
        DependenciesGraph& graph) {
    for(unordered_map<int, SingleData>::iterator a = data->arity.begin(); a != data->arity.end(); ++a) {
        Predicate predicate = *this;
        predicate.arity = a->first;
        //if(predicate.hasDefiningRules())
            graph.addToItsComponent(predicate);
    }
}

void
Predicate::createIndex(
        const list<int>& positionsToIndex) {
    data->arity[this->arity].indices.create(positionsToIndex);
    cout << *this << this->arity << ": " << data->arity[this->arity].indices << endl;
}

void
Predicate::addDefiningRules(
        list<Rule*>& exitRules,
        list<Rule*>& recursiveRules) {
    for(list<Rule*>::iterator it = data->arity[this->arity].headOccurrences.begin(); it != data->arity[this->arity].headOccurrences.end(); ++it) {
        Rule* rule = *it;
        if(rule->isRecursive())
            recursiveRules.push_back(rule);
        else
            exitRules.push_back(rule);
    }
}

const Indices::Tuples*
Predicate::instantiate(
        const Atom& atom,
        const unordered_map<string, Term*>& variables) {
    return data->arity[this->arity].indices.instantiate(atom, variables);
}
