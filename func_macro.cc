#include <iostream>
#include <string>
using namespace std;

struct TestStruct
{
    TestStruct(): name(__func__) {}
    const char *name;
};

const char *hello()
{
    return __func__;
}

const char *world()
{
    return __func__;
}

int main()
{
    cout << hello() << ", " << world() << endl;

    TestStruct ts;
    cout << ts.name << endl;
}