/*
 * Constraint.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef CONSTRAINT_H_
#define CONSTRAINT_H_

#include "Rule.h"
#include "Body.h"

class Constraint : public Rule {
public:
    Constraint();
    virtual ~Constraint();

private:
    Body body;
};

#endif /* CONSTRAINT_H_ */
