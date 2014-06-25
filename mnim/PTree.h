//
//  PTree.h
//  mnim
//
//  Created by Anika on 6/25/14.
//
//

#ifndef __mnim__PTree__
#define __mnim__PTree__

#include <iostream>
#include "BaseObj.h"
#Include <list>

struct TreeNode
{
    NODE node;
    TreeNode * parent;
    std::list<TreeNode *> children;
    //pp means the propagation from parent to the current node
    double pp;
    TreeNode(NODE cnode, TreeNode *){}
    void insertChild(Treenode &);
    void setParent(Treenode &);
    
};


class PTree{
    
};

#endif /* defined(__mnim__PTree__) */
