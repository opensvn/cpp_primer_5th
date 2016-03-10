#include <iostream>
using namespace std;

typedef char CType;

template <typename CType>
CType f5(CType a)
{
    cout << a << endl;
    a = 0.0;
    return a;
}

int main()
{
    cout << f5(3.2) << endl;
    return 0;
}
