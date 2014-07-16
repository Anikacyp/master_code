//
//  Seed.h
//  imms
//
//  Created by Anika on 7/8/14.
//
//

#ifndef __imms__Seed__
#define __imms__Seed__

#include <iostream>
#include <fstream>
#include "Graph.h"
#include "BaseLine.h"
#include "Model.h"
#include "ppTree.h"

class Seed
{
private:
    int type;
    std::vector<int> seeds;
    std::vector<double> spreads;
    std::map<int,int> node_id_map;
    std::map<int,int> node_net_map;
    Graph *graph;
public:
    Seed();
    Seed(std::vector<std::string> files);
    ~Seed();
    void run(int mode);
    void writeToFile(int mode);
    void setVariables();
};
#endif /* defined(__imms__Seed__) */
