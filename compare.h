#ifndef _COMPARE_H
#define _COMPARE_H

#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

struct Sales_Data
{
    std::string isbn;
    double price;
};

template <typename T>
int compare(const T &v1, const T &v2)
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}

template <unsigned N, unsigned M>
int compare(const char (&p)[N], const char (&q)[M])
{
    return strcmp(p, q);
}

template <typename I, typename V>
I find(I first, I last, const V &value)
{
    while (first != last)
    {
        if (*first == value)
        {
            break;
        }
        ++first;
    }
    return first;
}

template <typename T, unsigned N>
std::ostream &print(std::ostream &os, const T (&p)[N])
{
    for (int i = 0; i < N; ++i)
    {
        os << p[i] << " ";
    }
    return os;
}

template <typename T, unsigned N>
const T *first(const T (&p)[N])
{
    cout << "begin: const * const *" << endl;
    return &p[0];
}

template <typename T, unsigned N>
const T *last(const T (&p)[N])
{
    cout << "end: const * const *" << endl;
    return &p[N];
}

template <typename T, unsigned N>
const T *first(T (&p)[N])
{
    cout << "begin: const * *" << endl;
    return &p[0];
}

template <typename T, unsigned N>
const T *last(T (&p)[N])
{
    cout << "end: const * *" << endl;
    return &p[N];
}

#endif