
#include <iostream>
#include "queue.h"


int main()
{
    char c;
    std::cout << "Type of queue (a - array, l - list): ";
    std::cin >> c;
    
    BasicQueue *queue = NULL;
    if (c == 'a')
        queue = new ArrayQueue;
    else if (c == 'l')
        queue = new ListQueue;
    else {
        std::cout << "Bad type, exit" << std::endl;
        return 1;
    }

    /*
     * Put here your tests: en/dequeue large number of elements
     */

    delete queue;
    return 0;
}
