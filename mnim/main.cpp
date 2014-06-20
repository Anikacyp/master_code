//
//  main.cpp
//  mnim
//
//  Created by Anika on 6/19/14.
//
//
#include <iostream>
#include "Graph.h"
int main(int agrc, char * argv[])
{
    Graph * graph=new Graph();
    graph->fileInput();
    graph->graphBuilding();
    graph->print();
    delete graph;
    return 1;
}
