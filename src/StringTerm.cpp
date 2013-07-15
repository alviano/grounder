/*
 * StringTerm.cpp
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#include "StringTerm.h"

StringTerm::StringTerm(
        const string& name) {
    this->data = new Data();
    this->data->name = name;
}

StringTerm::~StringTerm() {
}

