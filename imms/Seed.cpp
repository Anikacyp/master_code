//
//  Seed.cpp
//  imms
//
//  Created by Anika on 7/8/14.
//
//

#include "Seed.h"

Seed::Seed(std::vector<std::string> files){
	graph=new Graph(files);
    graph->buildGraph();
    setVariables();
    //std::map<int,int>::iterator iter=this->node_id_map.begin();
    //std::cout<<"total node number: "<<this->node_id_map.size()<<std::endl;
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
        this->seeds=baseline->getSeed();
        this->spreads=baseline->getSpread();
        delete baseline;
    }
    //propagation tree method
    if (mode==2) {
        Model *model=new Model(graph);
        ppTree *ptree=new ppTree(model);
       	
        delete ptree;
    	delete model;
    }
    //the maximum propagation path method
    if (mode==3) {
    }
    writeToFile(mode);
}

void Seed::writeToFile(int mode)
{
    std::string fname;
 	if (mode==1){
        fname="greedy.txt";
    }
    if (mode==2){
        fname="ptree.txt";
    }
    if (mode==3){
        fname="mip.txt";
    }
    std::cout<<fname<<std::endl;
    std::ofstream ofile;
    ofile.open(fname.c_str());
    if (ofile) {
        for (int i=0; i<seeds.size(); i++) {
            ofile<<seeds[i]<<"\t"<<node_id_map[seeds[i]]<<"\t"<<node_net_map[seeds[i]]<<"\t"<<spreads[i]<<"\n";
        }
    }else
    {
        std::cout<<"fail to open "<<fname<<std::endl;
    }
}
