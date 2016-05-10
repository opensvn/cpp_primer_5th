/// \file friend.cc
/// \brief a pitfall about friend usage.
///
/// A relies the definition of B, and B also relies the definition of A.
///
/// \author opensvn
/// \version 0.0.1
/// \date Tue 10 May 2016 03:44:20 PM CST

#include <vector>

using namespace std;

class A {
    friend void B::f();
};

class B {
public:
    void f();
private:
    vector<A> vec;
};

