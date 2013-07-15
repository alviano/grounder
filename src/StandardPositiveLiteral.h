/*
 * StandardPositiveLiteral.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef STANDARDPOSITIVELITERAL_H_
#define STANDARDPOSITIVELITERAL_H_

#include "common.h"

#include "StandardLiteral.h"

class StandardPositiveLiteral : public StandardLiteral {
public:
    StandardPositiveLiteral(const Atom& atom);
    virtual ~StandardPositiveLiteral();

    virtual Clonable* clone() const { return new StandardPositiveLiteral(*this); }

    virtual int getPriority(int componentIndex) const;
};

#endif /* STANDARDPOSITIVELITERAL_H_ */
