//
//  PTree.cpp
//  mnim
//
//  Created by Anika on 6/25/14.
//
//

#include "PTree.h"
TreeNode::TreeNode(NODE cnode,Treenode * p=0)
{
    node=cnode;
    parent=p;
}

void TreeNode::setParent(TreeNode & node)
{
    parent=node;
}
void TreeNode::insertChild(TreeNode & node)
{
    TreeNode *p=&node;
    children.push_back(p);
}

PTree::PTree(NODE root)
{
    this->root=root;
}

PTree::~PTroot()
{}

void PTree::build(std::map<NODE,std::vector<ADJEDGE> > mpp)
{
    std::map<NODE,std::vector<ADJEDGE> >::iterator iter=mpp.begin();
    while (iter!=mpp.end()) {
        
        iter++;
    }
}