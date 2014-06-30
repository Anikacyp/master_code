//
//  Model.cpp
//  mnim
//
//  Created by Anika on 6/20/14.
//

#include "Model.h"
Model::Model(int mode)
{
    this->mode=mode;
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


Model::~Model(){}

void Model::randominf()
{
    std::srand(unsigned(time(0)));
    double tval=0.0;
    std::set<int>::iterator iter=nodes.begin();
    while (iter!=nodes.end()) {
        tval=std::rand()/(double)(RAND_MAX);
        //tval=0.9;
        naive[*iter]=tval;
        std::cout<<*iter<<"\t"<<tval<<std::endl;
        iter++;
    }
}

void Model::spread()
{
    if (mode==1) {
        traversal(1);
    }
    if (mode==2) {
        traversal(2);
    }
    if (mode==3) {
        MPPinf();
        printMpp();
    }
}

void Model::traversal(int flag)
{
    std::set<int>::iterator iter=nodes.begin();
    while (iter!=nodes.end()) {
        if (flag==1) {
            //intialize the variable as empty
            nodeStatus.clear();
            Can.clear();
            tmpinf.clear();
            tmpGinf.clear();
            //path record
            tmppath.clear();
            
            synICM(*iter);
            GlobalInf[*iter]=tmpGinf;
            GIP[*iter]=tmppath;
        }else
        {
            asynICM(*iter);
        }
        iter++;
    }
    /*if (flag==1)
        print(1);
    else
        print(2);*/
}

//syncICM treat the nodes which has the same node_id were activated at the same time.
void Model::synICM(int node)
{
    tmpGinf[node]=1;
    
    std::set<int> tnet=nodenet[node];
    std::set<int>::iterator iter=tnet.begin();
    while (iter!=tnet.end()) {
        NODE tn(node,*iter);

        Can.insert(tn);
        tmpinf[tn]=1;
        nodeStatus[tn]=1;
        tmpGinf[node]=0;
        
        //record the influence propagation path
        pathRecord(tn,tn,1.0);

        iter++;
    }
    //propagation simulate
    SpreadICM(Can);
}

//asynICM treats the nodes which has the same node_id were randomly activated
void Model::asynICM(int node)
{
    std::set<int> tnet=nodenet[node];
    std::set<int>::iterator iter=tnet.begin();
    while (iter!=tnet.end()) {
        NODE tn(node,*iter);
        
        //initialize:
        nodeStatus.clear();
        Can.clear();
        tmpinf.clear();
        tmpGinf.clear();
        tmppath.clear();
        
        Can.insert(tn);
        tmpinf[tn]=1;
        tmpGinf[node]=0;
        pathRecord(tn,tn,1.0);
        
        SpreadICM(Can);
        
        GlobalAsynInf[tn]=tmpGinf;
        GIPAsyn[tn]=tmppath;
        
        iter++;
    }
    
}

void Model::SpreadICM(std::set<NODE> can)
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
                        if (tmpGinf.count(tadj[i].dest.node_id))
                        {
                            if ((*iter).node_id==tadj[i].dest.node_id)
                            {
                                tmpinf[tadj[i].dest]=tval;
                                tCan.insert(tadj[i].dest);
                                nodeStatus[tadj[i].dest]=1;
                                tmpGinf[tadj[i].dest.node_id]*=(1-tval);
                                pathRecord(*iter,tadj[i].dest,tadj[i].weight);
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
                }
            }
        }
        //means the node has been activated.
        nodeStatus[*iter]=2;
        iter++;
    }
    if (tCan.size()>0) {
        SpreadICM(tCan);
    }else
        return;
}

//using the maximum propagation path as the approximately influence propagation value
void Model::MPPinf()
{
    std::set<int>::iterator iter=nodes.begin();
    while (iter!=nodes.end()) {
        if(nodenet.count(*iter))
        {
            std::set<int>::iterator iter1=nodenet[*iter].begin();
            while (iter1!=nodenet[*iter].end()) {
                
                tmpp.clear();
                tmval.clear();
                cans.clear();
                cain.clear();
                
                NODE node(*iter,*iter1);
                current_node=node;
                
                if (!mpp.count(node)) {
                    
                    //record the influence path;
                    ADJEDGE tadj;
                    tadj.dest=node;
                    tadj.weight=1;
                    tmpp[node].push_back(tadj);
                    tmval[node]=1;
                    cain.insert(node.node_id);
                }
                Dijkstra(node);
                infval[node]=tmval;
                mpp[node]=tmpp;
                //break;
                iter1++;
            }
        }
        //break;
        iter++;
    }
   // printMpp();
}

