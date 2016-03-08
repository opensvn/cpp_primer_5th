#include <iostream>
#include <string>
#include <vector>
#include "compare.h"

using namespace std;

int main()
{
    cout << compare(1, -1) << endl;
    cout << compare(string("Hello"), string("world")) << endl;
    cout << compare("Hello", "me") << endl;
    // cout << compare(Sales_Data(), Sales_Data()) << endl;
    //
    vector<int> ivec = {0, 1, 2, 3, 4};
    auto i = find(ivec.begin(), ivec.end(), 2);
    cout << *i << endl;

    vector<string> svec = {"hello", "world", "my"};
    auto s = find(svec.begin(), svec.end(), "me");
    if (s == svec.end())
    {
        cout << "not found" << endl;
    }

    print(cout, "hello") << endl;
    print(cout, "me") << endl;
    // print(cout, ivec);

    for (auto p = first("hello"); p != last("hello"); ++p)
    {
        cout << *p;
    }
    cout << endl;

    char a[5] = "hell";
    first(a);
    last(a);

    return 0;
}