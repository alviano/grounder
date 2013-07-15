/*
 * Indices.h
 *
 *  Created on: Jul 5, 2013
 *      Author: malvi
 */

#ifndef INDICES_H_
#define INDICES_H_

#include "common.h"
#include "Term.h"

class Atom;

class Indices {
    friend ostream& operator<<(ostream& out, const Indices& indices);
public:
    class Structure {
        friend ostream& operator<<(ostream& out, const Structure& structure);
    public:
        Structure();
        virtual ~Structure();

        bool isTerminal() const { return terminal; }
        void add(list<int>::const_iterator from, list<int>::const_iterator to);

        unordered_map<int, Structure*>::const_iterator begin() const { return subIndices.begin(); }
        unordered_map<int, Structure*>::const_iterator end() const { return subIndices.end(); }

    private:
        bool terminal;
        unordered_map<int, Structure*> subIndices;
    };

    class Tuples {
        friend ostream& operator<<(ostream& out, const Tuples& tuples);
    public:
        typedef unordered_map<string, Terms*>::const_iterator const_iterator;

        Tuples();
        virtual ~Tuples();

        Tuples* find(const string& key);
        void addInstance(const string& key, Terms* value, const Structure& structure);

        const_iterator begin() const { return data.begin(); }
        const_iterator end() const { return data.end(); }

    private:
        unordered_map<string, Terms*> data;
        unordered_map<string, Tuples*> byIndex;
    };

    Indices();
    virtual ~Indices();

    void create(const list<int>& positions);
    const Tuples* instantiate(const Atom& atom, const unordered_map<string, Term*>& variables);
    void addInstance(Terms* terms);

private:
    Structure structure;
    Tuples tuples;
    unordered_map<string, pair<Terms*, bool> > data;
};

#endif /* INDICES_H_ */
