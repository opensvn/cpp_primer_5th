#include "array.h"
#include <iostream>
#include <algorithm>
using namespace std;

void print(const int& elem) {
    cout << elem << " ";
}

void print(const string& elem) {
    cout << elem << " ";
}

int main() {
    Array<int> a(5);
    for (int i = 0; i < 5; ++i)
        a[i] = i;

    void (*g)(const int&) = print;

    for_each(&a[0], &a[5], g);
    cout << endl;

    Array<string> as(5);
    as[0] = "hello";
    as[1] = "iostream";
    for (int i = 0; i < 3; ++i)
        as[i + 2] = "Array";

    void (*f)(const string&) = print;

    for_each(&as[0], &as[5], f);
    cout << endl;

    Array<int> b;
    b = a;
    for_each(&b[0], &b[5], g);
    cout << endl;

    return 0;
}

