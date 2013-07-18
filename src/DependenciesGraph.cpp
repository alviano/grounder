/*
 * DependenciesGraph.cpp
 *
 *  Created on: Jul 4, 2013
 *      Author: malvi
 */

#include "DependenciesGraph.h"

#include "Component.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>

class AdjacencyList: public boost::adjacency_list<> {
};

DependenciesGraph::DependenciesGraph()
: graph(*new AdjacencyList()),
  nextIndex(0) {
}

DependenciesGraph::~DependenciesGraph() {
    for(vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
        delete *it;
    delete &graph;
}

void
DependenciesGraph::addDependency(
        const Predicate& from,
        const Predicate& to) {
    int fromIndex = getIndex(from);
    int toIndex = getIndex(to);
    if(fromIndex == toIndex)
        selfLoops.insert(fromIndex);
    boost::add_edge(fromIndex, toIndex, graph);
}

int
DependenciesGraph::getIndex(
        const Predicate& p) {
    unordered_map<string, unordered_map<int, int> >::iterator it_1 = predicateIndex.find(p.getName());
    if(it_1 == predicateIndex.end())
        it_1 = predicateIndex.insert(unordered_map<string, unordered_map<int, int> >::value_type(p.getName(), unordered_map<int, int>())).first;
    unordered_map<int, int>::iterator it_2 = it_1->second.find(p.getArity());
    if(it_2 == it_1->second.end())
        it_2 = it_1->second.insert(unordered_map<int, int>::value_type(p.getArity(), nextIndex++)).first;
    return it_2->second;
}

int
DependenciesGraph::getIndex(
        const Predicate& p) const {
    unordered_map<string, unordered_map<int, int> >::const_iterator it_1 = predicateIndex.find(p.getName());
    assert(it_1 != predicateIndex.end());
    unordered_map<int, int>::const_iterator it_2 = it_1->second.find(p.getArity());
    assert(it_2 != it_1->second.end());
    return it_2->second;
}

void
DependenciesGraph::computeComponents() {
    assert(componentIndex.empty());
    assert(components.empty());

    componentIndex.resize(boost::num_vertices(graph));
    vector<int> discover_time(boost::num_vertices(graph));
    vector<boost::default_color_type> color(boost::num_vertices(graph));
    vector<boost::graph_traits<boost::adjacency_list<> >::vertex_descriptor> root(boost::num_vertices(graph));

    int numberOfComponents = boost::strong_components(graph, &componentIndex[0], boost::root_map(&root[0]).color_map(&color[0]).discover_time_map(&discover_time[0]));
    while(numberOfComponents-- > 0)
        components.push_back(new Component());
}

int
DependenciesGraph::getComponentIndex(
        const Predicate& p) const {
    assert(getIndex(p) >= 0);
    assert(static_cast<unsigned>(getIndex(p)) < componentIndex.size());
    return componentIndex[getIndex(p)];
}

void
DependenciesGraph::addToItsComponent(
        Predicate& p) {
    int idx = getComponentIndex(p);
    assert(static_cast<unsigned>(idx) < components.size());
    components[idx]->addPredicate(p, selfLoops.find(idx) != selfLoops.end());
    p.setComponent(*components[idx]);
}

void
DependenciesGraph::notifyHeadPredicate(
        const Predicate& p) {
    addDependency(p, p.getProgram().getFalsePredicate());
}

void
DependenciesGraph::printComponents(
        ostream& out) const {
    for(vector<Component*>::const_iterator it = components.begin(); it != components.end(); ++it) {
        assert(*it != NULL);
        out << **it << " ";
    }
    out << endl;
}
