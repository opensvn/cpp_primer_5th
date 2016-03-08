#include <string>
#include <iostream>
#include "lmt_quote.h"

using std::string;
using std::ostream;

ostream &operator<<(ostream &out, const Lmt_quote &l)
{
    out << "ISBN: " << l.isbn() << " #price: " << l.price
    << " #max: " << l.lmt_qty << " #discount: " << l.discount;
    return out;
}

Lmt_quote::Lmt_quote(const string& book, double sales_price,
    size_t max, double discnt): Quote(book, sales_price),
    lmt_qty(max), discount(discnt)
{
}

double Lmt_quote::net_price(size_t cnt) const
{
    if (cnt <= lmt_qty)
    {
        return cnt * (1 - discount) * price;
    }
    else
    {
        return (cnt - lmt_qty * discount) * price;
    }
}