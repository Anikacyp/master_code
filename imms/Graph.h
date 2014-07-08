//
//  Graph.h
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#ifndef __imms__Graph__
#define __imms__Graph__

#include <iostream>
#include <map>
#include <iostream>
#include <set>
#include <fstream>
#include <vector>
#include "Objects.h"

class Graph{
private:
    bool built=false;
    std::vector<std::string> files;
    
    //this map store node and its corresponding id;
    std::map<int,int> node_id_map;
    //this map store node and its corresponding net;
    std::map<int,int> node_net_map;
    //this map real node_id and its corresponding nodes;
    std::map<int,std::set<int> > node_set_map;
    
    //nii record the influence between the same node.
    std::map<int,double> weakCoeff;
    
    std::map<int,std::vector<ADJ> > adjTable;
    std::vector<Edge> Edges;
public:
    Graph();
    ~Graph();
    void fileInput();
    void buildGraph();
    void adjacentTable(int u,int v,double w);
    void weakCoefficient();
    void nodeintGraph();
    bool isBuilt();
    //return variables
    std::map<int,int> getNodeIdMap();
    std::map<int,int> getNodeNetMap();
    std::map<int,std::set<int> >getNodeSetMap();
    std::map<int,double> getWeakCoeff();
    std::map<int,std::vector<ADJ> > getAdjTable();
    std::vector<Edge> getEdges();
};

#endif /* defined(__imms__Graph__) */
