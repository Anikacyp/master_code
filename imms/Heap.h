//
//  Heap.h
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#ifndef __imms__Heap__
#define __imms__Heap__

#include <iostream>
#include "Objects.h"
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

#endif /* defined(__imms__Heap__) */
