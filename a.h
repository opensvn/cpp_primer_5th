#ifndef CPP_PRIMER_A_H
#define CPP_PRIMER_A_H

#include "b.h"

class A {
    friend void B::f();
public:
    int get() const { return i; }
private:
    int i = 0;
};

#endif
