#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<int, int> poker;

    poker.insert(make_pair(1, 3));
    poker.insert(make_pair(4, 2));
    poker.insert(make_pair(3, 7));
    poker.insert(make_pair(2, 9));
    poker.insert(make_pair(0, 2));

    for (map<int, int>::iterator it = poker.begin();
            it != poker.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }

    return 0;
}
