#include "drive_poker.h"

int main()
{
    AFPoker mPoker;

    U8 p[13] = {1, 5, 9, 8, 19, 21, 23, 27, 32, 36, 39, 46, 44};
    mPoker.Check_Array(p, 14);
    return 0;
}
// 2 4 5 5 6