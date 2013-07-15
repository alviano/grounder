/*
 * Indices.cpp
 *
 *  Created on: Jul 5, 2013
 *      Author: malvi
 */

#include "Indices.h"

#include "Atom.h"

ostream& operator<<(ostream& out, const Indices& indices) {
    out << "{structure: " << indices.structure << ", tuples: [";
    for(unordered_map<string, pair<Terms*, bool> >::const_iterator it = indices.data.begin(); it != indices.data.end(); ++it)
        out << "(" << *it->second.first << "), ";
    return out << "], indexed: " << indices.tuples << "]";
}

ostream& operator<<(ostream& out, const Indices::Structure& structure) {
    out << "{";
    if(structure.isTerminal())
        out << "*, ";
    for(unordered_map<int, Indices::Structure*>::const_iterator it = structure.subIndices.begin(); it != structure.subIndices.end(); ++it)
        out << it->first << ": " << *it->second << ", ";
    return out << "}";
}

ostream& operator<<(ostream& out, const Indices::Tuples& tuples) {
    out << "{tuples: [";
    for(unordered_map<string, Terms*>::const_iterator it = tuples.data.begin(); it != tuples.data.end(); ++it)
        out << "(" << *it->second << "), ";
    out << "], byIndex: {";
    for(unordered_map<string, Indices::Tuples*>::const_iterator it = tuples.byIndex.begin(); it != tuples.byIndex.end(); ++it)
        out << it->first << ": " << *it->second << ", ";
    return out << "}}";
}

Indices::Structure::Structure()
: terminal(false) {
}

Indices::Structure::~Structure() {
    for(unordered_map<int, Indices::Structure*>::iterator it = subIndices.begin(); it != subIndices.end(); ++it)
        delete it->second;
}

void
Indices::Structure::add(
        list<int>::const_iterator from,
        list<int>::const_iterator to) {
    if(from == to)
            terminal = true;
        else {
            unordered_map<int, Indices::Structure*>::iterator it = subIndices.find(*from);
            if(it == subIndices.end())
                it = subIndices.insert(unordered_map<int, Indices::Structure*>::value_type(*from, new Indices::Structure())).first;
            it->second->add(++from, to);
        }
}

Indices::Tuples::Tuples() {

}

Indices::Tuples::~Tuples() {

}

Indices::Tuples*
Indices::Tuples::find(
        const string& key) {
    unordered_map<string, Tuples*>::iterator it = byIndex.find(key);
    if(it != byIndex.end())
        return it->second;
    return NULL;
}

void
Indices::Tuples::addInstance(
        const string& key,
        Terms* value,
        const Structure& structure) {
    assert(value != NULL);

    if(structure.isTerminal()) {
        const pair<unordered_map<string, Terms*>::iterator, bool>& res = data.insert(unordered_map<string, Terms*>::value_type(key, value));
        assert(res.second);
        cout << "HERE" << endl;
    }

    Terms& terms = *value;
    for(unordered_map<int, Structure*>::const_iterator it = structure.begin(); it != structure.end(); ++it) {
        const string& subkey = toString(terms[it->first]);
        pair<unordered_map<string, Tuples*>::iterator, bool> res = byIndex.insert(unordered_map<string, Tuples*>::value_type(subkey, NULL));
        if(res.second)
            res.first->second = new Tuples();
        cout << "AAA: " << subkey << *res.first->second<< endl;
        res.first->second->addInstance(key, value, *it->second);
    }

}

Indices::Indices() {
}

Indices::~Indices() {
    for(unordered_map<string, pair<Terms*, bool> >::iterator it = data.begin(); it != data.end(); ++it)
        delete it->second.first;
}

void
Indices::create(
        const list<int>& positions) {
    structure.add(positions.begin(), positions.end());
}

const Indices::Tuples*
Indices::instantiate(
        const Atom& atom,
        const unordered_map<string, Term*>& variables) {
    Tuples* tuples = &this->tuples;
    for(list<int>::const_iterator it = atom.getBoundArguments().begin(); it != atom.getBoundArguments().end(); ++it) {
        Term* substitution = atom.getTerms()[*it].replace(variables);
        const string& key = toString(*substitution);
        delete substitution;

        tuples = tuples->find(key);
        if(tuples == NULL)
            return NULL;
    }

    return tuples;
}

void
Indices::addInstance(
        Terms* terms) {
    assert(terms != NULL);
    const string& key = toString(*terms);
    pair<unordered_map<string, pair<Terms*, bool> >::iterator, bool > res = data.insert(unordered_map<string, pair<Terms*, bool> >::value_type(key, pair<Terms*, bool>(NULL, true)));
    if(res.second) {
        res.first->second.first = terms;
        tuples.addInstance(key, res.first->second.first, structure);
    }
    else
        delete terms;
    cout << "Indices::addInstance() " << *this << endl;
}
