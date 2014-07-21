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
#include <map>

class Heap
{
private:
    std::vector<HeapNode> data;
    std::map<int,int> node_id_map;
    std::map<int,int> node_net_map;
    int size;
public:
    Heap(std::map<int,int> map1,std::map<int,int> map2,std::vector<HeapNode> &data);
    ~Heap();
    void buildHeap(std::vector<HeapNode> &data);
    void heapSort(std::vector<HeapNode> &data);
    void heapAdjust(std::vector<HeapNode> &data,int pos);
    void swap(std::vector<HeapNode> & data,int p1,int p2);
    HeapNode pop(std::vector<HeapNode> &data,int isPop);
    
    //void update(int node,double val);
    void print(std::vector<HeapNode> data);
};

#endif /* defined(__imms__Heap__) */
