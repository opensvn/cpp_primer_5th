#include <cstdio>

#define PR(...) printf(__VA_ARGS__)
#define LOG(...) {\
    fprintf(stderr, "%s: Line %d:\t", __FILE__, __LINE__);\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n");\
}

int main()
{
    int x = 3;
    LOG("x = %d", x);
    return 0;
}