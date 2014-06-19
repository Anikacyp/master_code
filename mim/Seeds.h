//
//  Seeds.h
//  mnim
//
//  Created by Anika on 6/18/14.
//
//

#ifndef SEEDS__H
#define SEEDS__H
#include <map>
#include <vector>
#include <iostream>
#include "Graph.h"



class Seeds{
private:
    std::map<Node,std::map<Node,double> > infValue;
    std::map<node,std::map<Node,std::vector<EdgeNode> > > infPath;
    
public:
    
};

#endif /* defined(__mnim__Seeds__) */
