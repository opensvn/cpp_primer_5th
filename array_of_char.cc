#include <iostream>
#include <string>
#include <memory>
#include <cstring>
using namespace std;

int main()
{
    const char *p1 = "Hello, ";
    const char *p2 = "world!\n";

    size_t len1 = strlen(p1);
    size_t len2 = strlen(p2);
    size_t new_len = len1 + len2 + 1;

    unique_ptr<char[]> u_p1(new char[new_len]);

    size_t i = 0;
    while (p1[i] != 0)
    {
        u_p1[i] = p1[i];
        ++i;
    }
    
    size_t j = 0;
    while (p2[j] != 0)
    {
        u_p1[i] = p2[j];
        ++i;
        ++j;
    }
    u_p1[i] = 0;

    for (size_t i = 0; u_p1[i] != 0; ++i)
        cout << u_p1[i];
    cout << endl;

    return 0;
}
