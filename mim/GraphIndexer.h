//
//  GraphIndexer.h
//  mnim
//
//  Created by Anika on 6/10/14.
//
//

#ifndef GraphIndexer__
#define GraphIndexer__
#include <map>
#include <vector>
#include <iostream>
#include "Graph.h"

typedef struct EdgeNode
{
    int node_ID;
    int net_ID;
    double weight;
    //struct EdgeNode *next;
}EdgeNode;


typedef struct AdjNode
{
    int node_ID;
    int net_ID;
   // EdgeNode * firstEdge;
    std::vector<EdgeNode> edgenodes;
    //AdjNode(){}
}AdjNode;

struct MPP
{
    //Node source;
    Node dest;
    std::vector<EdgeNode> path;
    MPP(){}
    bool operator <(const MPP& mpp1)
    {
        return dest.node_ID<mpp1.dest.node_ID;
    }
};


class GraphIndexer
{
    
private:
    //std::map<std::string,int> headIndex;
    std::map<Node,int> headIndex;
    std::vector<AdjNode> adjnodes;
    
    //original informationa
    std::vector<Edge> edges;
    std::set<int> nodes;
    std::map<int,std::set<int> > node_set;
    NETINFO nInfo;
    
    
    //propagation probability
    std::map<Node,std::map<Node,double> > infMap;
    std::map<Node,MPP> infPath;
    
public:
    GraphIndexer(NETINFO ninfo);
    GraphIndexer();
    ~GraphIndexer();
    void setNetInfo(NETINFO ninfo);
    void adjTable();
    void infCal();
    void Dijkstra(int node_ID, int net_ID);
};

#endif /* defined(__mnim__GraphIndexer__) */
