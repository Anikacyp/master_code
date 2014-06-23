//
//  HBI.cpp
//  mnim
//
//  Created by Anika on 6/20/14.
//

#include "HBI.h"

HBI::HBI()
{
    nodes.clear();
    Graph * graph=new Graph();
    graph->fileInput();
    graph->graphBuilding();
    this->nodes=graph->getNodes();
    this->adjTable=graph->getAdjTable();
    this->nodenet=graph->getNodeNet();
    randominf();
    delete graph;
}


HBI::~HBI(){}


void HBI::traversal()
{
    std::set<int>::iterator iter=nodes.begin();
    while (iter!=nodes.end()) {
        //intialize the variable as null
        nodeStatus.clear();
        Can.clear();
        tmpinf.clear();
        tmpGinf.clear();
        
        //path record
        tmppath.clear();
        
        synICM(*iter);
        
        GlobalInf[*iter]=tmpGinf;
        GIP[*iter]=tmppath;
        
        iter++;
    }
    print();
}

void HBI::synICM(int node)
{
    tmpGinf[node]=1;
    
    //std::map<NODE,double> tmpinf;
    std::set<int> tnet=nodenet[node];
    std::set<int>::iterator iter=tnet.begin();
    while (iter!=tnet.end()) {
        NODE tn(node,*iter);

        Can.insert(tn);
        tmpinf[tn]=1;
        nodeStatus[tn]=1;
        tmpGinf[node]=0;
        
        //record the influence propagation path
        //--------------------------------------
        pathRecord(tn,tn,1.0);
        //--------------------------------------
        iter++;
    }
    //initialize
    spreadICM(Can);
}

void HBI::spreadICM(std::set<NODE> can)
{
    std::set<NODE> tCan;
    std::set<NODE>::iterator iter=can.begin();
    while (iter!=can.end())
    {
        if(adjTable.count(*iter))
        {
            std::vector<ADJEDGE> tadj=adjTable[*iter];
            for (int i=0; i<tadj.size(); i++)
            {
                double tval=tmpinf[*iter]*(tadj[i].weight);
                
                if (tval>=THETA) {
                    if (!nodeStatus.count(tadj[i].dest))
                    {
                        //std::cout<<iter->node_id<<"_"<<iter->net_id<<"\t"<<tadj[i].dest.node_id<<"_"<<tadj[i].dest.net_id<<"\t"<<tval<<std::endl;
                        if (tmpGinf.count(tadj[i].dest.node_id))
                        {
                            if ((*iter).node_id==tadj[i].dest.node_id)
                            {
                                tmpinf[tadj[i].dest]=tval;
                                tCan.insert(tadj[i].dest);
                                nodeStatus[tadj[i].dest]=1;
                                tmpGinf[tadj[i].dest.node_id]*=(1-tval);
                                pathRecord(*iter,tadj[i].dest,tadj[i].weight);
                                //std::cout<<"nodeStatus暂不包含 "<<tadj[i].dest.node_id<<"_"<<tadj[i].dest.net_id<<" 并且tmpGinf包含"<<tadj[i].dest.node_id<<"\t自身传播\t"<<tmpGinf[tadj[i].dest.node_id]<<std::endl;
                            }else
                            {
                                tval*=naive[tadj[i].dest.node_id];
                                if (tval>=THETA)
                                {
                                    tmpinf[tadj[i].dest]=tval;
                                    tCan.insert(tadj[i].dest);
                                    nodeStatus[tadj[i].dest]=1;
                                    tmpGinf[tadj[i].dest.node_id]*=(1-tval);
                                    pathRecord(*iter,tadj[i].dest,tadj[i].weight*naive[tadj[i].dest.node_id]);
                                    //std::cout<<"nodeStatus暂不包含 "<<tadj[i].dest.node_id<<"_"<<tadj[i].dest.net_id<<" 并且tmpGinf包含"<<tadj[i].dest.node_id<<"\t非自身传播\t"<<tval<<"\t"<<tmpGinf[tadj[i].dest.node_id]<<std::endl;
                                }
                            }
                        }else
                        {
                            tmpinf[tadj[i].dest]=tval;
                            tCan.insert(tadj[i].dest);
                            nodeStatus[tadj[i].dest]=1;
                            tmpGinf[tadj[i].dest.node_id]=(1-tval);
                            pathRecord(*iter,tadj[i].dest,tadj[i].weight);
                            //std::cout<<"nodeStatus暂不包含 "<<tadj[i].dest.node_id<<"_"<<tadj[i].dest.net_id<<" 并且tmpGinf不包含"<<tadj[i].dest.node_id<<"\t非自身传播\t"<<tmpGinf[tadj[i].dest.node_id]<<std::endl;
                        }
                    }
                    /*if (!nodeStatus.count(tadj[i].dest))
                    {
                        std::cout<<iter->node_id<<"_"<<iter->net_id<<"\t"<<tadj[i].dest.node_id<<"_"<<tadj[i].dest.net_id<<"\t"<<tval<<std::endl;
                        tmpinf[tadj[i].dest]=tval;
                        tCan.insert(tadj[i].dest);
                        
                        //turn the node to active status.
                        nodeStatus[tadj[i].dest]=1;
                        
                        if (!tmpGinf.count(tadj[i].dest.node_id))
                        {
                            tmpGinf[tadj[i].dest.node_id]=(1-tval);
                            std::cout<<"nodeStatus暂不包含 "<<tadj[i].dest.node_id<<"_"<<tadj[i].dest.net_id<<" 并且tmpGinf也不包含"<<tadj[i].dest.node_id<<"\t"<<tmpGinf[tadj[i].dest.node_id]<<std::endl;
                        }
                        else
                        {
                            tmpGinf[tadj[i].dest.node_id]*=(1-tval);
                            std::cout<<"nodeStatus暂不包含 "<<tadj[i].dest.node_id<<"_"<<tadj[i].dest.net_id<<" 但是tmpGinf包含"<<tadj[i].dest.node_id<<"\t"<<tmpGinf[tadj[i].dest.node_id]<<std::endl;
                        }
                    }*/
                   /* else
                    {
                        if (nodeStatus[tadj[i].dest]==1)
                        {
                            tmpGinf[tadj[i].dest.node_id]*=(1-tval);
                            std::cout<<"nodeStatus包含 "<<tadj[i].dest.node_id<<"_"<<tadj[i].dest.net_id<<" 并且tmpGinf也包含"<<tadj[i].dest.node_id<<"\t"<<tmpGinf[tadj[i].dest.node_id]<<std::endl;
                        }
                    }*/
                }
            }
        }
        //means the node has been activated.
        nodeStatus[*iter]=2;
        iter++;
    }
    if (tCan.size()>0) {
        spreadICM(tCan);
    }else
        return;
}


