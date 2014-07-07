//
//  Model.cpp
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#include "Model.h"

Model::Model()
{
	Graph *graph=new Graph();
    graph->buildGraph();
    this->node_id_map=graph->getNodeIdMap();
    this->node_net_map=graph->getNodeNetMap();
    this->node_set_map=graph->getNodeSetMap();
    this->weakCoeff=graph->getWeakCoeff();
    this->adjTable=graph->getAdjTable();
    delete graph;
    MPP();
    print();
}
Model::~Model(){}

int randomNum(int range)
{
    std::srand(unsigned(time(0)));
    return std::rand()%range;
}

void Model::traversal()
{
    std::map<int,int>::iterator iter=this->node_id_map.begin();
    while (iter!=node_id_map.end()) {
        spread(iter->first);
        iter++;
    }
    /*std::map<int,std::vector<ADJ> >::iterator iter=adjTable.begin();
     while (iter!=adjTable.end()) {
     std::cout<<node_id_map[iter->first]<<"_"<<node_net_map[iter->first]<<":"<<std::endl;
     std::vector<ADJ> adjs=iter->second;
     for (int i=0; i<adjs.size(); i++) {
     std::cout<<node_id_map[adjs[i].u]<<"_"<<node_net_map[adjs[i].u]<<"\t"<<adjs[i].w<<std::endl;
     }
     std::cout<<"-------------------"<<std::endl;
     iter++;
     }*/
}


//hop-based influence calculation
void Model::spread(int node)
{
   
}


void Model::MPP()
{
    std::map<int,int>::iterator iter=this->node_id_map.begin();
    while (iter!=node_id_map.end()) {
        
        current_node=iter->first;
        
        tmppp.clear();
        tmppath.clear();
        tmpS.clear();
        tmpids.clear();
		
        //tmpS.insert(current_node);
        tmppp[current_node]=1.0;
        ADJ adj(current_node,1.0);
        tmppath[current_node].push_back(adj);
        
        //tmpids.insert(node_id_map[current_node]);
        
        Dijkstra(current_node);
        
        miv[current_node]=tmppp;
        mip[current_node]=tmppath;
        
        iter++;
    }
}
void Model::Dijkstra(int id)
{
    tmpS.insert(current_node);
    tmpids.insert(node_id_map[current_node]);
    
    if (adjTable.count(id)) {
        double tv=0.0,tmv=0.0;
        int tmp_id=-1;
        std::vector<ADJ> adjs=adjTable[id];
        for(int i=0;i<adjs.size();i++)
        {
            if (!tmpS.count(adjs[i].u))
            {
            	tv=tmppp[id]*adjs[i].w;
            	if (tv>THETA)
                {
                    /*if ((!tmppp.count(adjs[i].u)) || (tmppp[adjs[i].u]<tv))
                        {
                            
                            tmppp[adjs[i].u]=tv;
                            recordPath(id,adjs[i].u,adjs[i].w);
                        }
                        if (tmv<tv)
                        {
                            tmv=tv;
                            tmp_id=adjs[i].u;
                        }*/

                    if (!tmppp.count(adjs[i].u))
                    {
                        if (tmpids.count(node_id_map[adjs[i].u])) {
                            if (node_id_map[id]!=node_id_map[adjs[i].u]) {
                                tv*=weakCoeff[node_id_map[adjs[i].u]];
                            }
                        }
                        if (tv>THETA) {
                            tmppp[adjs[i].u]=tv;
                            recordPath(id,adjs[i].u,adjs[i].w);
                        }
                    }else
                    {
                        if (tmpids.count(node_id_map[adjs[i].u])) {
                            if (node_id_map[id]!=node_id_map[adjs[i].u]) {
                                tv*=weakCoeff[node_id_map[adjs[i].u]];
                            }
                        }
                        if (tv>THETA && tmppp[adjs[i].u]<tv) {
                            tmppp[adjs[i].u]=tv;
                            recordPath(id,adjs[i].u,adjs[i].w);
                        }
                    }
                    
            	}
            }
        }
        //choose the next immediate point
        std::map<int,double>::iterator iter=tmppp.begin();
        while (iter!=tmppp.end()) {
            if (!tmpS.count(iter->first)) {
                if (tmv<iter->second) {
                    tmv=iter->second;
                    tmp_id=iter->first;
                }
            }
            iter++;
        }
        //recursive call
    	if (tmp_id!=-1)
        {
            tmpS.insert(tmp_id);
            tmpids.insert(node_id_map[tmp_id]);
            Dijkstra(tmp_id);
        }else
            return;
        
    }
}

void Model::recordPath(int source,int dest, double w)
{
    ADJ adj(dest,w);
    std::vector<ADJ> adjs=tmppath[source];
    adjs.push_back(adj);
    tmppath[dest]=adjs;
}

void Model::print(){
    std::map<int,std::map<int,double> >::iterator iter=miv.begin();
    while (iter!=miv.end()) {
        //std::cout<<"----"<<node_id_map[iter->first]<<"_"<<node_net_map[iter->first]<<"----"<<std::endl;
        std::map<int,double> tval=iter->second;
        std::map<int,std::vector<ADJ> > tpath=mip[iter->first];
        std::map<int,double>::iterator iter1=tval.begin();
        while (iter1!=tval.end()) {
            std::cout<<node_id_map[iter->first]<<"_"<<node_net_map[iter->first]<<"\t"<<node_id_map[iter1->first]<<"_"<<node_net_map[iter1->first]<<"\t"<<iter1->second<<std::endl;
            std::vector<ADJ> links=tpath[iter1->first];
            for (int i=0; i<links.size(); i++) {
                std::cout<<node_id_map[links[i].u]<<"_"<<node_net_map[links[i].u]<<" :"<<links[i].w<<"\t";
            }
            std::cout<<"\n\n"<<std::endl;
            iter1++;
        }
        iter++;
    }
}