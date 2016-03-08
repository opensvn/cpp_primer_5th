#include <string>
#include <iostream>
#include "bulk_quote.h"

using std::string;
using std::ostream;

ostream &operator<<(ostream &out, const Bulk_quote &b)
{
    out << "ISBN: " << b.isbn() << " #price: " << b.price
    << " #min: " << b.min_qty << " #discount: " << b.discount;
    return out;
}

Bulk_quote::Bulk_quote(const string& book, double sales_price,
    size_t min, double discnt): Quote(book, sales_price),
    min_qty(min), discount(discnt)
{
}

double Bulk_quote::net_price(size_t cnt) const
{

}