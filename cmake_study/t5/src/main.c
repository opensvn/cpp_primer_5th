#include <stdio.h>

int main() {
#ifdef DEBUG
    printf("Debug\n");
#else
    printf("Release\n");
#endif
    return 0;
}
