#include <iostream>
using namespace std;

struct People {
    int hand;
    static People* all;
};

int main() {
    People p;
    cout << "sizeof(p.hand): " << sizeof(p.hand) << endl;
    cout << "sizeof(People::all): " << sizeof(People::all) << endl;
    cout << "sizeof(People::hand): " << sizeof(People::hand) << endl;
    cout << "sizeof(((People*)0)->hand): " << sizeof(((People*)0)->hand) << endl;
}