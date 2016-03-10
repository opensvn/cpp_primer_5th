#include <iostream>
using namespace std;

class Base
{
public:
    virtual void memfcn(Base &b) { b = *this; }
protected:
    int prot_mem;     // protected member
};

class Sneaky : public Base
{
public:
    Sneaky(int i = 0) : j(i) {}
    void memfcn(Base &b) { b = *this; }
    int get_j() { return j; }
private:
    friend void clobber(Sneaky &); // can access Sneaky::prot_mem
    friend void clobber(Base &);   // can't access Base::prot_mem
    int j;                          // j is private by default
};

int main()
{
    Base a, b;
    Sneaky c, d(1);

    a.memfcn(b);
    d.memfcn(c);

    cout << c.get_j() << endl;
    cout << d.get_j() << endl;

    return 0;
}