#include "array_queue.h"
#include <iostream>
using namespace std;

int main()
{
    ArrayQueue<int> queue;
    for (int i = 0; i < 10; ++i) {
        queue.add(i);
        queue.print();
    }

    queue.remove();
    queue.remove();
    queue.print();

    return 0;
}