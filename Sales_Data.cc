#include <iostream>
#include <string>
using namespace std;

struct Sales_data
{
    Sales_data &operator+=(const Sales_data &rhs);
    std::string isbn() { return bookNo; }
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

ostream &operator<<(ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

instream &operator>>(instream &in, Sales_data &item)
{
    double price;
    in >> item.bookNo >> item.units_sold >> price;
    if (in)
        item.revenue = price * item.units_sold;
    else
        item = Sales_data();
    return in;
}

ostream &operator>>(ostream &out, const Sales_data &data);
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs);

int main()
{
    return 0;
}