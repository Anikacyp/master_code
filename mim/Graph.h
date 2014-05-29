#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
/*
	the program stores the information about the inputed graph.
	like the node's degree, the propagation probability

*/
struct Edge
{
	int u,v;
	double w1, w2;
};

struct NtkInfo
{
	std::vector<Edge> edge;
	std::vector<int> degree;
	std::map<int,std::map<int,double> > index;
};

class Graph
{
private:
	int node_num,edge_num;
	std::string file_name;
	static std::vector<Edge> edges;
	static std::vector<int> degree;
	static std::map<int,std::map<int,double> > index;
	NtkInfo ntk;
public:
	Graph(std::string fname);
	~Graph();
	void buildGraph();
	int getNodeNum();
	int getEdgeNum();
	int getDegree(int node_id);
	NtkInfo getNetwork();
};
#endif