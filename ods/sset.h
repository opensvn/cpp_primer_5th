#ifndef CPP_ODS_SSET_H
#define CPP_ODS_SSET_H

template <typename T>
class SSet {
public:
    size_t size() = 0;
    void add(const T& x) = 0;
    T remove(const T& x) = 0;
    T find(const T& x) = 0;
};

#endif