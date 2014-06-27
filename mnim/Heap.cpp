//
//  Heap.cpp
//  mnim
//
//  Created by Anika on 6/26/14.
//
//

#include "Heap.h"

Heap::Heap(){}
Heap::~Heap(){}
void Heap::heapSort(std::vector<HeapNode> & data)
{
    buildHeap(data);
    int size=data.size();
    for (int i=size; i>=1; i--) {
        
        heapAdjust(data,1);
    }
}

void Heap::buildHeap(std::vector<HeapNode> & data)
{
    int size=data.size();
    for(int i=size/2;i>=0;i--)
    {
        heapAdjust(data,i);
    }
}


void Heap::heapAdjust(std::vector<HeapNode> & data, int pos)
{
    int l=pos*2;
    int r=pos*2+1;
	int largest=pos;
    if ((l<=data.size()) && (data[l].value>data[pos].value))
        largest=l;
    if ((r<=data.size()) && (data[r].value>data[largest].value))
        largest=r;
    if (largest!=pos) {
        swap(data,largest,pos);
        heapAdjust(data,largest);
    }
}


void Heap::swap(std::vector<HeapNode> & data,int p1,int p2)
{
    HeapNode tmpnode;
    tmpnode.node=data[p1].node;
    tmpnode.value=data[p1].value;
    tmpnode.status=data[p1].status;
    data[p1]=data[p2];
    data[p2]=tmpnode;
}