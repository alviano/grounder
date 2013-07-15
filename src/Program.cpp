/*
 * Program.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "Program.h"

ostream& operator<<(ostream& out, const Program& program) {
    for(list<Rule*>::const_iterator it = program.rules.begin(); it != program.rules.end(); ++it)
        out << **it << endl;
    return out;
}

Program::Program() {
    falsePredicate = new Predicate(createPredicate("#fail"));
}

Program::~Program() {
    delete falsePredicate;

    for(list<Rule*>::iterator it = rules.begin(); it != rules.end(); ++it)
        delete *it;

    for(unordered_map<string, Predicate>::iterator it = predicates.begin(); it != predicates.end(); ++it)
        delete it->second.data;

    for(unordered_map<string, StringTerm>::iterator it = stringTerms.begin(); it != stringTerms.end(); ++it)
        delete it->second.data;

    for(vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
        delete *it;
}

Predicate
Program::createPredicate(
        const string& name) {
    unordered_map<string, Predicate>::iterator it = predicates.find(name);
    if(it != predicates.end())
        return it->second;
    return predicates.insert(unordered_map<string, Predicate>::value_type(name, Predicate(*this, name))).first->second;
}

StringTerm
Program::createStringTerm(
        const string& name) {
    unordered_map<string, StringTerm>::iterator it = stringTerms.find(name);
    if(it != stringTerms.end())
        return it->second;
    return stringTerms.insert(unordered_map<string, StringTerm>::value_type(name, StringTerm(name))).first->second;
}

void
Program::addRule(
        Rule* rule) {
    assert(rule != NULL);
    rules.push_back(rule);
}

void
Program::computeComponents() {
    assert(components.empty());

    DependenciesGraph dependenciesGraph;
    DependenciesGraph positiveDependenciesGraph;

    for(list<Rule*>::const_iterator r = rules.begin(); r != rules.end(); ++r) {
        const Rule* rule = *r;
        rule->addDependencies(dependenciesGraph, false);
        rule->addDependencies(positiveDependenciesGraph, true);
    }

    dependenciesGraph.computeComponents();
    for(unordered_map<string, Predicate>::iterator p = predicates.begin(); p != predicates.end(); ++p)
        p->second.addToComponents(dependenciesGraph);

    positiveDependenciesGraph.computeComponents();
    for(unordered_map<string, Predicate>::iterator p = predicates.begin(); p != predicates.end(); ++p)
        p->second.addToComponents(positiveDependenciesGraph);

    for(int i = 1, j = 1; ;) {
        assert(i < positiveDependenciesGraph.getNumberOfComponents());
        assert(j < dependenciesGraph.getNumberOfComponents());
        Component* c_i = positiveDependenciesGraph.getComponent(i);
        Component* c_j = dependenciesGraph.getComponent(j);
        assert(c_i->size() > 0);
        assert(c_j->size() > 0);
        if(c_i->getIndex() == -1 && c_j->contains(c_i->front())) {
            c_i->setIndex(components.size());
            components.push_back(c_i);

            c_j->removeAll(*c_i);
            if(c_j->size() == 0)
                if(++j >= dependenciesGraph.getNumberOfComponents())
                    break;
            i = 1;
        }
        else
            ++i;
    }

    positiveDependenciesGraph.detachComponents();
}

void
Program::printComponents(ostream& out) const {
    for(unsigned i = 0; i < components.size(); ++i)
        out << *components[i] << " ";
}

void
Program::sortRules() {
    for(list<Rule*>::iterator it = rules.begin(); it != rules.end(); ++it) {
        Rule* rule = *it;
        rule->sort();
    }
}

void
Program::indexPredicates() {
    for(list<Rule*>::iterator it = rules.begin(); it != rules.end(); ++it) {
        Rule* rule = *it;
        rule->indexPredicates();
    }
}

void
Program::instantiate() {
    for(vector<Component*>::iterator it = components.begin(); it != components.end(); ++it) {
        Component* component = *it;
        component->instantiate();
    }
}
