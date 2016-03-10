#include <sstream>
using namespace std;

template <typename T>
string foo(T *a, int len)
{
    stringstream ss;
    for (int i = 0; i < len; ++i)
    {
        ss << int(a[i]) << " ";
    }
    return ss.str();
}