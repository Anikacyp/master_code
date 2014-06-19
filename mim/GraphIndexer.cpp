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
    adjTable();
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
            AdjNode tmpNode=adjnodes[headIndex[u]-1];
            EdgeNode tedge;
            
            tedge.dest=v;
            tedge.weight=w1;
            tmpNode.edgenodes.push_back(tedge);
            adjnodes[headIndex[u]-1]=tmpNode;
        }else
        {
            AdjNode tmpNode;
            tmpNode.source=u;
            
            EdgeNode tedge;
            tedge.dest=v;
            tedge.weight=w1;
            
            tmpNode.edgenodes.push_back(tedge);
            adjnodes.push_back(tmpNode);
            headIndex[u]=adjnodes.size();
        }
        
        
        if(headIndex.count(v))
        {
            AdjNode tmpNode=adjnodes[headIndex[v]-1];
            EdgeNode tedge;
            
            tedge.dest=u;
            tedge.weight=w2;
            
            tmpNode.edgenodes.push_back(tedge);
            adjnodes[headIndex[v]-1]=tmpNode;
        }else
        {
            AdjNode tmpNode;
            tmpNode.source=v;
            
            EdgeNode tedge;
            tedge.dest=u;
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
        
        //std::vector<EdgeNode> tedge=tmp.edgenodes;
        std::vector<EdgeNode>::iterator iter2=tmp.edgenodes.begin();
        while (iter2!=tmp.edgenodes.end()) {
            EdgeNode te=*iter2;
            std::cout<<tmp.source.node_ID<<"_"<<tmp.source.net_ID<<"\t"<<te.dest.node_ID<<"_"<<te.dest.net_ID<<"\t"<<te.weight<<std::endl;
            iter2++;
        }
        std::cout<<std::endl;
        iter1++;
    }
    std::cout<<"-----------------------------------"<<std::endl;
}

void GraphIndexer::infCal()
{
    std::set<int>::iterator iter=nodes.begin();
    while (iter!=nodes.end()) {
        if(node_set.count(*iter))
        {
            std::set<int>::iterator iter1=node_set[*iter].begin();
            while (iter1!=node_set[*iter].end()) {
                
                std::map<Node,std::vector<EdgeNode> > mpp;
                Node node(*iter,*iter1);
                if (!infPath.count(node)) {
                    infPath[node]=mpp;
                }
                S.clear();
                S.insert(node);
                Dijkstra(node,node,1);
                //return;
                iter1++;
            }
        }
        iter++;
    }
}


int GraphIndexer::Dijkstra(Node source, Node tmp,int num)
{
    //if(num>3)
      //  return 1;
    std::map<Node,double> dijkmap;
    std::map<Node,std::vector<EdgeNode> > tmpp=infPath[source];
    float minval=0.0;
    Node tmpnode;
    bool flag=false;
    if(headIndex.count(tmp))
    {
        //get the original map of the current node.
        if(infMap.count(source))
        {
            dijkmap=infMap[source];
        }
        if(infPath.count(source))
        {
            tmpp=infPath[source];
        }
        if (source==tmp) {
            dijkmap[tmp]=1;
            std::vector<EdgeNode> tedges;
            EdgeNode tedge(tmp,1.0);
            tedges.push_back(tedge);
            tmpp[tmp]=tedges;
        }
        //update the maximum-propagation-path value, get the adjacent table of the current node.
        AdjNode tadj=adjnodes[headIndex[tmp]-1];
        std::vector<EdgeNode>::iterator iter=tadj.edgenodes.begin();
       
        while (iter!=tadj.edgenodes.end()) {
            if(iter->dest.net_ID==source.net_ID){
            if(dijkmap.count(iter->dest))
            {
                if (dijkmap[iter->dest]<(dijkmap[tmp]*(iter->weight)))
                {
                    dijkmap[iter->dest]=dijkmap[tmp]*(iter->weight);
                    //record the path
                    std::vector<EdgeNode> tedges=tmpp[tmp];
                    EdgeNode tedge(iter->dest,iter->weight);
                    tedges.push_back(tedge);
                    tmpp[iter->dest]=tedges;
                }
            }else
            {
                if (dijkmap[tmp]*iter->weight!=0)
                {
                    dijkmap[iter->dest]=dijkmap[tmp]*iter->weight;
                    //record the path
                    std::vector<EdgeNode> tedges=tmpp[tmp];
                    EdgeNode tedge(iter->dest,iter->weight);
                    tedges.push_back(tedge);
                    tmpp[iter->dest]=tedges;
                }
            }
            }
            iter++;
        }
        infMap[source]=dijkmap;
        infPath[source]=tmpp;
        S.insert(tmp);
        std::map<Node,double>::iterator siter=dijkmap.begin();
        while (siter!=dijkmap.end()) {
            if (!S.count(siter->first))
            {
                if (minval<siter->second)
                {
                    minval=siter->second;
                    tmpnode=siter->first;
                    flag=true;
                }
            }
            siter++;
        }
    }

    if (flag) {
        return Dijkstra(source,tmpnode,num+1);
    }else
        return 0;
    
}

void GraphIndexer::prints()
{
    std::map<Node,std::map<Node,double> >::iterator iter1=infMap.begin();
    while (iter1!=infMap.end()) {
        std::map<Node,std::vector<EdgeNode> >tpath=infPath[iter1->first];
        std::map<Node,double> tmap=iter1->second;
        std::map<Node,double>::iterator iter2=tmap.begin();
        while (iter2!=tmap.end()) {
            std::cout<<iter1->first.node_ID<<"_"<<iter1->first.net_ID<<"\t"<<iter2->first.node_ID<<"_"<<iter2->first.net_ID<<"\t"<<iter2->second<<std::endl;
            std::cout<<"path";
            if(tpath.count(iter2->first))
            {
                std::vector<EdgeNode> tedges=tpath[iter2->first];
                std::vector<EdgeNode>::iterator iter3=tedges.begin();
                while (iter3!=tedges.end()) {
                    std::cout<<iter3->dest.node_ID<<"_"<<iter3->dest.net_ID<<": "<<iter3->weight<<"\t";
                    iter3++;
                }
            }
            std::cout<<std::endl;
            std::cout<<std::endl;
            iter2++;
        }
        iter1++;
    }
}
