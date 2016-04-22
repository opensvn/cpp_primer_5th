#ifndef CPP_ODS_SSET_H
#define CPP_ODS_SSET_H

template <typename T>
class SSet {
public:
    virtual size_t size() = 0;
    virtual void add(const T& x) = 0;
    virtual T remove(const T& x) = 0;
    virtual T find(const T& x) = 0;
};

#endif

