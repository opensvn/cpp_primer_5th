#include <iostream>
#include <vector>
using namespace std;

int main()
{
    const vector<int> ivec;
    cout << "nothing" << endl;
    for (auto i : ivec)
        cout << i << endl;

    //ivec.push_back(1);
    return 0;
}
