//
//  GraphIndexer.h
//  mnim
//
//  Created by Anika on 6/10/14.
//
//

#ifndef GRAPHINDEXER_H
#define GRAPHINDEXER_H
#include <map>
#include <vector>
#include <iostream>
#include "Graph.h"

typedef struct EdgeNode
{
    Node dest;
    double weight;
    //struct EdgeNode *next;
    EdgeNode(Node node,double w):dest(node),weight(w){}
    EdgeNode(){}
}EdgeNode;


typedef struct AdjNode
{
    Node source;
   // EdgeNode * firstEdge;
    std::vector<EdgeNode> edgenodes;
    AdjNode(){}
}AdjNode;

/*struct MPP
{
    //Node source;
    Node dest;
    //double max_weight;
    std::vector<EdgeNode> path;
    MPP(){}
};*/


class GraphIndexer
{
    
private:
    std::map<Node,int> headIndex;
    std::vector<AdjNode> adjnodes;
    
    //original informationa
    std::vector<Edge> edges;
    std::set<int> nodes;
    std::map<int,std::set<int> > node_set;
    NETINFO nInfo;
    
    
    //propagation probability
    std::map<Node,std::map<Node,double> > infMap;
    std::map<Node,std::map<Node,std::vector<EdgeNode> > > infPath;
    std::set<Node> S;
    
public:
    GraphIndexer(NETINFO ninfo);
    GraphIndexer();
    ~GraphIndexer();
    void setNetInfo(NETINFO ninfo);
    void adjTable();
    void infCal();
    int Dijkstra(Node source,Node tmp,int num);
    void prints();
};

#endif /* defined(__mnim__GraphIndexer__) */
