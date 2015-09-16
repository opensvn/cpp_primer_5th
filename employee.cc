#include <iostream>
#include <string>
using namespace std;

class Employee
{
public:
    Employee(std::string nm=string()): name(nm), e_id(sn++) {}
    ~Employee();
private:
    std::string name;
    size_t e_id;
    static size_t sn;
};

size_t Employee::sn = 0;

int main()
{
    return 0;
}
