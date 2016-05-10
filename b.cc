#include "a.h"
#include "b.h"
#include <iostream>
using namespace std;

void B::f() {
    cout << __PRETTY_FUNCTION__ << endl;
    for (auto &a: vec)
        ++a.i;
}

void B::addA(A a) {
    vec.push_back(a);
}

void B::display() {
    for (const auto &a: vec)
        cout << a.get() << " ";
    cout << endl;
}


