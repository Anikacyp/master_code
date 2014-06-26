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
    
public:
    void heapBuild();
    void insert();
    HeapNode pop();
    
};
#endif /* defined(__mnim__Heap__) */
