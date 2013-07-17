/*
 * main.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */


#include "Predicate.h"
#include "Program.h"
#include "Term.h"
#include "StringTerm.h"
#include "Atom.h"
#include "StandardPositiveLiteral.h"
#include "StandardNegativeLiteral.h"
#include "Body.h"
#include "NormalRule.h"
#include "Variable.h"
#include "Program.h"
#include "aspcore2.h"

int main() {
    Program program;

    Predicate a = program.createPredicate("a");
    Predicate b = program.createPredicate("b");
    Predicate a2 = program.createPredicate("a");
    assert(a == a2);
    assert(b != a);

    StringTerm term1 = program.createStringTerm("1");
    Variable var1("X");
/*
    Terms terms;
    terms.push_back(term1);
    terms.push_back(var1);

    Atom atom(a, terms);
    StandardPositiveLiteral pos_literal(atom);
    StandardNegativeLiteral neg_literal(atom);
    Body body;
    body.push_back(neg_literal);
    body.push_back(pos_literal);
    cout << body << endl;
    program.addRule(new NormalRule(atom, body));
*/

    Terms terms2;
    terms2.push_back(term1);
    program.addRule(new NormalRule(Atom(a, terms2), Body()));

    Terms terms3;
    terms3.push_back(var1);
    Body body2;
    body2.push_back(StandardPositiveLiteral(Atom(a, terms3)));
    program.addRule(new NormalRule(Atom(b, terms3), body2));

    /*
*/
    cout << program;

    program.computeComponents();
    program.printComponents(cout);
    cout << endl;

    program.sortRules();
    cout << program;

    program.indexPredicates();
    program.instantiate();

    cout << "end" << endl;

    Program p;
    AspCore2& parser = *AspCore2::getInstance();
    parser.parse(p);
    cout << p;

    AspCore2::free();

    return 0;
}
