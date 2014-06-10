#include "Graph.h"
#include "PP.h"
#include <cstdlib>
#include <ctime>
//#include <stdlib.h>
int main(int argc, char * argv[])
{
	
	Graph * graph=new Graph(2);
	graph->inputNet();
	graph->buildGraph();
    
    
	PP *pp=new PP();
	pp->setNetInfo(graph->getNetInfo());
    pp->infProbCal();
    
    
    delete pp;
	delete graph;	
	/*
	std::srand(unsigned(time(0)));
	for(int i=0;i<10;i++)
	{
		double val=std::rand()/(double)(RAND_MAX/10);
		std::cout<<val<<std::endl;
	}*/
	return 0;
}