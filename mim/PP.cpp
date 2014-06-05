#include "PP.h"
PP::PP(){}

PP::~PP(){}


void PP::setNetInfo(NETINFO ntf)
{
	this->netInfo=ntf;
	this->indexing();
}

void PP::indexing()
{
	std::vector<Edge> edges=netInfo.edges;
	std::vector<Edge>::iterator iter=edges.begin();
	while(iter!=edges.end())
	{
		Edge edge=*iter;

		Node u=edge.u;
		Node v=edge.v;

		
		
		iter++;
	}
}
void PP::infProbCal()
{
		
}

void PP::DFS(int u, int v)
{

}