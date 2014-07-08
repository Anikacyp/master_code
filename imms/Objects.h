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
};

struct HeapNode{
    int node;
    int status;
    double value;
};

struct TreeNode
{
    int node;
    std::vector<int> children;
    int parent;
    double weight;
};
#endif /* defined(__imms__Objects__) */
