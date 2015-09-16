#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s = "abcd";
    if (s.find('@'))
        cout << "Found" << endl;
    else
        cout << "Not found" << endl;

    cout << "string::npos: " << string::npos << endl;

    if (string::npos == -1)
        cout << "true" << endl;
    return 0;
}
