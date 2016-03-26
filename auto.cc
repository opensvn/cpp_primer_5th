#include <iostream>
#include <typeinfo>

using namespace std;

int main()
{
    const int i = 42;
    auto j = i;
    const auto &k = i;
    auto *p = &i;
    const auto j2 = i, &k2 = i;

    cout << "j is " << typeid(j).name() << endl;
    cout << "k is " << typeid(k).name() << endl;
    cout << "p is " << typeid(p).name() << endl;
    cout << "j2 is " << typeid(j2).name() << endl;
    cout << "k2 is " << typeid(k2).name() << endl;

    return 0;
}
