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
#include "stdlib.h"


class Graph{
private:
    bool built;
    std::vector<std::string> files;
    
    //this map store node and its corresponding id;
    std::map<int,int> node_id_map;
    //this map store node and its corresponding net;
    std::map<int,int> node_net_map;
    //this map real node_id and its corresponding nodes;
    std::map<int,std::set<int> > node_set_map;
    //adjacent tables
    std::map<int,std::vector<ADJ> > adjTable;
    //all the edges.
    std::vector<Edge> Edges;
    
    //nii record the influence between the same node.
    //std::map<int,double> weakCoeff;
public:
    Graph(std::vector<std::string> files);
    Graph();
    ~Graph();
    void fileInput();
    void buildGraph();
    void adjacentTable(int u,int v,double w);
    void nodeintGraph();
    bool isBuilt();
    
    std::map<int,int> getNodeIdMap();
    std::map<int,int> getNodeNetMap();
    std::map<int,std::set<int> >getNodeSetMap();
    std::map<int,std::vector<ADJ> > getAdjTable();
    std::vector<Edge> getEdges();
    
    //std::map<int,double> getWeakCoeff();
    //void weakCoefficient();
};

#endif /* defined(__imms__Graph__) */
