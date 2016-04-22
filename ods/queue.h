#ifndef CPP_ODS_QUEUE_H
#define CPP_ODS_QUEUE_H

template <typename T>
class Queue {
public:
    virtual void add(const T& x) = 0;
    virtual void enqueue(const T& x) = 0;
    virtual T remove() = 0;
    virtual T dequeue() = 0;
};

#endif

