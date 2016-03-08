#include <iostream>
#include "quote.h"

using std::ostream;

ostream &operator<<(ostream &out, const Quote &q)
{
    out << "ISBN: " << q.isbn() << " #price: " << q.price;
    return out;
}