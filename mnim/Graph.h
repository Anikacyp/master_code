//
//  Graph.h
//  mnim
//
//  Created by Anika on 6/19/14.
//
//

#ifndef __mnim__Graph__
#define __mnim__Graph__

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include "BaseObj.h"

class Graph
{
    
private:
    int network_NO;
    
    std::vector<std::string> files;
    //edges stores the edges of the overall networks
    static std::vector<EDGE> edges;
    
    //adjTable stores the adjacent table of a given node.!!!
    static std::map<NODE, std::vector<ADJEDGE> > adjTable;
    
    //netifmap stores the influence value between networks
    static std::map<NetPair, double> netifmap;
    
    //nodes stores the total nodes of the overall networks!!!
    static std::set<int> nodes;
    
    //netnodes stores the nodes of a network.
    static std::map<int, std::set<int> > netnodes;
    
    //nodenet stores the node was contained in which networks.!!!
    static std::map<int, std::set<int> > nodenet;


public:
    Graph();
    ~Graph();
    void fileInput();
    void graphBuilding();
    void netinfGraph();
    void adjacentTable(NODE n1,NODE n2, double w);
    void print();
    std::map<NODE, std::vector<ADJEDGE> > getAdjTable();
    std::set<int> getNodes();
    std::map<int, std::set<int> > getNodeNet();
};



#endif /* defined(__mnim__Graph__) */
