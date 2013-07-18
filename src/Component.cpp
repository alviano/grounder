/*
 * Component.cpp
 *
 *  Created on: Jul 4, 2013
 *      Author: malvi
 */

#include "Component.h"

#include "Rule.h"

ostream& operator<<(ostream& out, const Component& c) {
    out << "[";
    for(list<Predicate>::const_iterator it = c.predicates.begin(); it != c.predicates.end(); ++it)
        out << *it << " ";
    return out << "]" << (c.isRecursive() ? "r" : "");
}

Component::Component()
: recursive(false),
  index(-1) {

}

Component::~Component() {
}

void
Component::addPredicate(
        const Predicate& predicate,
        bool selfLoop) {
    if(selfLoop || !predicates.empty())
        recursive = true;
    predicates.push_back(predicate);
}

bool
Component::contains(const Predicate& predicate) const {
    return find(predicates.begin(), predicates.end(), predicate) != predicates.end();
}

void
Component::removeAll(
        const Component& c) {
    for(list<Predicate>::const_iterator it = c.predicates.begin(); it != c.predicates.end(); ++it)
        predicates.remove(*it);
}

void
Component::instantiate() {
    cerr << "Component::instantiate() " << *this << endl;
    list<Rule*> exitRules;
    list<Rule*> recursiveRules;

    for(list<Predicate>::iterator it = predicates.begin(); it != predicates.end(); ++it)
        it->addDefiningRules(exitRules, recursiveRules);

    for(list<Rule*>::iterator it = exitRules.begin(); it != exitRules.end(); ++it) {
        Rule* rule = *it;
        rule->instantiate();
    }

}
