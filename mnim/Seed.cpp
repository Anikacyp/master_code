//
//  Seed.cpp
//  mnim
//
//  Created by Anika on 6/23/14.
//
//

#include "Seed.h"

Seed::Seed(){
    
}

Seed::Seed(int mode)
{
    this->mode=mode;
    if(mode==1 || mode==2 || mode==3)
    {
        Model *model=new Model(mode);
        model->spread();
        setVariables(model);
        buildMIA();
        delete model;
    }
}

Seed::~Seed(){}

void Seed::setHeapData()
{
    if (mode==1) {
        std::map<int,std::map<int,double> >::iterator iter=GlobalInf.begin();
        while (iter!=GlobalInf.end()) {
            NODE tn(iter->first,0);
            HeapNode hnode;
            double sumval=0.0;
            hnode.node=tn;
            std::map<int,double>::iterator iterinner=iter->second.begin();
            while (iterinner!=iter->second.end()) {
                sumval+=iterinner->second;
                iterinner++;
            }
            heapData.push_back(hnode);
            iter++;
        }
    }
    if (mode==2) {
        std::map<NODE,std::map<int,double> >::iterator iter=GlobalAsynInf.begin();
        while (iter!=GlobalAsynInf.end()) {
            HeapNode hnode;
            double sumval=0.0;
            hnode.node=iter->first;
            std::map<int,double>::iterator iterinner=iter->second.begin();
            while (iterinner!=iter->second.end()) {
                sumval+=iterinner->second;
                iterinner++;
            }
            heapData.push_back(hnode);
            iter++;
        }
    }
    if (mode==3) {
        std::map<NODE,std::map<NODE,double> >::iterator iter=mppInf.begin();
        while (iter!=mppInf.end()) {
            HeapNode hnode;
            double sumval=0.0;
            hnode.node=iter->first;
            std::map<NODE,double>::iterator iterinner=iter->second.begin();
            while (iterinner!=iter->second.end()) {
                sumval+=iterinner->second;
                iterinner++;
            }
            heapData.push_back(hnode);
            iter++;
        }
    }
}

void Seed::setVariables(Model * model)
{
    //variables for synchronous propagation process
    if (this->mode==1) {
        GlobalInf=model->getGlobalInf();
        GIP=model->getGIP();
    }
    
    //variables for asynchronous propagation process
    if (this->mode==2) {
       GlobalAsynInf=model->getGlobalAsynInf();
       GIPAsyn=model->getGIPAsyn();
    }
    
    //variables for maximum propagation path
    if(this->mode==3)
    {
        mpp=model->getMpp();
        mppInf=model->getMppInf();
    }
}


void Seed::buildMIA()
{
    std::map<NODE,std::map<NODE,std::vector<ADJEDGE> > > intree;
    if (this->mode==1) {
        /*std::map<int,std::map<NODE,infPath> >::iterator iter=GIP.begin;
        while (iter!=GIP.end()) {
            std::map<NODE,infPath>::iterator iter1=iter->second.begin();
            while (iter1!=iter->second.end()) {
                if (intree.count(iter1->first)) {
                    if (!intree[iter1->first].count(iter->first)) {
                        intree[iter1->first][iter->first]=iter1->second.path;
                    }
                }else
                {
                    intree[iter1->first][iter->first]=iter1->second.path;
                }
                iter1++;
            }
            iter++;
        }*/
    }
    if (this->mode==2) {
        std::map<NODE,std::map<NODE,infPath> >::iterator iter=GIPAsyn.begin();
        while (iter!=GIPAsyn.end()) {
            std::map<NODE,infPath>::iterator iter1=iter->second.begin();
            while (iter1!=iter->second.end()) {
                if (intree.count(iter1->first)) {
                    if (!intree[iter1->first].count(iter->first)) {
                        intree[iter1->first][iter->first]=iter1->second.path;
                    }
                }else
                {
                    intree[iter1->first][iter->first]=iter1->second.path;
                }
                iter1++;
            }
            iter++;
        }
    }
    if (this->mode==3) {
        
        std::map<NODE,std::map<NODE,std::vector<ADJEDGE> > >::iterator iter=mpp.begin();
        while (iter!=mpp.end()) {
            std::map<NODE,std::vector<ADJEDGE> >::iterator iter1=iter->second.begin();
			while (iter1!=iter->second.end()) {
                
                if (intree.count(iter1->first)) {
                    if (!intree[iter1->first].count(iter->first)) {
                        intree[iter1->first][iter->first]=iter1->second;
                    }
                }else
                {
                    intree[iter1->first][iter->first]=iter1->second;
                }
                iter1++;
            }
            iter++;
        }
        std::cout<<"total size: "<<intree.size()<<std::endl;
    }
}


void Seed::topkSeed()
{
    
}



