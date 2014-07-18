//
//  Model.cpp
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#include "Model.h"

Model::Model(Graph *graph)
{
    setVariables(graph);
}
Model::Model(){}
Model::~Model(){}

void Model::setVariables(Graph *graph)
{
    if (!graph->isBuilt()) {
        graph->buildGraph();
    }
    this->node_id_map=graph->getNodeIdMap();
    this->node_net_map=graph->getNodeNetMap();
    this->node_set_map=graph->getNodeSetMap();
    //this->weakCoeff=graph->getWeakCoeff();
    this->adjTable=graph->getAdjTable();
}

/*int randomNum(int range)
{
    srand(unsigned(time(0)));
    return rand()%range;
}*/

void Model::traversal(int type)
{
    if(type==2)
    {
        MPP();
        print();
        std::cout<<"///////////////////////////////"<<std::endl;
        buildMIA();
        //run();
        
    }
}

void Model::MPP()
{
    std::map<int,int>::iterator iter=this->node_id_map.begin();
    HeapNode hnode;
    while (iter!=node_id_map.end()) {
        
        current_node=iter->first;
        tmppp.clear();
        tmppath.clear();
        tmpS.clear();
        tmpids.clear();
        spread=0.0;
		
        tmppp[current_node]=1.0;
        ADJ adj(current_node,1.0);
        tmppath[current_node].push_back(adj);
        //spread+=1.0;
        
        Dijkstra(current_node);
        
        miv[current_node]=tmppp;
        mip[current_node]=tmppath;
        
		if (spread>0) {
            hnode.node=current_node;
            hnode.status=0;
            hnode.value=spread;
            init_seed_spread.push_back(hnode);
        }
        
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
                    if (!tmppp.count(adjs[i].u))
                    {
                        tmppp[adjs[i].u]=tv;
                        recordPath(id,adjs[i].u,adjs[i].w);
                    }else
                    {
                        if (tmppp[adjs[i].u]<tv) {
                            tmppp[adjs[i].u]=tv;
                            recordPath(id,adjs[i].u,adjs[i].w);
                        }
                    }
            	}
            }
        }
        //choose the next intermediate point
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
            spread+=tmv;
            tmpS.insert(tmp_id);
            tmpids.insert(node_id_map[tmp_id]);
            Dijkstra(tmp_id);
        }else
            return;
    }
}

//使用弱化系数计算的最大传播路径
/*
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
                    //if ((!tmppp.count(adjs[i].u)) || (tmppp[adjs[i].u]<tv))
                    //    {
                    //
                    //        tmppp[adjs[i].u]=tv;
                    //        recordPath(id,adjs[i].u,adjs[i].w);
                    //   }
                    //    if (tmv<tv)
                    //    {
                    //        tmv=tv;
                    //        tmp_id=adjs[i].u;
                    //    }

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
        //choose the next intermediate point
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
}*/

void Model::recordPath(int source,int dest, double w)
{
    ADJ adj(dest,w);
    std::vector<ADJ> adjs=tmppath[source];
    adjs.push_back(adj);
    tmppath[dest]=adjs;
}

void Model::buildMIA()
{
    std::map<int,std::set<ADJ> > tmp_graph;
    std::map<int,std::map<int,std::vector<ADJ> > >::iterator iter=mip.begin();
    while (iter!=mip.end()) {
        std::map<int,std::vector<ADJ> >::iterator iter_path=iter->second.begin();
        while (iter_path!=iter->second.end()) {
            tmp_graph.clear();
            if (mia.count(iter_path->first) && iter_path->second.size()>1) {
                tmp_graph=mia[iter_path->first];
            }
            for (int i=iter_path->second.size()-1; i>=0; i--) {
                if (i-1>=0) {
                	ADJ tadj(iter_path->second[i-1].u,iter_path->second[i].w);
                    tmp_graph[iter_path->second[i].u].insert(tadj);
                }
            }
            if (tmp_graph.size()>0) {
            	mia[iter_path->first]=tmp_graph;
            }
            iter_path++;
        }
        iter++;
    }
    std::map<int,std::map<int,std::set<ADJ> > >::iterator iter1=mia.begin();
    while (iter1!=mia.end()) {
        std::cout<<"current root is "<<node_id_map[iter1->first]<<"_"<<node_net_map[iter1->first]<<std::endl;
        std::map<int,std::set<ADJ> >::iterator iter2=iter1->second.begin();
        while (iter2!=iter1->second.end()) {
            std::cout<<node_id_map[iter2->first]<<"_"<<node_net_map[iter2->first]<<" :\t";
            std::set<ADJ>::iterator iter3=iter2->second.begin();
            while (iter3!=iter2->second.end()) {
                std::cout<<node_id_map[iter3->u]<<"_"<<node_net_map[iter3->u]<<":"<<iter3->w<<"\t";
                iter3++;
            }
            std::cout<<"\n\n"<<std::endl;
            iter2++;
        }
        iter1++;
    }
}

void Model::run()
{
    total_spread=0.0;
    Heap * heap=new Heap(node_id_map,node_net_map,init_seed_spread);
    heap->buildHeap(init_seed_spread);
    for (int i=0; i<SEED_SIZE; i++) {
        HeapNode node=heap->pop(init_seed_spread,1);
        
        
        total_spread+=node.value;
        seedset.insert(node.node);
        
        std::cout<<node_id_map[node.node]<<"_"<<node_net_map[node.node]<<"\t"<<node.value<<std::endl;
        
        while (1)
        {
            heap->heapAdjust(init_seed_spread,0);
            node=heap->pop(init_seed_spread,0);
            if (node.status!=i+1)
            {
                node.value=updateBenefit(node.node,seedset);
                //更新init_seed_spread的值
            }else
            {
                break;
            }
        }
    }
    delete heap;
}


double Model::updateBenefit(int node,std::set<int>seed)
{
    
    std::map<int,double> tmp_inf=miv[node];
    /*if (tmp_inf.size()==1) {
        return 1;
    }else
    {*/
        std::map<int,double>::iterator iter=tmp_inf.begin();
        while (iter!=tmp_inf.end()) {
            std::map<int,std::set<ADJ> > tmp_rtree=mia[iter->first];
            
            iter++;
        }
    //}
    return 0;
}

double Model::ap(int target)
{
    
}

void Model::print(){
    std::map<int,std::map<int,double> >::iterator iter=miv.begin();
    while (iter!=miv.end()) {
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


