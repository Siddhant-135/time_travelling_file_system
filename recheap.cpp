#include <iostream>
#include "header.hpp"
#include <vector>
#include <algorithm> 
using namespace std; 
//======================================
recheap::recheap()
{
    capacity = 31;
    heap.resize(capacity);
    size = 0; 
}

recheap::~recheap()
{
}
//======================================
void recheap::heap_down(int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    
    if(left < size && heap[left]->ltime > heap[largest]->ltime)
    {
        largest = left;
    }
    if(right < size && heap[right]->ltime > heap[largest]->ltime)
    {
        largest = right;
    }
    if(largest != i)
    {
        swap(heap[i], heap[largest]);
        heap_down(largest);
    }
}

void recheap::heap_up(int i)
{
    int p = (i-1)/2;
    while(i > 0 && p>=0)
    {
        if (heap[i]->ltime>heap[p]->ltime)
        {
            swap(heap[i], heap[p]);
        }
        i = p;
        p = (i-1)/2;
    }
}

void recheap::insert(tree* thefile)
{
    if(size == 0)
    {
        heap[0] = thefile;
        size += 1; 
    }
    else
    {
        heap[size] = thefile;
        heap_up(size);
        size+=1;
    }
}

void recheap::heapify()
{
    for(int j=(size/2)-1; j>=0; j--)
    {
        heap_down(j); 
    }
}

tree* recheap::poptop()
{
    if (size == 0) return nullptr;
    swap(heap[0], heap[size-1]);
    size-=1;
    heapify();
    return heap[size]; 
}
string printer(chrono::time_point<std::chrono::system_clock> timestamp)
{
    time_t time = std::chrono::system_clock::to_time_t(timestamp);
    char buffer[26];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    return buffer;
}
void recheap::topk(int k)
{
    recheap temp = *this;
    for(int j =0; j<k; j++)
    {
        tree* t = temp.poptop();
        if (t) {
            cout << t->filename << " " << printer(t->ltime) << endl;
        }
    }
}