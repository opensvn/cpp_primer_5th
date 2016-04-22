#ifndef CPP_ODS_Array_H
#define CPP_ODS_Array_H

#include <cstddef>

template <typename T>
class Array {
public:
    Array(size_t len = 0) {
        length = len;
        a = new T[length];
    }

    T& operator[](size_t i) {
        return a[i];
    }

    Array<T>& operator=(Array<T> &b) {
        if (a != NULL)
            delete[] a;
        a = b.a;
        length = b.length;
        b.a = NULL;
        return *this;
    }

    ~Array() {
        if (a != NULL)
            delete[] a;
    }

    size_t getLength() {
        return length;
    }
private:
    T *a;
    size_t length;
};

#endif

