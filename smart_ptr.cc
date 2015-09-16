#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>
using namespace std;

int main()
{
    shared_ptr<string> p1;
    shared_ptr<list<int>> p2;

    p1 = make_shared<string>("Hello, world!");
    cout << *p1 << endl;

    auto q(p1);

    if (p1.unique())
    {
        cout << "unique" << endl;
    }
    else
    {
        cout << p1.use_count() << endl;
    }

    return 0;
}
