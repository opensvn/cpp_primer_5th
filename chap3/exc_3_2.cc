#include <iostream>
#include <string>
using namespace std;

int main()
{
    string line;
    while (getline(cin, line))
    {
        cout << line << endl;
    }
    cin.clear();

    string word;
    while (cin >> word)
        cout << word << endl;

    return 0;
}
