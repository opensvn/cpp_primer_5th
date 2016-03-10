#include <iostream>
using namespace std;

class A
{
public:
    A(char *p = NULL);
    ~A();
private:
    char *data;
};

A::A(char *p)
{
    if (p == NULL)
    {
        data = new char[8];
    }
    else
    {
        data = p;
    }
}

A::~A()
{
    cout << "destructor" << endl;
    if (data != NULL)
    {
        delete [] data;
    }
}

int main()
{
    A *p1 = new A();
    delete p1;

    A *p2 = new A();
    delete (void *)p2;

    return 0;
}