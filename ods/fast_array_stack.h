#ifndef CPP_ODS_FAST_ARRAY_STACK_H
#define CPP_ODS_FAST_ARRAY_STACK_H

#include "array.h"
#include "list.h"
#include <iostream>

template <typename T>
class FastArrayStack: public List<T> {
public:
    size_t size() {
        return num;
    }

    T get(size_t i) {
        return array[i];
    }

    T set(size_t i, const T& x) {
        T y = array[i];
        array[i] = x;
        return y;
    }

    void add(size_t i, const T& x) {
        if (num + 1 > array.getLength())
            resize();
        std::copy_backward(array + i, array + num, array + num + 1);
        array[i] = x;
        ++num;
    }

private:
    void resize() {
        Array<T> b(std::max(num * 2, size_t(1)));
        std::copy(array + 0, array + num, b + 0);
        array = b;
    }

    Array<T> array;
    size_t num;
};

#endif

