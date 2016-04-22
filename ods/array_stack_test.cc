#include "array_stack.h"
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ArrayStack<char> asc(0);
    asc.add(0, 'b');
    asc.add(1, 'r');
    asc.add(2, 'e');
    asc.add(3, 'd');
    asc.print();

    asc.add(2, 'e');
    asc.add(5, 'r');
    asc.print();

    asc.add(5, 'e');
    asc.print();

    asc.remove(4);
    asc.print();

    asc.remove(4);
    asc.print();

    asc.remove(4);
    asc.print();

    asc.set(2, 'i');
    asc.print();

    return 0;
}
