#include <iostream>
#include <vector>
using namespace std;

struct X
{
    X() { cout << "X()" << endl; }
    X(const X&) { cout << "X(const X&)" << endl; }
    X &operator=(const X&) { cout << "X &operator=(const X&)" << endl; }
    ~X() { cout << "~X()" << endl; }
};

X f1(X x)
{
    return x;
}

X& f2(X& x)
{
    return x;
}

int main()
{
    cout << "x" << endl;
    X x;
    cout << "new y" << endl;
    X *y = new X();

    cout << "call f1" << endl;
    f1(x);
    cout << "call f2" << endl;
    f2(x);

    cout << "push_back" << endl;
    vector<X> v_x;
    v_x.push_back(x);

    cout << "delete y" << endl;
    delete y;

    return 0;
}
