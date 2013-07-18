/*
 * Output.cpp
 *
 *  Created on: Jul 18, 2013
 *      Author: malvi
 */

#include "Output.h"

#include "Atom.h"
#include "NormalRule.h"

Output::Output(ostream& out_) : out(out_) {
}

Output::~Output() {
}

void
Output::falseAtom(
        const string& predicate) {
    getId(predicate);
}

void
Output::normalRuleStart(
        const string& head) {
    assert(positiveLiterals.empty());
    assert(negativeLiterals.empty());
    out << "1 " << getId(head);
}

void
Output::positiveLiteral(
        const string& atom) {
    positiveLiterals.push_back(getId(atom));
}

void
Output::negativeLiteral(
        const string& atom) {
    negativeLiterals.push_back(getId(atom));
}

void
Output::normalRuleEnd() {
    out << " " << (positiveLiterals.size() + negativeLiterals.size()) << " " << negativeLiterals.size();
    for(unsigned i = 0; i < negativeLiterals.size(); ++i)
        out << " " << negativeLiterals[i];
    for(unsigned i = 0; i < positiveLiterals.size(); ++i)
        out << " " << positiveLiterals[i];
    out << endl;
    positiveLiterals.clear();
    negativeLiterals.clear();
}

int
Output::getId(
        const string& atom) {
    const pair<unordered_map<string, int>::iterator, bool>& res = atomId.insert(unordered_map<string, int>::value_type(atom, atomId.size()+1));
    return res.first->second;
}

void
Output::programStart() {
}

void
Output::programEnd() {
    out << "0\n";
    for(unordered_map<string, int>::const_iterator it = atomId.begin(); it != atomId.end(); ++it)
        if(!censored(it->first))
            out << it->second << " " << it->first << endl;
    out << "0\nB+\n0\nB-\n1\n0\n1" << endl;
}
