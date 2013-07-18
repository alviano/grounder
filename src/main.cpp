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
#include "Output.h"
#include "AspCore2.h"

int main() {
    Output outputBuilder;
    Program program(outputBuilder);
    AspCore2::getInstance().parse(program);
    //cout << program;
    program.instantiate();

    AspCore2::free();

    return 0;
}
