_Pragma("once");
#define PRAGMA(x) _Pragma(#x)

int main()
{
    PRAGMA("once");
    return 0;
}