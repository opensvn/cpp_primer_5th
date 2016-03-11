#include <iostream>
#include <utility>
using namespace std;

struct Maythrow {
    Maythrow() {}
    Maythrow(const Maythrow&) {
        cout << "Maythrow copy constructor." << endl;
    }
    Maythrow(Maythrow&&) {
        cout << "Maythrow move constructor." << endl;
    }
};

struct Nothrow {
    Nothrow() {}
    Nothrow(Nothrow&&) noexcept {
        cout << "Nothrow move constructor." << endl;
    }
    Nothrow(const Nothrow&) {
        cout << "Nothrow copy constructor." << endl;
    }
};

int main() {
    Maythrow m;
    Nothrow n;

    Maythrow mt = move_if_noexcept(m);
    Nothrow nt = move_if_noexcept(n);

    return 0;
}