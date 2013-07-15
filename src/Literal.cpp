/*
 * Literal.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "Literal.h"

ostream& operator<<(ostream& out, const Literal& literal) {
    literal.print(out);
    return out;
}

Literal::Literal() {

}

Literal::~Literal() {
}
