/// \file friend.cc
/// \brief a simple example about friend usage.
///
/// A relies the definition of B, and B also relies the definition of A.
///
/// \author opensvn
/// \version 0.0.1
/// \date Tue 10 May 2016 03:44:20 PM CST

#include <iostream>
#include <vector>

using namespace std;

class A;

class B {
public:
    void f();
    void addA(A);
    void display();
private:
    vector<A> vec;
};

class A {
    friend void B::f();
public:
    int get() const { return i; }
private:
    int i = 0;
};

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

int main() {
    B b;

    for (auto i = 0; i != 5; ++i) {
        b.addA(A());
        b.f();
        b.display();
    }

    return 0;
}

