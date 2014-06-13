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
GraphIndexer::~GraphIndexer(){}

void GraphIndexer::setNetInfo(NETINFO ninfo)
{
    this->nInfo=ninfo;
    this->edges=this->nInfo.edges;
    this->nodes=this->nInfo.nodes;
    this->node_set=this->nInfo.node_set;
}
void GraphIndexer::indexing()
{
    //int nSize=0;
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
        
        //std::cout<<u.node_ID<<"_"<<u.net_ID<<"\t"<<v.node_ID<<"_"<<v.net_ID<<"\t"<<w1<<"\t"<<w2<<std::endl;
        
        if(headIndex.count(keyu))
        {
            AdjNode tmpNode=adjnodes[headIndex[keyu]-1];
            EdgeNode tedge;
            
            tedge.node_ID=v.node_ID;
            tedge.net_ID=v.net_ID;
            tedge.weight=w1;
            tmpNode.edgenodes.push_back(tedge);
            adjnodes[headIndex[keyu]-1]=tmpNode;
        }
        else
        {
            AdjNode tmpNode;
            tmpNode.node_ID=u.node_ID;
            tmpNode.net_ID=u.net_ID;
            
            EdgeNode tedge;
            tedge.node_ID=v.node_ID;
            tedge.net_ID=v.net_ID;
            tedge.weight=w1;
            
            tmpNode.edgenodes.push_back(tedge);
            adjnodes.push_back(tmpNode);
            headIndex[keyu]=adjnodes.size();
        }
        
        
        if(headIndex.count(keyv))
        {
            AdjNode tmpNode=adjnodes[headIndex[keyv]-1];
            EdgeNode tedge;
            
            tedge.node_ID=u.node_ID;
            tedge.net_ID=u.net_ID;
            tedge.weight=w2;
            
            tmpNode.edgenodes.push_back(tedge);
            adjnodes[headIndex[keyv]-1]=tmpNode;
        }else
        {
            AdjNode tmpNode;
            tmpNode.node_ID=v.node_ID;
            tmpNode.net_ID=v.net_ID;
            
            EdgeNode tedge;
            tedge.node_ID=u.node_ID;
            tedge.net_ID=u.net_ID;
            tedge.weight=w2;
            
            tmpNode.edgenodes.push_back(tedge);
            adjnodes.push_back(tmpNode);
            headIndex[keyv]=adjnodes.size();
        }
        iter++;
    }
}