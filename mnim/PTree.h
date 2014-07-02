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
#include <list>

/*struct TreeNode
{
    NODE node;
    TreeNode * parent;
    std::list<TreeNode *> children;
    //pp means the propagation from parent to the current node
    double pp;
    //active dedicates whether current node has been selected as seed node
    bool active;
    
    TreeNode(NODE cnode, TreeNode *){}
    void insertChild(Treenode &);
    void setParent(Treenode &);
};*/

class PTree{
private:
    NODE root;
public:
    PTree();
    ~PTree();
    void build(std::map<NODE,std::map<NODE,std::vector<ADJEDGE> > > mpp);
};

#endif /* defined(__mnim__PTree__) */
