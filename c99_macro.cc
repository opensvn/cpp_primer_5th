#include <iostream>
using namespace std;

int main()
{
    // cout << "Standard Clib: " << __STDC__HOSTED__ << endl;
    cout << "Standard C: " << __STDC__ << endl;
    // cout << "C standard version: " << __STDC_VERSION__ << endl;
    cout << "ISO/IEC: " << __STDC_ISO_10646__ << endl;

    return 0;
}
