#include <iostream>
#include <vector>
#include <memory>
using namespace std;

vector<int> *new_vector()
{
    return new vector<int>;
}

shared_ptr<vector<int>> new_vector_shr()
{
    return make_shared<vector<int>>();
}

void set_value(vector<int> *p)
{
    *p = {0, 1, 2, 3, 4};
}

void set_value_shr(shared_ptr<vector<int>> shr_p)
{
    *shr_p = {5, 6, 7, 8, 9};
}

void print_value(vector<int> *p)
{
    for (auto i : *p)
    {
        cout << i << " ";
    }
    cout << endl;
}

void print_value_shr(shared_ptr<vector<int>> shr_p)
{
    for (auto i : *shr_p)
    {
        cout << i << " ";
    }
    cout << endl;
}
    
int main()
{
    vector<int> *p = new_vector();
    set_value(p);
    print_value(p);

    delete p;

    shared_ptr<vector<int>> shr_p = new_vector_shr();
    set_value_shr(shr_p);
    print_value_shr(shr_p);

    int *ip = new int(42);
    shared_ptr<int> shr_ip(ip);

//    delete ip;
//    cout << *shr_ip << endl;

    auto sp = make_shared<int>();
    if (sp == nullptr)
        cout << "sp nullptr" << endl;
    
    auto i_sp = sp.get();
    if (i_sp == nullptr)
        cout << "i_sp nullptr" << endl;
    //delete i_sp;
    
    return 0;
}
