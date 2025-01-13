#include "PriorityQueue.hpp"
#include <limits.h>

using namespace std;

void tswap(ReviewInfo *a, ReviewInfo *b)
{
    ReviewInfo temp = *a;
    *a = *b;
    *b = temp;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ(int cap)
{
    capacity = cap;
    currentSize = 0;
    heapArr = new ReviewInfo[cap];
}

/*
Destructor
*/
PriorityQ::~PriorityQ()
{
    delete[] heapArr;                              
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
    return (index - 1) / 2;
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
    return 2 * index +1;
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
    
    return  2 * index + 2;
}

void PriorityQ::peek()
{
    if(heapArr == nullptr)
    {
        cout << "no record found" << endl;
    }
    else
    {
        ReviewInfo rw = heapArr[0];
        cout << "Restaurant: " << rw.restaurantName << endl;
        cout << "Customer: " << rw.customer << endl;
        cout << "Review: " << rw.review << endl;
        cout << "Time: " << rw.time << endl;
    }

}

void PriorityQ::heapify(int i)
{
    int largest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if(left < currentSize && heapArr[left].time > heapArr[largest].time)
    {
        largest = left;
    }
    
    if(right < currentSize && heapArr[right].time > heapArr[largest].time)
    {
        largest = right;
    }

    if(largest != i)
    {
        tswap(&heapArr[i], &heapArr[largest]);
        heapify(largest);
    }
}

void PriorityQ::insertElement(ReviewInfo restaurant)
{
    if(currentSize == capacity)
    {
        cout << "Maximum heap size reached. Cannot insert anymore" << endl;
    }
    else
    {
        int i = currentSize;
        heapArr[i] = restaurant;
        currentSize++;

        while(i != 0 && heapArr[parent(i)].time < heapArr[i].time)
        {
            tswap(&heapArr[parent(i)], &heapArr[i]);
            i = parent(i);
        }
    }
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
    for(int i = 0; i < currentSize; i++)
    {
        cout << "\t" << "Customer: " << heapArr[i].customer << endl;
        cout << "\t" << "Review: " << heapArr[i].review << endl;
        cout << "\t" << "Time: " << heapArr[i].time << endl;
        cout << "\t" << "=====" << endl;
    }
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
    ReviewInfo lastElement = heapArr[currentSize-1];
    heapArr[0] = lastElement;
    currentSize = currentSize - 1;
    heapify(0);
}
