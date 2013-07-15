/*
 * Component.h
 *
 *  Created on: Jul 4, 2013
 *      Author: malvi
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "common.h"
#include "Predicate.h"

class Component {
    friend ostream& operator<<(ostream& out, const Component& c);
public:
    Component();
    virtual ~Component();

    void addPredicate(const Predicate& predicate, bool selfLoop);
    unsigned size() const { return predicates.size(); }

    bool isRecursive() const { return recursive; }

    bool contains(const Predicate& predicate) const;
    const Predicate& front() const { return predicates.front(); }

    void removeAll(const Component& c);

    int getIndex() const { return index; }
    void setIndex(int value) { assert(index == -1); assert(value >= 0); index = value; }

    void instantiate();

private:
    list<Predicate> predicates;
    bool recursive;
    int index;
};

#endif /* COMPONENT_H_ */
