#include <cassert>
#include <cstring>
using namespace std;

template <typename T, typename U>
void bit_copy(T& a, U& b) {
    assert(sizeof(a) == sizeof(b));
    memcpy(&a, &b, sizeof(b));
}

#define assert_static(e)\
    do {\
        enum { assert_static__ = 1 / (e) };\
    } while (0)

template <typename T, typename U>
void bit_copy2(T& a, U& b) {
    assert_static(sizeof(a) == sizeof(b));
    memcpy(&a, &b, sizeof(b));
}

template <typename T, typename U>
void bit_copy3(T& a, U& b) {
    static_assert(sizeof(a) == sizeof(b), "the parameters must have same size.");
    memcpy(&a, &b, sizeof(b));
}

static_assert(sizeof(int) == 8, "This 64-bit machine should follow this!");

int main()
{
    int a = 0x2468;
    double b;
    bit_copy(b, a);
    // bit_copy2(b, a);
    // bit_copy3(b, a);
}