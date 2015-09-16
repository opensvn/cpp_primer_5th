#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
    istream_iterator<int> in_iter(cin), eof;
    ostream_iterator<int> out_iter(cout, " ");

    vector<int> ivec(in_iter, eof);

    sort(ivec.begin(), ivec.end());

    copy(ivec.cbegin(), ivec.cend(), out_iter);
    cout << endl;

    return 0;
}
