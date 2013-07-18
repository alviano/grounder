/*
 * DependenciesGraph.h
 *
 *  Created on: Jul 4, 2013
 *      Author: malvi
 */

#ifndef DEPENDENCIESGRAPH_H_
#define DEPENDENCIESGRAPH_H_

#include "common.h"
#include "Predicate.h"
#include "Program.h"

class AdjacencyList;

class DependenciesGraph {
public:
    DependenciesGraph();
    virtual ~DependenciesGraph();

    void addDependency(const Predicate& from, const Predicate& to);
    void computeComponents();

    int getComponentIndex(const Predicate& p) const;
    int getNumberOfComponents() const { return components.size(); }
    Component* getComponent(int idx) { return components[idx]; }

    void addToItsComponent(Predicate& p);

    void detachComponents() { components.clear(); }
    void notifyHeadPredicate(const Predicate& p);

    void printComponents(ostream& out) const;

private:
    AdjacencyList& graph;
    set<int> selfLoops;
    unordered_map<string, unordered_map<int, int> > predicateIndex;
    int nextIndex;

    vector<int> componentIndex;
    vector<Component*> components;

    int getIndex(const Predicate& p);
    int getIndex(const Predicate& p) const;
};

#endif /* DEPENDENCIESGRAPH_H_ */
