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
struct Edge
{
	//int u,v;
	std::string u,v;
	//int net_u,net_v;
	double w1, w2;
};


class Graph
{
private:
	//used to store file
	std::vector<std::string> files;
	std::map<std::string,double >net_inf;

	static std::vector<Edge> edges;

	static std::set<int> nodes;

	static std::map<int,std::set<std::string> > node_set;

	static std::map<int,std::set<int> > net_node_set;
	//static std::map<int,int> node_map;
	
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
};
#endif