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