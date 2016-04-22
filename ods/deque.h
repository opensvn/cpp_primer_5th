#ifndef CPP_ODS_DEQUE_H
#define CPP_ODS_DEQUE_H

template <typename T>
class Deque {
public:
    virtual void addFirst(const T& x) = 0;
    virtual void addLast(const T& x) = 0;
    virtual T removeFirst() = 0;
    virtual T removeLast() = 0;
};

#endif

