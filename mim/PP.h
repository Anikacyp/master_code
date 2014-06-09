#ifndef PP_H
#define PP_H
#include <map>
//#include <set>
#include <vector>
#include "Graph.h"

struct arcNode
{
	Node node;
	float weight;
	/*arcNode * next;
	arcNode(){}
	arcNode(Node v, float w): node(v), weight(w), next(NULL){}
	arcNode(Node v):node(v),weight(0),next(NULL){}*/
};

struct InfProb
{
	int u,v;
	double w;
	std::vector<Node> path;
};

class PP
{
private:
	/*
	netInfo contains: 
	1. int net_num;
	2. std::vector<Edge> edges;
	3. std::map<std::string,double> net_inf;
	4. std::set<int> nodes;
	5. std::map<int,std::set<int> > node_set;
	6. std::map<int,std::set<int> >net_node_set;
	*/
	NETINFO netInfo;
	std::map<std::string, std::vector<arcNode> > AdjForward;
	std::map<std::string, std::vector<arcNode> > AdjBackward;
    std::map<int,std::set<int> > node_set;

public:
	PP();
	~PP();

	void setNetInfo(NETINFO ntf);
	void indexing();

	double infProbCal(int nodeA,int nodeB);
	void subinf(Node nodeA,Node nodeB);
};

#endif