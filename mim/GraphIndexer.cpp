//
//  GraphIndexer.cpp
//  mnim
//
//  Created by Anika on 6/10/14.
//
//

#include "GraphIndexer.h"

GraphIndexer::GraphIndexer(NETINFO ninfo)
{
    this->nInfo=ninfo;
    this->edges=this->nInfo.edges;
    this->nodes=this->nInfo.nodes;
    this->node_set=this->nInfo.node_set;
}
GraphIndexer::GraphIndexer(){}

void GraphIndexer::indexing()
{
    int nSize=0;
   /* std::map<int,std::set<int> >::iterator iter=node_set.begin();
    while (iter!=node_set.end()) {
        nSize+=iter->second.size();
        iter++;
    }*/
    //this->AdjList=new HeadNode[nSize];
	std::vector<Edge>::iterator iter=this->edges.begin();
	while(iter!=this->edges.end())
	{
		Edge edge=*iter;
        
		Node u=edge.u;
		Node v=edge.v;
        
        float w1=edge.w1;
        float w2=edge.w2;
        
        std::string keyu=std::to_string(u.node_ID)+"_"+std::to_string(u.net_ID);
        std::string keyv=std::to_string(v.node_ID)+"_"+std::to_string(v.net_ID);
        
        if(headIndex.count(keyu))
        {
            AdjNode tmpNode=adjnodes[headIndex[keyu]];
            EdgeNode tedge;
            tedge.node_ID=v.node_ID;
            tedge.net_ID=v.net_ID;
            tedge.weight=w2;
            tmpNode.edgenodes.push_back(tedge);
            adjnodes[headIndex[keyu]]=tmpNode;
        }else
        {
            AdjNode tmpNode;
            EdgeNode tedge;
            tedge.node_ID=v.node_ID;
            tedge.net_ID=v.net_ID;
            tedge.weight=w2;
            tmpNode.edgenodes.push_back(tedge);
            adjnodes[headIndex[keyu]]=tmpNode;
            int size=headIndex.size();
            headIndex[keyu]=size+1;
        }
        
        
        if(headIndex.count(keyv))
        {
            AdjNode tmpNode=adjnodes[headIndex[keyv]];
            EdgeNode tedge;
            tedge.node_ID=u.node_ID;
            tedge.net_ID=u.net_ID;
            tedge.weight=w1;
            tmpNode.edgenodes.push_back(tedge);
            adjnodes[headIndex[keyv]]=tmpNode;
        }else
        {
            AdjNode tmpNode;
            EdgeNode tedge;
            tedge.node_ID=u.node_ID;
            tedge.net_ID=u.net_ID;
            tedge.weight=w1;
            tmpNode.edgenodes.push_back(tedge);
            adjnodes[headIndex[keyv]]=tmpNode;
            int size=headIndex.size();
            headIndex[keyv]=size+1;
        }
    }
}