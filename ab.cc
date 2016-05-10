#include "b.h"
#include "a.h"

int main() {
    B b;

    for (auto i = 0; i != 5; ++i) {
        b.addA(A());
        b.f();
        b.display();
    }

    return 0;
}
