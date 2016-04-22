#ifndef CPP_ODS_USET_H
#define CPP_ODS_USET_H

template <typename T>
class USet {
public:
    virtual size_t size() = 0;
    virtual void add(const T& x) = 0;
    virtual void remove(const T& x) = 0;
    virtual T find(const T& x) = 0;
};

#endif

