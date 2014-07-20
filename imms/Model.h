//
//  Model.h
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#ifndef __imms__Model__
#define __imms__Model__

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <stdlib.h>
#include "Graph.h"
#include "Objects.h"
#include "limit.h"
#include "Heap.h"

class Model
{
private:
    //graph information & variables
    std::map<int,int> node_id_map;
    std::map<int,int> node_net_map;
    std::map<int,std::set<int> > node_set_map;
    std::map<int,std::vector<ADJ> > adjTable;
    //std::map<int,double> weakCoeff;
    
    //tmp vairables
    std::set<int>tat;
    int current_node;
    std::map<int,double> tmppp;
    std::map<int,std::vector<ADJ> >tmppath;
    std::set<int> tmpS;
    std::set<int> tmpids;
    double spread;
    double total_spread;
    
    //result variables
    std::map<int,std::map<int,double> > miv;
    //最大传播路径
    std::map<int,std::map<int,std::vector<ADJ> > >mip;
    //逆向最大传播路径
    std::map<int,std::map<int,std::set<ADJ> > > mia;
    //初始点的Spread值
    std::vector<HeapNode> init_seed_spread;
    //每个点和其在heap中所对应的位置
    std::map<int,int> heapPos;
    //每个点的Spread值
    std::map<int,double> node_influence;
    //所选的种子集合
    std::set<int> seedset;
    
    //使用最大路径局部传播树计算marginal gain时使用的变量。
    std::map<int,double> aps;
    
    
public:
    Model(Graph *graph);
    Model();
    ~Model();
    void setVariables(Graph *graph);
    
    void traversal(int type);
    void MPP();
    void Dijkstra(int id);
    void recordPath(int source,int dest,double w);
    void buildMIA();
    
	void run();
    double updateBenefit(int node);
    double ap(int root,int child,std::set<int> tmpseed);
    
    void print();
    /*
    int randomNum(int range);
    void spread(int node);*/
};

#endif /* defined(__imms__Model__) */
