//
//  Objects.h
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#ifndef __imms__Objects__
#define __imms__Objects__

#include <iostream>
#include <vector>

struct Edge
{
    int u,v;
    double pp;
    Edge(int nu,int nv,double w):u(nu),v(nv),pp(w){}
    Edge(){}
};

struct ADJ
{
    int u;
    double w;
    ADJ(int n,double weight):u(n),w(weight){}
    ADJ(){}
    bool operator<(const ADJ &adj) const{
        return u<adj.u;
    }
    bool operator==(const ADJ &adj) const{
        return ((u==adj.u)&&(w==adj.w));
    }
};

struct HeapNode{
    int node;
    int status;
    double value;
};

/*struct TreeNode
{
    int data;
    std::vector<TreeNode> children;
    std::vector<double> weights;
    TreeNode(){}
    TreeNode(int value):data(value){}
};*/
#endif /* defined(__imms__Objects__) */
