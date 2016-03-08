#include <iostream>
#include <string>

#include "quote.h"
#include "bulk_quote.h"
#include "lmt_quote.h"
using namespace std;

int main()
{
    Bulk_quote b("b", 3, 5, 4);
    Quote q("q", 4);
    Lmt_quote l("l", 3, 2, 1);

    // cout << b.isbn() << endl;
    // cout << q.isbn() << endl;

    cout << b << endl;
    cout << q << endl;
    cout << l << endl;

    cout << "sizeof(Bulk_quote): " << sizeof(Bulk_quote)
        << " sizeof(b): " << sizeof(b) << endl;
    cout << "sizeof(Quote): " << sizeof(Quote)
        << " sizeof(q): " << sizeof(q) << endl;
    cout << "sizeof(string): " << sizeof(string)
        << " sizeof(double): " << sizeof(double) << endl;
    cout << "sizeof(size_t): " << sizeof(size_t)
        << " sizeof(double): " << sizeof(double) << endl;
    cout << "sizeof(void*): " << sizeof(void*) << endl;

    return 0;
}