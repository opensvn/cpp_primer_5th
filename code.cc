#include <iostream>
#include <cstring>
using namespace std;

class Code
{
private:
    long long m_nData;

public:
    Code(long long n = 0);
    operator long long();
};

Code::Code(long long n)
{
    m_nData = n;
}

Code::operator long long()
{
    return m_nData;
}

int main()
{
    Code code;
    cout << "sizeof(Code): " << sizeof(code) << " code = " << code << endl;

    Code code2(15);
    long long i = code2;
    // memcpy(&i, &code2, sizeof(Code));

    if (code2 > 14)
        cout << "Implict convert to long long and make comparison" << endl;

    cout << i << endl;
}