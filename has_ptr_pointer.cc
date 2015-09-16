#include <iostream>
#include <string>
#include <memory>
using namespace std;

class HasPtrPointer
{
public:
    HasPtrPointer(const std::string &s = std::string()):
        p(new std::string(s)), i(0), use(new std::size_t(1)) {}
    HasPtrPointer(const HasPtrPointer &rhs);
    HasPtrPointer &operator=(const HasPtrPointer&);
    ~HasPtrPointer();

    void set_str(const std::string &s) { *p = s; }
    void print_str() { std::cout << *p << std::endl; }
private:
    std::string *p;
    size_t i;
    std::size_t *use;
};

HasPtrPointer::HasPtrPointer(const HasPtrPointer &rhs):
    p(rhs.p), i(rhs.i), use(rhs.use)
{
    ++*use;
}

HasPtrPointer &HasPtrPointer::operator=(const HasPtrPointer &rhs)
{
    ++*rhs.use;
    if (--*use == 0)
    {
        delete p;
        delete use;
    }

    p = rhs.p;
    i = rhs.i;
    use = rhs.use;

    return *this;
}

HasPtrPointer::~HasPtrPointer()
{
    if (--*use == 0)
    {
        delete p;
        delete use;
    }
}

int main()
{
    HasPtrPointer o1("Hello");
    {
        HasPtrPointer o2 = o1;
        o2.print_str();
        o2.set_str("world");
        o2.print_str();
    }
    o1 = o1;
    o1.print_str();

    return 0;
}
