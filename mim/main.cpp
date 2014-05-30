#include "Graph.h"
#include "PP.h"

int main(int argc, char * argv[])
{
	Graph * graph=new Graph(2);
	graph->inputNet();
	graph->buildGraph();
	graph->printGraph();
	delete graph;	
	return 0;
}