//using maximum propagation probability as the probability which calculated by the dijkstra algorithm
void Model::Dijkstra(NODE source)
{
    //std::cout<<"current middle node: "<<source.node_id<<"_"<<source.net_id<<std::endl;
    cans.insert(source);
    cain.insert(source.node_id);
    std::vector<ADJEDGE> tmpadjs=adjTable[source];
    
    double tp=tmval[source];
    
    NODE next;
    double tval=0.0;
    double tvalue=0.0;
    bool flag=false;
    //bool t1=false;
    //bool t2=false;
    
    
    for (int i=0; i<tmpadjs.size(); i++)
    {
        ADJEDGE tedge=tmpadjs[i];
        if (!cans.count(tedge.dest))
        {
            //t1=false;
            //t2=false;
            tvalue=tp*tedge.weight;
            
            if (tvalue>THETA)
            {
                if (!tmpp.count(tedge.dest))
                {
                    if (cain.count(tedge.dest.node_id)) {
                        if (source.node_id!=tedge.dest.node_id) {
                            tvalue*=naive[tedge.dest.node_id];
                            //t1=true;
                            
                        }
                    }
                    if (tvalue>THETA) {
                        /*if (t1) {
                            std::cout<<"不包含---"<<tedge.dest.node_id<<"_"<<tedge.dest.net_id<<"\t但包含"<<tedge.dest.node_id<<"\t"<<tvalue<<std::endl;
                        }*/
                        tmpp[tedge.dest]=tmpp[source];
                        tmpp[tedge.dest].push_back(tedge);
                        tmval[tedge.dest]=tvalue;
                    }
                    /*if(!cain.count(tedge.dest.node_id))
                    {
                        
                        //std::cout<<"不包含---"<<tedge.dest.node_id<<"_"<<tedge.dest.net_id<<"\t"<<tvalue<<std::endl;
                    }else
                    {
                        if (source.node_id!=tedge.dest.node_id) {
                            tvalue*=naive[tedge.dest.node_id];
                        }
                        if (tvalue>THETA) {
                            tmpp[tedge.dest]=tmpp[source];
                            tmpp[tedge.dest].push_back(tedge);
                            tmval[tedge.dest]=tvalue;
                            //std::cout<<"包含---"<<tedge.dest.node_id<<"_"<<tedge.dest.net_id<<"\t"<<tvalue<<std::endl;
                        }
                    }*/
                    
                }else
                {
                    
                    if (cain.count(tedge.dest.node_id)) {
                        if (source.node_id!=tedge.dest.node_id) {
                            tvalue*=naive[tedge.dest.node_id];
                            //t2=true;
                            
                        }
                    }
                    
                    if((tvalue>THETA)&&(tvalue>tmval[tedge.dest]))
                    {
                        /*if (t2) {
                            std::cout<<"包含---"<<tedge.dest.node_id<<"_"<<tedge.dest.net_id<<"\t也包含"<<tedge.dest.node_id<<"\t"<<tvalue<<std::endl;
                        }*/
                        tmpp[tedge.dest]=tmpp[source];
                        tmpp[tedge.dest].push_back(tedge);
                        tmval[tedge.dest]=tvalue;
                    }
                    /*if (cain.count(tedge.dest.node_id)) {
                        if (source.node_id!=tedge.dest.node_id) {
                            tvalue*=naive[tedge.dest.node_id];
                        }
                        if((tvalue>THETA)&&(tvalue>tmval[tedge.dest]))
                        {
                            std::cout<<"包含点---"<<tedge.dest.node_id<<"_"<<tedge.dest.net_id<<"\t"<<tvalue<<std::endl;
                            tmpp[tedge.dest]=tmpp[source];
                            tmpp[tedge.dest].push_back(tedge);
                            tmval[tedge.dest]=tvalue;
                        }
                    }else
                    {
                        
                        tmpp[tedge.dest]=tmpp[source];
                        tmpp[tedge.dest].push_back(tedge);
                        tmval[tedge.dest]=tvalue;
                        cain.insert(tedge.dest.node_id);
                        std::cout<<"不包含---"<<tedge.dest.node_id<<"_"<<tedge.dest.net_id<<"\t"<<tvalue<<std::endl;
                    }*/
                }
            }
        }
    }
    
    std::map<NODE,double>::iterator iter=tmval.begin();
    while (iter!=tmval.end()) {
        if (!cans.count(iter->first)) {
            if (tval<iter->second) {
                tval=iter->second;
                next=iter->first;
                flag=true;
            }
        }
        iter++;
    }
    if (flag) {
        Dijkstra(next);
    }else
        return;
}

