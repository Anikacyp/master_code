//
//  Graph.cpp
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#include "Graph.h"
Graph::Graph(std::vector<std::string> files){
    this->files=files;
	built=false;
}

Graph::Graph(){
	this->built=false;
    fileInput();
}

Graph::~Graph(){}

void Graph::fileInput()
{
    int network_NO;
    std::cout<<"network number"<<std::endl;
    std::cin>>network_NO;
    std::string file("");
    for (int i=0; i<network_NO; i++) {
        std::cout<<"please input the file of "<<i+1<<"th network"<<std::endl;
        std::cin>>file;
        files.push_back(file);
    }
}

void Graph::buildGraph()
{
    //fileInput();
    std::map<int,int> tmp_map;
    std::ifstream ifile;
    int nu,nv,tmp_nu,tmp_nv;
    double w1,w2;
    for (int i=0; i<files.size(); i++) {
        ifile.open(files[i].c_str(),std::istream::in);
        if(ifile)
        {
            tmp_map.clear();
            while(!ifile.eof())
            {
                ifile>>nu>>nv>>w1>>w2;
                tmp_nu=nu;
                tmp_nv=nv;
                if (!tmp_map.count(nu))
                {
                    if (node_id_map.count(nu))
                    {
                        tmp_nu=node_id_map.size()+1;
                    }else
                    {
                        tmp_nu=nu;
                    }
                    node_id_map[tmp_nu]=nu;
                    tmp_map[nu]=tmp_nu;
                    node_net_map[tmp_nu]=i+1;
                    node_set_map[nu].insert(tmp_nu);
                }
                else
                {
                    tmp_nu=tmp_map[nu];
                }
                
                if (!tmp_map.count(nv))
                {
                    if (node_id_map.count(nv))
                    {
                        tmp_nv=node_id_map.size()+1;
                    }else
                    {
                        tmp_nv=nv;
                    }
                    node_id_map[tmp_nv]=nv;
                    tmp_map[nv]=tmp_nv;
                    node_net_map[tmp_nv]=i+1;
                    node_set_map[nv].insert(tmp_nv);
                }else
                {
                	tmp_nv=tmp_map[nv];
                }
                
                Edge edge(tmp_nu,tmp_nv,w1);
                Edges.push_back(edge);
                edge.u=tmp_nv;
                edge.v=tmp_nu;
                edge.pp=w2;
                Edges.push_back(edge);
                if (w1>0) {
                    adjacentTable(tmp_nu,tmp_nv,w1);
                }
                if (w2>0) {
                    adjacentTable(tmp_nv,tmp_nu,w2);
                }
            }
        }
        ifile.close();
    }
    //weakCoefficient();
    nodeintGraph();
    
    built=true;
    std::cout<<"node_set_map size: \t"<<node_set_map.size()<<std::endl;
    std::cout<<"node_id_map size: \t"<<node_id_map.size()<<std::endl;
}

/*void Graph::weakCoefficient()
{
    srand(unsigned(time(0)));
    double tval=0.0;
    std::map<int,std::set<int> >::iterator iter=node_set_map.begin();
    while (iter!=node_set_map.end()) {
        //该随机数是节点已被激活后，其他网络中该点被激活的弱化系数
        tval=rand()/(double)(RAND_MAX);
		weakCoeff[iter->first]=tval;
        
        //该随机数表示网络中节点本身之间的激活系数
        //tval=std::rand()/(double)(RAND_MAX);
        //naive[iter->first]=tval;
        iter++;
    }
}*/

void Graph::nodeintGraph()
{
    srand(unsigned(time(0)));
    std::vector<int> tmpvec;
    std::map<int,std::set<int> >::iterator iter=node_set_map.begin();
    while (iter!=node_set_map.end()) {
        tmpvec.clear();
        //int id=iter->first;
        std::set<int> nodes=iter->second;
        std::set<int>::iterator iter1=nodes.begin();
        while (iter1!=nodes.end()) {
            tmpvec.push_back(*iter1);
            iter1++;
        }
        for (int i=0; i<tmpvec.size(); i++) {
            for (int j=0; j<tmpvec.size(); j++) {
                if (i!=j) {
                    double tval=rand()/(double)(RAND_MAX);
                    tval*=0.1;
                    adjacentTable(tmpvec[i],tmpvec[j],tval);
                }
            }
        }
        iter++;
    }
}

void Graph::adjacentTable(int u,int v,double w)
{
    ADJ adj(v,w);
    adjTable[u].push_back(adj);
}


std::map<int,int> Graph::getNodeIdMap()
{
    return node_id_map;
}
std::map<int,int> Graph::getNodeNetMap()
{
    return node_net_map;
}
std::map<int,std::set<int> > Graph::getNodeSetMap()
{
    return node_set_map;
}
std::map<int,std::vector<ADJ> > Graph::getAdjTable()
{
    return adjTable;
}
std::vector<Edge> Graph::getEdges()
{
    return Edges;
}
bool Graph::isBuilt()
{
    return built;
}

/*std::map<int,double> Graph::getWeakCoeff()
 {
 return weakCoeff;
 }*/
