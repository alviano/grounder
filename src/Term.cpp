/*
 * Term.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "Term.h"

ostream& operator<<(ostream& out, const Term& term) {
    term.print(out);
    return out;
}

Term::Term() {
    // TODO Auto-generated constructor stub

}

Term::~Term() {
    // TODO Auto-generated destructor stub
}