//record the propagation path. which mainly record the path based on the hop process
void Model::pathRecord(NODE parent, NODE child, double w)
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

void Model::print(int flag)
{
    //
    double value=0.0;
    if (flag==1) {
        std::cout<<"result-----------------pp---------------------"<<std::endl;
        std::map<int,std::map<int,double> >::iterator iter=GlobalInf.begin();
        while (iter!=GlobalInf.end()) {
            value=0.0;
            std::map<int,double>::iterator titer=iter->second.begin();
            while (titer!=iter->second.end()) {
                value+=(1-titer->second);
                std::cout<<iter->first<<"\t"<<titer->first<<"\t"<<1-titer->second<<std::endl;
                titer++;
            }
            std::cout<<"    ("<<iter->first<<"\t"<<value<<")     \n\n"<<std::endl;
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
    }else
    {
        std::cout<<"result-----------------pp---------------------"<<std::endl;
        std::map<NODE,std::map<int,double> >::iterator iter=GlobalAsynInf.begin();
        while (iter!=GlobalAsynInf.end()) {
            value=0.0;
            std::map<int,double>::iterator titer=iter->second.begin();
            while (titer!=iter->second.end()) {
                value+=(1-titer->second);
                std::cout<<iter->first.node_id<<"_"<<iter->first.net_id<<"\t"<<titer->first<<"\t"<<1-titer->second<<std::endl;
                titer++;
            }
            std::cout<<"     ("<<iter->first.node_id<<"_"<<iter->first.net_id<<"\t"<<value<<")     \n\n"<<std::endl;
            //std::cout<<"------------------------"<<std::endl;
            iter++;
        }
        //
        std::cout<<"result-----------------path---------------------"<<std::endl;
        std::map<NODE,std::map<NODE,infPath> >::iterator iter2=GIPAsyn.begin();
        while (iter2!=GIPAsyn.end()) {
            std::cout<<"current propagation path of node "<<iter2->first.node_id<<"_"<<iter2->first.net_id<<std::endl;
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
}


void Model::printMpp()
{
    std::map<NODE,std::map<NODE,double> >::iterator iter=infval.begin();
    while (iter!=infval.end()) {
        std::map<NODE,double>::iterator iter1=iter->second.begin();
        double sum=0.0;
        while (iter1!=iter->second.end()) {
            std::cout<<iter->first.node_id<<"_"<<iter->first.net_id<<"\t"<<iter1->first.node_id<<"_"<<iter1->first.net_id<<"\t"<<iter1->second<<std::endl;
            std::vector<ADJEDGE> path=mpp[iter->first][iter1->first];
            for (int i=0; i<path.size(); i++) {
                std::cout<<path[i].dest.node_id<<"_"<<path[i].dest.net_id<<" ("<<path[i].weight<<")\t";
            }
            std::cout<<"\n"<<std::endl;
            sum+=iter1->second;
            iter1++;
        }
        std::cout<<iter->first.node_id<<"_"<<iter->first.net_id<<"\t"<<sum<<std::endl;
        iter++;
    }
}


//return variables like propagation probability between nodes and the propagation path between nodes
std::map<int,std::map<int,double> > Model::getGlobalInf()
{
    return GlobalInf;
}
std::map<int,std::map<NODE,infPath> > Model::getGIP()
{
    return GIP;
}
//variables for asynchronous propagation process
std::map<NODE,std::map<int,double> > Model::getGlobalAsynInf()
{
    return GlobalAsynInf;
}
std::map<NODE,std::map<NODE,infPath> > Model::getGIPAsyn()
{
    return GIPAsyn;
}
//variables for maximum propagation path
std::map<NODE,std::map<NODE,std::vector<ADJEDGE> > > Model::getMpp()
{
    return mpp;
}
std::map<NODE,std::map<NODE,double> > Model::getMppInf()
{
    return infval;
}

