#ifndef CPP_PRIMER_B_H
#define CPP_PRIMER_B_H

#include <vector>

class A;

class B {
public:
    void f();
    void addA(A);
    void display();
private:
    std::vector<A> vec;
};

#endif
