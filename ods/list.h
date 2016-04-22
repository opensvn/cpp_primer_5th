#ifndef CPP_ODS_LIST_H
#define CPP_ODS_LIST_H

template <typename T>
class List {
public:
    virtual size_t size() = 0;
    virtual T get(size_t i) = 0;
    virtual T set(size_t i, const T& x) = 0;
    virtual void add(size_t i, const T& x) = 0;
    virtual T remove(size_t i) = 0;
};

#endif

