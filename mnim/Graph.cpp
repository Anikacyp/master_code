//
//  Graph.cpp
//  mnim
//
//  Created by Anika on 6/19/14.
//
//

#include "Graph.h"

std::vector<EDGE> Graph::edges;
std::map<NODE,std::vector<ADJEDGE> > Graph::adjTable;
std::map<NetPair,double> Graph::netifmap;
std::set<int> Graph::nodes;
std::map<int,std::set<int> > Graph::netnodes;
std::map<int,std::set<int> > Graph::nodenet;

Graph::Graph(){
}
Graph::~Graph(){}

void Graph::fileInput()
{
    std::cout<<"network number"<<std::endl;
    std::cin>>network_NO;
    std::string file("");
    for (int i=0; i<network_NO; i++) {
        std::cout<<"please input the file of "<<i+1<<"th network"<<std::endl;
        std::cin>>file;
        files.push_back(file);
    }
    
    /*if (this->network_NO>1)
    {
        for (int i=1; i<=network_NO; i++)
        {
            int j=1;
            while (j<=this->network_NO)
            {
                if(i!=j)
                {
                    NetPair np(i,j);
                    std::cout<<"please input the influence of network "<<i<<" to network "<<j<<std::endl;
                    std::cin>>netifmap[np];
                }
                j++;
            }
        }
    }*/
    graphBuilding();
    std::cout<<"node number: "<<nodes.size()<<std::endl;
}


void Graph::nodeIntraInf()
{
    std::srand(unsigned(time(0)));
    double tval=0.0;
    std::set<int>::iterator iter=nodes.begin();
    while (iter!=nodes.end()) {
        tval=std::rand()/(double)(RAND_MAX);
        iin[*iter]=tval;
        iter++;
    }
}


void Graph::graphBuilding()
{
    
    /*图存储格式，node1   node2   w1  w2
     其中w1表示边node1->node2的权重，即点node1对node2的影响值
     而w2表示边node2->node1的权重，即点node2对点node1的影响值
     */
    std::ifstream ifile;
    NODE u,v;
    int nu,nv;
    double w1,w2;
    std::set<int> tnode;
    for (int i=0; i<files.size(); i++) {
        ifile.open(files[i].c_str(),std::istream::in);
        if(ifile)
        {
            tnode.clear();
            while(!ifile.eof())
            {
                ifile>>nu>>nv>>w1>>w2;
                //std::cout<<nu<<"\t"<<nv<<"\t"<<w1<<"\t"<<w2<<std::endl;
                u.node_id=nu;
                u.net_id=i+1;
                v.node_id=nv;
                v.net_id=i+1;
                
                
                nodes.insert(nu);
                nodes.insert(nv);
                tnode.insert(nu);
                tnode.insert(nv);
                nodenet[nu].insert(i+1);
                nodenet[nv].insert(i+1);
                
                EDGE edge;
                if(w1>0)
                {
                    edge.u=u;
                    edge.v=v;
                    edge.weight=w1;
                    edges.push_back(edge);
                    adjacentTable(u,v,w1);
                }if (w2>0)
                {
                    edge.u=v;
                    edge.v=u;
                    edge.weight=w2;
                    edges.push_back(edge);
                    adjacentTable(v,u,w2);
                }
            }
            
            netnodes[i+1]=tnode;
        }
        ifile.close();
    }
    
    nodeIntraInf();
    netinfGraph();
}

void Graph::netinfGraph()
{
    
    
    for (int i=1; i<=this->network_NO; i++) {
        for (int j=1; j<=this->network_NO; j++) {
            if (i!=j) {
                /*NetPair np;
                np.net1=i;
                np.net2=j;
                double w1=netifmap[np];*/
                
                
                std::set<int> nodenet1=netnodes[i];
                std::set<int> nodenet2=netnodes[j];
                
                std::set<int>::iterator iter=nodenet1.begin();
                while (iter!=nodenet1.end()) {
                    if (nodenet2.count(*iter)) {
                        NODE n1,n2;
                        EDGE edge;
                        n1.node_id=*iter;
                        n1.net_id=i;
                        n2.node_id=*iter;
                        n2.net_id=j;
                        double w1=iin[*iter];
                        if(w1>0)
                        {
                            edge.u=n1;
                            edge.v=n2;
                            edge.weight=w1;
                            edges.push_back(edge);
                            adjacentTable(n1,n2,w1);
                        }
                    }
                    iter++;
                }
                
            }
        }
    }
}

void Graph::adjacentTable(NODE n1, NODE n2, double w)
{
    ADJEDGE adje;
    adje.dest=n2;
    adje.weight=w;
    adjTable[n1].push_back(adje);
}

std::map<NODE, std::vector<ADJEDGE> > Graph::getAdjTable()
{
    return adjTable;
}
std::set<int> Graph::getNodes()
{
    return nodes;
}
std::map<int, std::set<int> > Graph::getNodeNet()
{
    return nodenet;
}


void Graph::print()
{
    /*std::map<NetPair,double>::iterator iter=netifmap.begin();
    while (iter!=netifmap.end()) {
        std::cout<<iter->first.net1<<"\t"<<iter->first.net2<<"\t"<<iter->second<<std::endl;
        iter++;
    }
    for (int i=0; i<files.size(); i++) {
        std::cout<<files[i]<<std::endl;
    }*/
    
    /*for (int i=0; i<edges.size(); i++) {
        EDGE edge=edges[i];
        std::cout<<edge.u.node_id<<"_"<<edge.u.net_id<<"\t"<<edge.v.node_id<<"_"<<edge.v.net_id<<"\t"<<edge.weight<<std::endl;
    }*/
    
    std::map<NODE,std::vector<ADJEDGE> >::iterator iter=adjTable.begin();
    while (iter!=adjTable.end()) {
        std::vector<ADJEDGE> tadjs=iter->second;
        for (int i=0; i<tadjs.size(); i++) {
            std::cout<<iter->first.node_id<<"_"<<iter->first.net_id<<"\t"<<tadjs[i].dest.node_id<<"_"<<tadjs[i].dest.net_id<<"\t"<<tadjs[i].weight<<std::endl;
        }
        iter++;
    }
}