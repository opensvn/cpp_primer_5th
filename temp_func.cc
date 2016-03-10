#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <typename T>
string foo(T *a, int len)
{
    stringstream ss;
    for (int i = 0; i < len; ++i)
    {
        ss << int(a[i]) << " ";
    }
    return ss.str();
}

int main()
{
    char a[4] = {0, 1, 2, 3};
    int b[4] = {5, 6, 7, 8};

    cout << foo(a, 4) << endl;
    cout << foo(b, 4) << endl;

    return 0;
}
