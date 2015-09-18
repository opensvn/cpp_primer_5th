#include <iostream>
using namespace std;

class Foo
{
public:
    Foo sorted(int avoidLoop) const &;
    Foo sorted() const &;
    Foo sorted() &&;
};

Foo Foo::sorted(int avoidLoop) const &
{
    if (avoidLoop > 10)
    {
        return *this;
    }
    cout << "call " << avoidLoop << endl;
    Foo ret(*this);
    return ret.sorted(avoidLoop + 1);
}

Foo Foo::sorted() const &
{
    return Foo(*this).sorted();
}

Foo Foo::sorted() &&
{
    return *this;
}

int main()
{
    Foo foo;
    foo.sorted(0);
    foo.sorted();
}