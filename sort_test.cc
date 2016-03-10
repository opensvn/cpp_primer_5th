#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

bool asc_order(int a, int b) {
    return a < b;
}

bool dsc_order(int a, int b) {
    return b < a;
}

int main() {
    int a[10];
    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        a[i] = rand() % 100;
        cout << a[i] << " ";
    }
    cout << endl;

    sort(a, a + 10, asc_order);

    for (int i = 0; i < 10; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;

    sort(a, a + 10, dsc_order);

    for (int i = 0; i < 10; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}