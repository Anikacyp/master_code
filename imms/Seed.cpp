//
//  Seed.cpp
//  imms
//
//  Created by Anika on 7/8/14.
//
//

#include "Seed.h"

Seed::Seed(){
	graph=new Graph();
}
Seed::~Seed(){
	delete graph;
}
void Seed::setVariables()
{
    this->node_id_map=graph->getNodeIdMap();
    this->node_net_map=graph->getNodeNetMap();
}

void Seed::run(int mode)
{
    //1 means the greedy algorithm, which is the baseline method
    if (mode==1) {
    	BaseLine *baseline=new BaseLine(graph);
        baseline->run();
        //return results
        delete baseline;
    }
    //propagation tree method
    if (mode==2) {
        
    }
    //the maximum propagation path method
    if (mode==3) {
        
    }
    else
        return;
}

void Seed::writeToFile(int mode)
{
    std::string fname;
 	if (mode==1){
        fname="greedy";
    }
    if (mode==2){
        fname="ptree";
    }
    if (mode==3){
        fname="mip";
    }
    else
        return;
    std::ofstream ofile;
    ofile.open(fname.c_str());
    if (ofile) {
        for (int i=0; i<seeds.size(); i++) {
            ofile<<seeds[i]<<"\n";
        }
    }else
    {
        std::cout<<"fail to open "<<fname<<std::endl;
    }
}
