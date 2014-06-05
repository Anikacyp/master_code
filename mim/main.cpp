#include "Graph.h"
#include "PP.h"

int main(int argc, char * argv[])
{
	Graph * graph=new Graph(2);
	graph->inputNet();
	graph->buildGraph();
	//graph->printGraph();
	PP *pp=new PP();
	pp->setNetInfo(graph->getNetInfo());
	pp->indexing();
	delete graph;	
	return 0;
}