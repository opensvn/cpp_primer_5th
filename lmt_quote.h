#ifndef _LMT_QUOTE_H
#define _LMT_QUOTE_H

#include "quote.h"

class Lmt_quote : public Quote
{
friend std::ostream &operator<<(std::ostream &, const Lmt_quote &);
public:
    Lmt_quote() = default;
    Lmt_quote(const std::string &, double, std::size_t, double);
    ~Lmt_quote() = default;

    double net_price(std::size_t) const override;
private:
    std::size_t lmt_qty = 0;
    double discount = 0.0;
};

#endif