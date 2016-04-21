#ifndef CPP_ODS_USET_H
#define CPP_ODS_USET_H

template <typename T>
class USet {
public:
    size_t size() = 0;
    void add(const T& x) = 0;
    void remove(const T& x) = 0;
    T find(const T& x) = 0;
};

#endif