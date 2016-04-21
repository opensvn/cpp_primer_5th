#ifndef CPP_ODS_ARRAY_STACK_H
#define CPP_ODS_ARRAY_STACK_H

#include "array.h"
#include "list.h"
#include <iostream>

template <typename T>
class ArrayStack: public List<T> {
public:
    ArrayStack(size_t capacity): array(capacity), num(0) {}
    size_t size() { return num; }
    T get(size_t i) { return array[i]; }
    T set(size_t i, const T& x) {
        T y = array[i];
        array[i] = x;
        return y;
    }
    T remove(size_t i) { 
        T x = array[i];
        for (int j = i; j < num - 1; ++j)
            array[j] = array[j + 1];
        --num;
        return x;
    }
    void add(size_t i, const T& x) {
        if (num + 1 > array.getLength()) resize();
        for (int j = num; j > i; --j)
            array[j] = array[j - 1];
        array[i] = x;
        ++num;
    }

    void print() {
        for (int i = 0; i < num; ++i)
            std::cout << array[i] << " ";
        std::cout << std::endl;
    }
private:
    void resize() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        Array<T> b(std::max(2 * num, size_t(1)));
        for (int i = 0; i < num; ++i)
            b[i] = array[i];
        array = b;
        std::cout << "length: " << array.getLength() << std::endl;
    }

    Array<T> array;
    size_t num;
};

#endif