#include <iostream>
using namespace std;

void Throw() { throw 1; }
void NoBlockThrow() { Throw(); }
void BlockThrow() noexcept { Throw(); }

int main() {
    try {
        Throw();
    } catch (...) {
        cout << "Found throw." << endl;
    }

    try {
        NoBlockThrow();
    } catch (...) {
        cout << "Throw is not blocked." << endl;
    }

    try {
        BlockThrow();
    } catch (...) {
        cout << "Found blocked throw." << endl;
    }
}