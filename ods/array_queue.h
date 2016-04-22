#ifndef CPP_ODS_ARRAY_QUEUE_H
#define CPP_ODS_ARRAY_QUEUE_H

#include "array.h"
#include <algorithm>
#include <iostream>

template <typename T>
class ArrayQueue {
public:
    ArrayQueue(int len = 0): array(len), front(0), num(0) {}
    void add(const T& x) {
        if (num + 1 > array.getLength())
            resize();
        array[(front + num) % array.getLength()] = x;
        ++num;
    }

    T remove() {
        T x = array[front];
        front = (front + 1) % array.getLength();
        --num;
        return x;
    }

    void print() {
        for (int i = 0; i < num; ++i) {
            std::cout << array[(front + i) % array.getLength()] << " ";
        }
        std::cout << std::endl;
    }
private:
    void resize() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        Array<T> b(std::max(array.getLength() * 2, size_t(1)));

        if (array.getLength() > 0) {
            for (int i = 0; i < num; ++i)
                b[i] = array[(front + i) % array.getLength()];
        }

        front = 0;
        array = b;
    }

    Array<T> array;
    int front;
    int num;
};

#endif

