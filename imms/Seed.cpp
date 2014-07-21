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
        this->seeds=baseline->getSeed();
        this->spreads=baseline->getSpread();
        delete baseline;
        writeToFile(1);
    }
    //the maximum propagation path method
    if (mode==2) {
        Model *model=new Model(graph);
        model->traversal(2);
        this->seeds=model->getSeed();
        this->spreads=model->getSpread();
    	delete model;
        writeToFile(2);
    }
    
    if (mode==3) {
        writeToFile(3);
    }
    //writeToFile(mode);
}

void Seed::writeToFile(int mode)
{
    std::string fname;
 	if (mode==1){
        fname="greedy.txt";
    }
    if (mode==2){
        fname="mip.txt";
    }
    if (mode==3){
        fname="other.txt";
    }
    //std::cout<<fname<<std::endl;
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
