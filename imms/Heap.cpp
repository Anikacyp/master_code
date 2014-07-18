//
//  Heap.cpp
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#include "Heap.h"
Heap::Heap(std::map<int,int> map1,std::map<int,int> map2,std::vector<HeapNode> &data)
{
    this->node_id_map=map1;
    this->node_net_map=map2;
    this->data=data;
    this->size=data.size();
}
Heap::~Heap(){}

void Heap::heapSort(std::vector<HeapNode> & data)
{
    /*this->size=data.size();
    buildHeap(data);
    
    for (int i=size-1; i>=1; i--) {
        swap(data,0,i);
        this->size-=1;
        heapAdjust(data,0);
    }*/
    //this->size=data.size();
    buildHeap(data);
    for (int i=0; i<size; i++) {
        HeapNode node=pop(data,1);
        if (node.node!=-1) {
            std::cout<<node_id_map[node.node]<<"_"<<node_net_map[node.node]<<"\t"<<node.value<<std::endl;
        }
        heapAdjust(data,0);
    }
    
}


void Heap::buildHeap(std::vector<HeapNode> & data)
{
    for(int i=this->size/2;i>=0;i--)
    {
        heapAdjust(data,i);
    }
}


void Heap::heapAdjust(std::vector<HeapNode> & data, int pos)
{
    int l=pos*2+1;
    int r=pos*2+2;
	int largest=pos;
    if ((l<data.size()) && (data[l].value>data[pos].value))
        largest=l;
    if ((r<data.size()) && (data[r].value>data[largest].value))
        largest=r;
    
    if (largest!=pos)
    {
        swap(data,largest,pos);
        heapAdjust(data,largest);
    }else
    {
        swap(data,0,data.size()-1);
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

void Heap::update(int node, double val)
{
    int position=pos[node];
    data[position].value=val;
    heapAdjust(data,0);
    
}

HeapNode Heap::pop(std::vector<HeapNode> &data,int pop)
{
    HeapNode node;
    if (data.size()>0) {
        node=data[data.size()-1];
        if (pop) {
            data.pop_back();
        }
    }
    return node;
}


void Heap::print(std::vector<HeapNode> data)
{
    for (int i=0; i<data.size(); i++) {
        std::cout<<node_id_map[data[i].node]<<"_"<<node_net_map[data[i].node]<<":\t"<<data[i].value<<std::endl;
    }
}