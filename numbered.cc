#include <iostream>
using namespace std;

class Numbered
{
public:
    Numbered(): mysn(sn++) {}
    Numbered(const Numbered &rhs): mysn(sn++) {}

public:
    int mysn;
    static int sn;
};

int Numbered::sn = 0;

void f(Numbered &s) { cout << s.mysn << endl; }

int main()
{
    Numbered a, b = a, c = b;
//    Numbered a, b, c;
    f(a);
    f(b);
    f(c);

    return 0;
}
