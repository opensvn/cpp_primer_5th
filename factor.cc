#include <iostream>
using namespace std;

int gcd(int m, int n)
{
    if (n == 0)
        return m;
    else
        gcd(n, m % n);
}

void factor(int &m, int &n)
{
    int g = gcd(m, n);
    m /= g;
    n /= g;
}

int main()
{
    double d;
    cin >> d;

    int i = d * 1000;
    int j = 1000;

    factor(i, j);

    cout << i << "/" << j << endl;

    return 0;
}
