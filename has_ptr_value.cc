#include <iostream>
#include <string>
using namespace std;

class HasPtrValue
{
public:
    HasPtrValue(const std::string &s = std::string()):
        ps(new std::string(s)), i(0) {}
    HasPtrValue(const HasPtrValue&);
    HasPtrValue &operator=(const HasPtrValue&);
    ~HasPtrValue() { delete ps; }

    void set_str(const std::string &s) { *ps = s; }
    void print_str() { std::cout << *ps << std::endl; }
private:
    std::string *ps;
    size_t i;
};

HasPtrValue::HasPtrValue(const HasPtrValue &rhs):
    ps(new std::string(*rhs.ps)), i(rhs.i)
{
}

HasPtrValue &HasPtrValue::operator=(const HasPtrValue &rhs)
{
    if (this == &rhs)
        return *this;

    delete ps;
    ps = new string(*rhs.ps);
    i = rhs.i;

    return *this;
}

int main()
{
    HasPtrValue o1("Hello");
    {
        HasPtrValue o2 = o1;
        o2.print_str();
        o2.set_str("world");
        o2.print_str();
    }
    o1 = o1;
    o1.print_str();

    return 0;
}
