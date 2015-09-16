#include <iostream>
#include <vector>
using namespace std;

void print(const vector<int> &ivec, int index)
{
    if (index == ivec.size())
        return;
    print(ivec, index + 1);
#ifndef NDEBUG
    cout << __FILE__ << ": in function "
        << __func__ << " at line " << __LINE__ 
        << endl << "Compiled on " << __DATE__
        << " at " << __TIME__ << endl;
#endif
    cout << ivec[index] << " ";
}

void print(const vector<int> &ivec)
{
    for (auto i: ivec)
        cout << ivec[i] << " ";
    cout << endl;
}

int main()
{
    vector<int> ivec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print(ivec, 0);
    cout << endl;

    return 0;
}
