#ifndef PP_H
#define PP_H
#include <map>
#include <set>
#include <vector>
#include "Graph.h"

struct arcNode
{
	Node node;
	float weight=0;
	arcNode * next;
	arcNode(){}
	arcNode(Node v, float w): node(v), weight(w), next(NULL){}
	arcNode(Node v):node(v),weight(0),next(NULL){}
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
	std::map<Node, std::vector<Node> > AdjChild;
	std::map<Node, std::vector<Node> > AdjParent;

public:
	PP();
	~PP();

	void setNetInfo(NETINFO ntf);
	void indexing();

	void infProbCal();
	void DFS();
};

#endif