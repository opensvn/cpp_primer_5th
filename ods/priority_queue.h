#ifndef CPP_ODS_PRIORITY_QUEUE_H
#define CPP_ODS_PRIORITY_QUEUE_H

template <typename T>
class PriorityQueue {
public:
    virtual void add(const T& x) = 0;
    virtual T deleteMin() = 0;
};

#endif

