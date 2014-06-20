//
//  BaseObj.h
//  mnim
//
//  Created by Anika on 6/19/14.
//
//
#ifndef BASEOBJ__H
#define BASEOBJ__H

struct NODE
{
    int node_id;
    int net_id;
    //overload the operator < and ==
    bool operator <(const NODE & other) const{
        if(other.node_id==node_id)
            return net_id<other.net_id;
        return node_id<other.node_id;
    }
    bool operator == (const NODE & other) const{
        return (node_id==other.node_id)&&(net_id==other.net_id);
    }
    
    //constructor
    NODE(int nid,int ntid):node_id(nid),net_id(ntid){}
    //NODE(NODE& node):node_id(node.node_id),net_id(node.net_id){}
    NODE(){}
};

struct EDGE
{
    NODE u,v;
    double weight;
};


struct ADJEDGE
{
    NODE dest;
    double weight;
    //ADJEDGE(NODE& node,double w):dest(node),weight(w){}
};


struct NetPair
{
    int net1;
    int net2;
    //double weight;
    bool operator <(const NetPair& other) const{
        if(other.net1==net1)
            return net2<other.net2;
        return net1<other.net1;
    }
    bool operator ==(const NetPair& other) const{
        return (net1==other.net1) &&(net2==other.net2);
    }
    NetPair(){}
    NetPair(int n1,int n2):net1(n1),net2(n2){}
    //NETIF(NETIF& nif):net1(nif.net1),net2(nif.net2){}
};


struct NodeInfPair
{
    NODE dest;
    double pp;
    std::vector<std::vector<NODE> > paths;
};

#endif