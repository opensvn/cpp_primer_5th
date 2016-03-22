#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main()
{
    vector<int> primes;
    primes.push_back(2);

    typedef vector<int>::size_type vsize_t;
    for (int i = 3; i < INT_MAX; i += 2)
    {
        bool isPrime = true;
        for (vsize_t j = 0; j != primes.size(); ++j)
        {
            if (i % primes[j] == 0)
            {
                isPrime = false;
                break;
            }
        }
        if (isPrime)
            primes.push_back(i);
    }

    cout << primes.size() << endl;

    return 0;
}
