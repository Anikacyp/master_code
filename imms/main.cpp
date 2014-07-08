//
//  main.cpp
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#include "Graph.h"
#include "Model.h"
#include "BaseLine.h"

int main(int argc,char * argv[])
{
	Graph * graph=new Graph();
    graph->buildGraph();
    BaseLine *baseline=new BaseLine(graph);
    baseline->run();
    delete baseline;
    delete graph;
    return 1;
}