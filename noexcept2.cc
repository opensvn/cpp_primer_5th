#include <iostream>
using namespace std;

struct A {
    ~A() { throw 1; }
};

struct B {
    ~B() noexcept(false) { throw 2; }
};

struct C {
    B b;
};

int funA() { A a; }
int funB() { B b; }
int funC() { C c; }

int main() {
    try {
        funB();
    } catch (...) {
        cout << "caught funB." << endl;
    }

    try {
        funC();
    } catch (...) {
        cout << "caught funC." << endl;
    }

    try {
        funA();
    } catch (...) {
        cout << "caught funA." << endl;
    }
}