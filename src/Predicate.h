/*
 * Predicate.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef PREDICATE_H_
#define PREDICATE_H_

#include "common.h"
#include "Term.h"
#include "Indices.h"

class Atom;
class Component;
class DependenciesGraph;
class Rule;
class Program;

class Predicate {
    friend class Program;
    friend ostream& operator<<(ostream& out, const Predicate& predicate);
public:
    virtual ~Predicate();

    const Program& getProgram() const { return this->data->program; }
    const string& getName() const { return this->data->name; }

    int getArity() const { return this->arity; }
    void setArity(int value);

    bool operator==(const Predicate& right) const { return this->data == right.data && this->arity == right.arity; }
    bool operator!=(const Predicate& right) const { return !(*this == right); }

    void addHeadOccurrence(Rule& rule) { this->data->arity[this->arity].headOccurrences.push_back(&rule); }
    bool hasDefiningRules() const { return !this->data->arity[this->arity].headOccurrences.empty(); }

    void addToComponents(DependenciesGraph& graph);

    const Component& getComponent() const { assert(data != NULL); assert(data->arity[this->arity].component != NULL); return *data->arity[this->arity].component; }
    void setComponent(Component& value) { assert(data != NULL); data->arity[this->arity].component = &value; }

    void createIndex(const list<int>& positionsToIndex);
    void addDefiningRules(list<Rule*>& exitRules, list<Rule*>& recursiveRules);

    const Indices::Tuples* instantiate(const Atom& atom, const unordered_map<string, Term*>& variables);
    void addInstance(Terms* terms) { cerr << data->arity[this->arity].indices<<endl; data->arity[this->arity].indices.addInstance(terms); }
    bool isTrue(const Terms& terms) const { return data->arity[this->arity].indices.isTrue(terms); }

private:
    struct SingleData {
        SingleData() : component(NULL) {}

        list<Rule*> headOccurrences;
        Component* component;
        Indices indices;
    };
    struct Data {
        Data(Program& program_, const string& name_) : program(program_), name(name_) {}
        Program& program;
        string name;
        unordered_map<int, SingleData> arity;
    };

    Predicate(Program& program, const string& name);

    Data* data;
    int arity;
};

#endif /* PREDICATE_H_ */
