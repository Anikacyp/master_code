//
//  ppTree.cpp
//  imms
//
//  Created by Anika on 7/8/14.
//
//

#include "ppTree.h"

ppTree::ppTree(Model * model)
{
	setVariables(model);
}

ppTree::ppTree(){}

ppTree::~ppTree(){}


void ppTree::setVariables(Model *model)
{
    this->miv=model->getMiv();
    this->mip=model->getMip();
}

void ppTree::buildTree()
{
    std::map<int,std::map<int,double> >::iterator iter=miv.begin();
    while (iter!=miv.end()) {
        double spread_value=0.0;
        std::map<int,double> inf_nodes=iter->second;
        std::map<int,double>::iterator iter_inner=inf_nodes.begin();
        std::map<int,std::vector<ADJ> > adjacent=mip[iter->first];
        while (iter_inner!=inf_nodes.end()) {
            spread_value+=iter_inner->second;
            iter_inner++;
        }
        nodeSpread[iter->first]=spread_value;
        iter++;
    }
}
