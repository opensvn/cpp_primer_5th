#ifndef CPP_ODS_DEQUE_H
#define CPP_ODS_DEQUE_H

template <typename T>
class Deque {
public:
    void addFirst(const T& x) = 0;
    void addLast(const T& x) = 0;
    T removeFirst() = 0;
    T removeLast() = 0;
};

#endif