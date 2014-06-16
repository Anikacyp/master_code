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
void GraphIndexer::adjTable()
{
    headIndex.clear();
    adjnodes.clear();
	std::vector<Edge>::iterator iter=this->edges.begin();
	while(iter!=this->edges.end())
	{
		Edge edge=*iter;
        
		Node u=edge.u;
		Node v=edge.v;
        
        float w1=edge.w1;
        float w2=edge.w2;
        
        //std::string keyu=std::to_string(u.node_ID)+"_"+std::to_string(u.net_ID);
        //std::string keyv=std::to_string(v.node_ID)+"_"+std::to_string(v.net_ID);
        
        //std::cout<<u.node_ID<<"_"<<u.net_ID<<"\t"<<v.node_ID<<"_"<<v.net_ID<<"\t"<<w1<<"\t"<<w2<<std::endl;
        
        if(headIndex.count(u))
        {
            //std::cout<<"Exist "<<u.node_ID<<"_"<<u.net_ID<<std::endl;
            AdjNode tmpNode=adjnodes[headIndex[u]-1];
            EdgeNode tedge;
            
            tedge.node_ID=v.node_ID;
            tedge.net_ID=v.net_ID;
            tedge.weight=w1;
            tmpNode.edgenodes.push_back(tedge);
            adjnodes[headIndex[u]-1]=tmpNode;
        }else
        {
            //std::cout<<"Not exist "<<u.node_ID<<"_"<<u.net_ID<<std::endl;
            AdjNode tmpNode;
            tmpNode.node_ID=u.node_ID;
            tmpNode.net_ID=u.net_ID;
            
            EdgeNode tedge;
            tedge.node_ID=v.node_ID;
            tedge.net_ID=v.net_ID;
            tedge.weight=w1;
            
            tmpNode.edgenodes.push_back(tedge);
            adjnodes.push_back(tmpNode);
            headIndex[u]=adjnodes.size();
        }
        
        
        if(headIndex.count(v))
        {
            //std::cout<<"Exist "<<v.node_ID<<"_"<<v.net_ID<<std::endl;
            AdjNode tmpNode=adjnodes[headIndex[v]-1];
            EdgeNode tedge;
            
            tedge.node_ID=u.node_ID;
            tedge.net_ID=u.net_ID;
            tedge.weight=w2;
            
            tmpNode.edgenodes.push_back(tedge);
            adjnodes[headIndex[v]-1]=tmpNode;
        }else
        {
            //std::cout<<"Not exist "<<v.node_ID<<"_"<<v.net_ID<<std::endl;
            AdjNode tmpNode;
            tmpNode.node_ID=v.node_ID;
            tmpNode.net_ID=v.net_ID;
            
            EdgeNode tedge;
            tedge.node_ID=u.node_ID;
            tedge.net_ID=u.net_ID;
            tedge.weight=w2;
            
            tmpNode.edgenodes.push_back(tedge);
            adjnodes.push_back(tmpNode);
            headIndex[v]=adjnodes.size();
        }
        iter++;
    }
    
    //print information:
    std::vector<AdjNode>::iterator iter1=adjnodes.begin();
    while (iter1!=adjnodes.end()) {
        AdjNode tmp=*iter1;
        
        std::vector<EdgeNode> tedge=tmp.edgenodes;
        std::vector<EdgeNode>::iterator iter2=tedge.begin();
        while (iter2!=tedge.end()) {
            EdgeNode te=*iter2;
            std::cout<<tmp.node_ID<<"_"<<tmp.net_ID<<"\t"<<te.node_ID<<"_"<<te.net_ID<<"\t"<<te.weight<<std::endl;
            iter2++;
        }
        std::cout<<std::endl;
        iter1++;
    }
}


void GraphIndexer::infCal()
{
    std::set<int>::iterator iter=nodes.begin();
    while (iter!=nodes.end()) {
        if(node_set.count(*iter))
        {
            std::set<int>::iterator iter1=node_set[*iter].begin();
            while (iter1!=node_set[*iter].end()) {
                
                Dijkstra(*iter,*iter1);
                iter1++;
            }
        }
        iter++;
    }
}


void GraphIndexer::Dijkstra(int node_ID,int net_ID)
{
    Node tnode;
    tnode.node_ID=node_ID;
    tnode.net_ID=net_ID;
    if(headIndex.count(tnode))
    {
        AdjNode tadj=adjnodes[headIndex[tnode]-1];
        std::vector<EdgeNode>::iterator iter=tadj.edgenodes.begin();
        float minval=0.0;
        int tnode,tnet;
        while (iter!=tadj.edgenodes.end()) {
            if (iter->weight>minval && (iter->node_ID!=node_ID)) {
                minval=iter->weight;
                tnode=iter->node_ID;
                tnet=iter->net_ID;
            }
            iter++;
        }
        //std::cout<<node_ID<<"_"<<net_ID<<"\t"<<tnode<<"_"<<tnet<<"\t"<<minval<<std::endl;
    }
}











