#include <iostream>
using namespace std;

template <typename T>
void print_array(T a[], int len)
{
    for (int i = 0; i < len; ++i)
    {
        if (sizeof(T) == sizeof(char))
            cout << int(a[i]) << " ";
        else
            cout << a[i] << " ";
    }
    cout << endl;
}

int main()
{
    int a[] = {0, 1, 2, 3, 4};
    char b[] = {5, 6, 7, 8, 9};
    long c[] = {10, 11, 12, 13};
    long long d[] = {14, 15, 16};
    double e[] = {3.4, 4.5, 7,8};
    short f[] = {5, 9, 7, 6, 4};

    print_array(a, 5);
    print_array(b, 5);
    print_array(c, 4);
    print_array(d, 3);
    print_array(e, 3);
    print_array(f, 5);

    return 0;
}
