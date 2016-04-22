#ifndef CPP_ODS_STACK_H
#define CPP_ODS_STACK_H

template <typename T>
class Stack {
public:
    virtual void push(const T& x) = 0;
    virtual T pop() = 0;
};

#endif

