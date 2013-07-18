/*
 * Output.h
 *
 *  Created on: Jul 18, 2013
 *      Author: malvi
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "common.h"

class Atom;
class NormalRule;

class Output {
public:
    Output(ostream& out = cout);
    virtual ~Output();

    virtual void falseAtom(const string& predicate);

    virtual void positiveLiteral(const string& atom);
    virtual void negativeLiteral(const string& atom);

    virtual void normalRuleStart(const string& head);
    virtual void normalRuleEnd();

    virtual void programStart();
    virtual void programEnd();

protected:
    ostream& out;
    vector<int> positiveLiterals;
    vector<int> negativeLiterals;

    virtual bool censored(const string& name) const { assert(name.length() > 0); return name[0] == '#'; }

private:
    Output(const Output&) : out(cout) { assert(0); }

    unordered_map<string, int> atomId;

    int getId(const string& atom);
};

#endif /* OUTPUT_H_ */