void HBI::randominf()
{
    std::srand(unsigned(time(0)));
    double tval=0.0;
    std::set<int>::iterator iter=nodes.begin();
    while (iter!=nodes.end()) {
        tval=std::rand()/(double)(RAND_MAX);
        naive[*iter]=tval;
        std::cout<<*iter<<"\t"<<tval<<std::endl;
        iter++;
    }
}

void HBI::pathRecord(NODE parent, NODE child, double w)
{
    std::vector<ADJEDGE> path;
    infPath ip;
    ADJEDGE adje;
    adje.dest=child;
    adje.weight=w;
    if (!tmppath.count(parent)) {
        if (parent==child) {
            path.clear();
            path.push_back(adje);
            
            ip.path=path;
            ip.pp=w;
            
            tmppath[child]=ip;
        }
    }else
    {
        ip=tmppath[parent];
        ip.path.push_back(adje);
        ip.pp*=w;
        tmppath[child]=ip;
    }
}

void HBI::print()
{
    //
    std::cout<<"result-----------------pp---------------------"<<std::endl;
    std::map<int,std::map<int,double> >::iterator iter=GlobalInf.begin();
    while (iter!=GlobalInf.end()) {
        std::map<int,double>::iterator titer=iter->second.begin();
        while (titer!=iter->second.end()) {
            std::cout<<iter->first<<"\t"<<titer->first<<"\t"<<1-titer->second<<std::endl;
            titer++;
        }
        iter++;
    }
    //
    std::cout<<"result-----------------path---------------------"<<std::endl;
    std::map<int,std::map<NODE,infPath> >::iterator iter2=GIP.begin();
    while (iter2!=GIP.end()) {
        std::cout<<"current propagation path of node "<<iter2->first<<std::endl;
        std::map<NODE,infPath>::iterator piter=iter2->second.begin();
        while (piter!=iter2->second.end()) {
            std::cout<<piter->first.node_id<<"_"<<piter->first.net_id<<":\t";
            std::vector<ADJEDGE> adjs=piter->second.path;
            std::vector<ADJEDGE>::iterator aiter=adjs.begin();
            while (aiter!=adjs.end()) {
                std::cout<<aiter->dest.node_id<<"_"<<aiter->dest.net_id<<"("<<aiter->weight<<")\t";
                aiter++;
            }
            std::cout<<"\tPP:\t"<<piter->second.pp<<std::endl;
            piter++;
        }
        std::cout<<std::endl;
        iter2++;
    }
    
}

void HBI::asynICM(NODE node)
{
    
}

