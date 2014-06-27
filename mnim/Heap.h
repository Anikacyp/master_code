//
//  Heap.h
//  mnim
//
//  Created by Anika on 6/26/14.
//
//

#ifndef __mnim__Heap__
#define __mnim__Heap__

#include <iostream>
#include "BaseObj.h"
#include <vector>

class Heap
{
private:
    std::vector<HeapNode> data;
    int size;
public:
    Heap();
    ~Heap();
    void buildHeap(std::vector<HeapNode> &data);
    void heapSort(std::vector<HeapNode> &data);
    void heapAdjust(std::vector<HeapNode> &data,int pos);
    
    void insert();
    HeapNode pop();
    void print(std::vector<HeapNode> & data);
    void swap(std::vector<HeapNode> & data,int p1,int p2);
};
#endif /* defined(__mnim__Heap__) */
