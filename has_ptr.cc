#include <iostream>
#include <string>
using namespace std;

class HasPtr
{
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr&);
    HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i)
    { p.ps = nullptr; }
    // HasPtr &operator=(const HasPtr&);
    HasPtr &operator=(HasPtr rhs)
    { swap(*this, rhs); return *this; }
    ~HasPtr() { delete ps; }
private:
    std::string *ps;
    size_t i;
};

HasPtr::HasPtr(const HasPtr &rhs):
    ps(new std::string(*rhs.ps)), i(rhs.i)
{
}

// HasPtr &HasPtr::operator=(const HasPtr &rhs)
// {
//     if (this == &rhs)
//         return *this;

//     delete ps;
//     ps = new string(*rhs.ps);
//     i = rhs.i;

//     return *this;
// }

int main()
{
    return 0;
}
