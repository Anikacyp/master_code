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
    arcNode(Node v,float w):node(v),weight(w){}
    arcNode(){}
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
	6. std::map<int,std::set<int> > net_node_set;
	*/
	NETINFO netInfo;
    ///
    int net_num;
    std::vector<Edge> edges;
    //std::map<std::string,double> net_inf;
    std::set<int> nodes;
    std::map<int,std::set<int> > node_set;
    //std::map<int,std::set<int> > net_node_set;
    ///
	std::map<std::string, std::vector<arcNode> > AdjForward;
	std::map<std::string, std::vector<arcNode> > AdjBackward;

public:
	PP();
	~PP();

	void setNetInfo(NETINFO ntf);
	void adjTable();

	void infProbCal();
	void MPP(int node_id);
    //std::map<std::string,std::map<std::string,double> >
    void Dijkstra(int node_id,int net_id);
};

#endif