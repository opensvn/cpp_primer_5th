#include <iostream>
#include <vector>
using namespace std;

template <typename T>
ostream &print_container(ostream &os, const T &c)
{
    for (typename T::const_iterator i = c.begin(); i != c.end(); ++i)
    {
        os << *i << " ";
    }
    return os;
}

int main()
{
    vector<int> ivec{0, 1, 2, 3, 4};
    print_container(cout, ivec) << endl;

    vector<string> svec{"hello", "world", "my", "name", "is", "xiaoyu"};
    print_container(cout, svec) << endl;

    return 0;
}
