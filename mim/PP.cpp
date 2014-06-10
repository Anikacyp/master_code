#include "PP.h"
PP::PP(){}

PP::~PP(){}


void PP::setNetInfo(NETINFO ntf)
{
	this->netInfo=ntf;
    this->node_set=this->netInfo.node_set;
    this->nodes=this->netInfo.nodes;
	this->adjTable();
}

void PP::adjTable()
{
    AdjForward.clear();
    //按照邻接表存储图结构，分别从正向和反向进行存储
    //其中key值按照node_ID+"_"+net_ID进行存储
	std::vector<Edge> edges=netInfo.edges;
	std::vector<Edge>::iterator iter=edges.begin();
	while(iter!=edges.end())
	{
		Edge edge=*iter;

		Node u=edge.u;
		Node v=edge.v;

        //keys
		std::string keyu=std::to_string(u.node_ID)+"_"+std::to_string(u.net_ID);
		std::string keyv=std::to_string(v.node_ID)+"_"+std::to_string(v.net_ID);

		float w1=edge.w1;
		float w2=edge.w2;

		arcNode tmpNode(v,w1);

        std::vector<arcNode> tmpvec;
		//----------------正向存储每个点u的邻接表：即有哪些点由点u出----------------//
        //存储key为keyu的点信息
		//tmpNode.node=v;
		//tmpNode.weight=w1;

       
		if(AdjForward.count(keyu))
		{
			AdjForward[keyu].push_back(tmpNode);
		}
		else
		{
			tmpvec.clear();
			tmpvec.push_back(tmpNode);
			AdjForward[keyu]=tmpvec;
		}
        
		//存储key为keyv的点信息
		tmpNode.node=u;
		tmpNode.weight=w2;
		if(AdjForward.count(keyv))
		{
			AdjForward[keyv].push_back(tmpNode);
		}
		else
		{
			tmpvec.clear();
			tmpvec.push_back(tmpNode);
			AdjForward[keyv]=tmpvec;
		}

		//----------------逆向存储每个点u的邻接表：即有哪些点进入点u----------------//
        

		iter++;
	}


	/*std::map<std::string, std::vector<arcNode> >::iterator iter1=AdjForward.begin();
	while(iter1!=AdjForward.end())
	{
		//std::cout<<iter1->first<<": \t"<<std::endl;
		std::vector<arcNode> tmp=iter1->second;
		for(int i=0;i<tmp.size();i++)
		{
			std::cout<<iter1->first<<"\t"<<tmp[i].node.node_ID<<"_"<<tmp[i].node.net_ID<<"\t"<<tmp[i].weight<<std::endl;
		}
        std::cout<<"---------------------------"<<std::endl;
		iter1++;
	}*/
}

void PP::infProbCal()
{
    /*std::set<int> setA;
    std::set<int> setB;
    double infval;
    if(this->node_set.count(nodeA))
        setA=this->node_set[nodeA];
    if(this->node_set.count(nodeB))
        setB=this->node_set[nodeB];
    int sizeA=setA.size();
    int sizeB=setB.size();
    int totalInfNum=sizeA*sizeB;
    
    std::set<int>::iterator iterA=setA.begin();
    std::set<int>::iterator iterB=setB.begin();
    while(iterB!=setB.end())
    {
        Node u=Node(nodeB,*iterB);
        iterA=setA.begin();
        while (iterA!=setA.end()) {
            Node v=Node(nodeA,*iterA);
            //std::cout<<v.node_ID<<"_"<<v.net_ID<<"\t"<<u.node_ID<<"_"<<u.net_ID<<std::endl;
            //计算点的传播概率，并记录传播路径
            subinf(u,v);
            iterA++;
        }
        iterB++;
    }
    return infval;*/
    std::set<int>::iterator iter=nodes.begin();
    while (iter!=nodes.end()) {
        MPP(*iter);
        iter++;
    }
}

void PP::MPP(int node_id)
{
    //Node node;
    if(this->nodes.count(node_id))
    {
        std::set<int> setN=node_set[node_id];
        std::set<int>::iterator iter=setN.begin();
        while (iter!=setN.end()) {
            //std::cout<<node_ID<<"\t"<<*iter<<std::endl;
            //node.node_ID=node_ID;
            //node.net_ID=*iter;
            Dijkstra(node_id,*iter);
            iter++;
        }
    }
}


//std::map<std::string,std::map<std::string,double> >
void PP::Dijkstra(int node_id, int net_id)
{
    std::string tkey=std::to_string(node_id)+"_"+std::to_string(net_id);
    if (AdjForward.count(tkey)) {
        std::vector<arcNode> tmpvec=AdjForward[tkey];
        //std::cout<<node_id<<"\t"<<net_id<<"\t"<<tmpvec.size()<<std::endl;
        double minval=(double)0.0;
        Node nextNode;
        for (int i=0; i<tmpvec.size(); i++) {
            arcNode anode=tmpvec[i];
            if(anode.weight>minval)
            {
                minval=anode.weight;
                nextNode.node_ID=anode.node.node_ID;
                nextNode.net_ID=anode.node.net_ID;
            }
        }
        std::cout<<node_id<<"_"<<net_id<<"\t"<<nextNode.node_ID<<"_"<<nextNode.net_ID<<"\t"<<minval<<std::endl;
    }
}

