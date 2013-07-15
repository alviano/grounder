/*
 * Clonable.h
 *
 *  Created on: Jul 2, 2013
 *      Author: malvi
 */

#ifndef CLONABLE_H_
#define CLONABLE_H_

#include "common.h"

class Clonable {
public:
    Clonable();
    virtual ~Clonable();

    virtual Clonable* clone() const = 0;
};

template<class C>
class ClonableVector : private vector<C*> {
    template<class CC>
    friend ostream& operator<<(ostream& out, const ClonableVector<CC>& vec);
public:
    using vector<C*>::empty;
    using vector<C*>::size;

    ClonableVector() {
    }
    ClonableVector(const ClonableVector<C>& init) {
        for(unsigned i = 0; i < init.size(); ++i)
            push_back(init[i]);
    }

    virtual ~ClonableVector() {
        for(typename vector<C*>::iterator it = vector<C*>::begin(); it < vector<C*>::end(); ++it)
            delete *it;
    }

    C& operator[](unsigned index) {
        return *vector<C*>::operator[](index);
    }
    const C& operator[](unsigned index) const {
        return *vector<C*>::operator[](index);
    }

    const C& front() const {
        return *vector<C*>::front();
    }
    void push_front(const C& elem) {
        vector<C*>::push_front(static_cast<C*>(elem.clone()));
    }

    const C& back() const {
        return *vector<C*>::back();
    }
    void push_back(const C& elem) {
        vector<C*>::push_back(static_cast<C*>(elem.clone()));
    }
    void push_back(C* elem) {
        vector<C*>::push_back(elem);
    }

    void swap(unsigned i, unsigned j) {
        C* tmp = vector<C*>::operator [](i);
        vector<C*>::operator [](i) = vector<C*>::operator [](j);
        vector<C*>::operator [](j) = tmp;
    }
};

template<class CC>
ostream& operator<<(ostream& out, const ClonableVector<CC>& vec) {
    if(!vec.empty()) {
        out << vec[0];
        for(unsigned i = 1; i < vec.size(); ++i)
            out << ", " << vec[i];
    }
    return out;
}


#endif /* CLONABLE_H_ */
