#include <iostream>
#include "template_func.h"
using namespace std;

int main()
{
    char a[4] = {0, 1, 2, 3};
    int b[4] = {5, 6, 7, 8};

    cout << foo(a, 4) << endl;
    cout << foo(b, 4) << endl;

    return 0;
}