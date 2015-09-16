#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
    shared_ptr<string> p1;
    shared_ptr<string> p2(new string("Hello, world"));

    cout << p2 << endl;

    if (!p1 && p2)
        cout << *p2 << endl;

    shared_ptr<int> p5 = make_shared<int>();
    shared_ptr<int> p6 = make_shared<int>(0);
    if (p5)
        cout << *p5 << endl;
    if (p6)
        cout << *p6 << endl;

    auto p7 = make_shared<vector<string>>();
    ifstream in("shared_ptr.cc");
    string line;
    while (getline(in, line))
        p7->push_back(line);

    ostream_iterator<string> out(cout, "\n");
    copy(p7->begin(), p7->end(), out);

    in.close();

    return 0;
}
