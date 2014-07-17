//
//  ppTree.h
//  imms
//
//  Created by Anika on 7/8/14.
//
//

#ifndef __imms__ppTree__
#define __imms__ppTree__

#include <iostream>
#include <vector>
#include <map>
#include "Model.h"
#include "Objects.h"


class ppTree
{
private:
    //std::map<int,double> nodeSpread;
    std::map<int,std::map<int,double> > miv;
    std::map<int,std::map<int,std::vector<ADJ> > >mip;
    std::map<int,int> node_id_map;
    std::map<int,int> node_net_map;
    std::map<int,TreeNode> mia;
    std::map<int,TreeNode> moa;
public:
    ppTree();
    ppTree(Model *model);
    ~ppTree();
    void buildTree();
    void setVariables(Model *model);
};

#endif /* defined(__imms__ppTree__) */
