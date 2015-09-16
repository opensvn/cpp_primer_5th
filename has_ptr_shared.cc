#include <iostream>
#include <string>
#include <memory>
using namespace std;

class HasPtrShared
{
public:
    HasPtrShared(const std::string &s = std::string()):
        p(new std::string(s)), i(0) {}
    HasPtrShared(const HasPtrShared&);
    HasPtrShared &operator=(const HasPtrShared&);
    ~HasPtrShared() {}

    void set_str(const std::string &s) { *p = s; }
    void print_str() { std::cout << *p << std::endl; }
private:
    shared_ptr<std::string> p;
    size_t i;
};

HasPtrShared::HasPtrShared(const HasPtrShared &rhs):
    p(rhs.p), i(rhs.i)
{
}

HasPtrShared &HasPtrShared::operator=(const HasPtrShared &rhs)
{
    if (this == &rhs)
        return *this;

    p = rhs.p;
    i = rhs.i;

    return *this;
}

int main()
{
    HasPtrShared o1("Hello");
    {
        HasPtrShared o2 = o1;
        o2.print_str();
        o2.set_str("world");
        o2.print_str();
    }
    o1 = o1;
    o1.print_str();

    return 0;
}
