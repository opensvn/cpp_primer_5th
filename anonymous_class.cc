template <typename T> class X {};
template <typename T> void TempFun(T t) {};
struct A {} a;
struct {int i;} b;
typedef struct {int i;} B;

void Fun() {
    struct C {} c;

    X<A> x1;
    X<B> x2;
    X<C> x3;

    TempFun(a);
    TempFun(b);
    TempFun(c);
}

int main()
{
    Fun();
}