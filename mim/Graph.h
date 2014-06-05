#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <set>

/*
	the program stores the information about the inputed graph.
	like the node's degree, the propagation probability

*/
struct Node
{
	int node_ID;
	int net_ID;
};


/*bool operator==(Node n1,Node n2)
{
	if((n1.node_ID==n2.node_ID) && (n1.net_ID==n2.net_ID))
		return true;
	else
		return false;
}

bool operator<(Node n1, Node n2)
{
	if(n1.node_ID<n2.node_ID)
		return true;
	else
		return false;
}*/


struct Edge
{
	//int u,v;
	//std::string u,v;
	Node u,v;
	//int net_u,net_v;
	double w1, w2;
};

struct NETINFO
{	
	//description:
	/*
	1.edges:存储边信息，为方便起见，每个点按照点ID+网络ID存储，相同点ID的点为同一个entity
	2.net_inf:存储网络之间的影响系数，表示网络n中的点对网络m中对应点的影响行为，例如：点A在
	微博中发表信息，他再次将此消息发布到人人网中的概率。正常情况下，每个点都有一个系数，这里
	为了方便起见，设为统一值。
	3.nodes:存储所有网络中的点
	4.node_set:map结构，key为点ID，value为一个set，存储这个点在哪些网络中存在。其中set中
	的值为对应的点ID+网络ID
	5.net_node_set:存储了每个网络中所含有的点集合，key为网络ID，value为一个set，存储点ID。
	*/
	int net_num;
	std::vector<Edge> edges;
	std::map<std::string,double> net_inf;
	std::set<int> nodes;
	//std::map<int,std::set<std::string> >node_set;
	std::map<int,std::set<int> > node_set;
	std::map<int,std::set<int> >net_node_set;
};

class Graph
{
private:
	//used to store file
	std::vector<std::string> files;
	std::map<std::string,double>net_inf;

	static std::vector<Edge> edges;

	static std::set<int> nodes;

	//static std::map<int,std::set<std::string> > node_set;

	static std::map<int, std::set<int> > node_set;

	static std::map<int,std::set<int> > net_node_set;	

	NETINFO netInfo;
	//static std::map<std::string,int> degree;
	//static std::map<std::string,std::map<std::string,double> > index;
	
	int node_num,edge_num;
	int net_num;
public:
	Graph(int);
	~Graph();
	void inputNet();
	void buildGraph();
	void printGraph();
	NETINFO getNetInfo();
};
#endif