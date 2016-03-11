#include <type_traits>
#include <iostream>
using namespace std;

int main() {
    cout << "int&& rvalue_ref? " << is_rvalue_reference<int &&>::value << endl;
    cout << "int&& lvalue_ref? " << is_lvalue_reference<int &&>::value << endl;
    cout << "int&& ref? " << is_reference<int &&>::value << endl;
}