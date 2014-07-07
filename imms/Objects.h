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

#endif /* defined(__imms__Objects__) */
