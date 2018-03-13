/*
 * MarkableReference.h
 *
 *  Created on: Mar 12, 2018
 *      Author: david
 */

#ifndef MARKABLEREFERENCE_H_
#define MARKABLEREFERENCE_H_

#include <atomic>
using namespace std;

/*Be VERY careful while using this class -
 * 1) We assume that the pointer MSB isn't important (that's usually the case)
 * 2) No destructor is called on value this reference points to. should call delete on getRef
 */
template<class T>
class MarkableReference
{
private:
    atomic<uintptr_t> val;
    static const uintptr_t mask = 1;
public:
    MarkableReference(T* ref = NULL, bool mark = false)
    {
        val = ((uintptr_t)ref & ~mask) | (mark ? 1 : 0);
    }
    T* getRef()
    {
        return (T*)(val & ~mask);
    }
    bool getMark()
    {
        return (val & mask);
    }
    void setMark(bool mark) {
    	val = ((uintptr_t)val & ~mask) | (mark ? 1 : 0);
    }
};

#endif /* MARKABLEREFERENCE_H_ */
