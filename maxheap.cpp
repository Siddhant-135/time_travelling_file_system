#include <iostream>
#include "header.hpp"
#include <vector>
#include <algorithm> 
using namespace std; 
//======================================
maxheap::maxheap()
{
    capacity = 31;
    heap.resize(capacity);
    size = 0; 
}

maxheap::~maxheap()
{
}
//======================================
void maxheap::heap_down(int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    
    if(left < size && heap[left]->vcount > heap[largest]->vcount)
    {
        largest = left;
    }
    if(right < size && heap[right]->vcount > heap[largest]->vcount)
    {
        largest = right;
    }
    if(largest != i)
    {
        swap(heap[i], heap[largest]);
        heap_down(largest);
    }
}

void maxheap::heap_up(int i)
{
    int p = (i-1)/2;
    while(i > 0 && p>=0)
    {
        int vi = heap[i]->vcount;
        int vp = heap[p]->vcount;
        if (vi>vp)
        {
            swap(heap[i], heap[p]);
        }
        i = p;
        p = (i-1)/2;
    }
}

void maxheap::insert(tree* thefile)
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

void maxheap::heapify()
{
    for(int j=(size/2)-1; j>=0; j--)
    {
        heap_down(j); 
    }
}

tree* maxheap::poptop()
{
    if (size == 0) return nullptr;
    swap(heap[0], heap[size-1]);
    size-=1;
    heapify();
    return heap[size]; 
}

void maxheap::topk(int k)
{
    maxheap temp = *this;
    for(int j =0; j<k; j++)
    {
        tree* t = temp.poptop();
        if (t) {
            cout << t->filename << " " << t->vcount+1 << endl;
        }
    }
}