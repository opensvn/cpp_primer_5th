#ifndef CPP_ODS_QUEUE_H
#define CPP_ODS_QUEUE_H

template <typename T>
class Queue {
public:
    void add(const T& x) = 0;
    void enqueue(const T& x) = 0;
    T remove() = 0;
    T dequeue() = 0;
};

#endif