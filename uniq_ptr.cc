#include <iostream>
#include <memory>
using namespace std;

int main()
{
    unique_ptr<int> u_ip(new int(42));
    unique_ptr<int> u_ip2 = u_ip;

    return 0;
}
