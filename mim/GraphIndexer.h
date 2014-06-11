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
}AdjNode;

class GraphIndexer
{
private:
    std::map<std::string,int> headIndex;
    std::vector<AdjNode> adjnodes;
    
    std::vector<Edge> edges;
    std::set<int> nodes;
    std::map<int,std::set<int> > node_set;
    NETINFO nInfo;
public:
    GraphIndexer(NETINFO ninfo);
    GraphIndexer();
    ~GraphIndexer();
    void indexing();
};

#endif /* defined(__mnim__GraphIndexer__) */
