#ifndef _BULK_QUOTE_H
#define _BULK_QUOTE_H

#include "quote.h"

class Bulk_quote : public Quote
{
friend std::ostream &operator<<(std::ostream &, const Bulk_quote &);
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string&, double, std::size_t,
        double);
    ~Bulk_quote() = default;

    double net_price(std::size_t) const override;
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};

#endif