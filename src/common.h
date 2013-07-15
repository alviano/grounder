/*
 * common.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <algorithm>
#include <cassert>
#include <list>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

template <class T>
string toString(const T& t) {
    stringstream ss;
    ss << t;
    return ss.str();
}

#endif /* COMMON_H_ */
