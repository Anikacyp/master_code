#include "PP.h"
PP::PP(){}

PP::~PP(){}


void PP::setNetInfo(NETINFO ntf)
{
	this->netInfo=ntf;
    this->node_set=this->netInfo.node_set;
	this->indexing();
}

void PP::indexing()
{
	std::vector<Edge> edges=netInfo.edges;
	std::vector<Edge>::iterator iter=edges.begin();
	while(iter!=edges.end())
	{
		Edge edge=*iter;

		Node u=edge.u;
		Node v=edge.v;

		std::string keyu=std::to_string(u.node_ID)+"_"+std::to_string(u.net_ID);
		std::string keyv=std::to_string(v.node_ID)+"_"+std::to_string(v.net_ID);

		float w1=edge.w1;
		float w2=edge.w2;


		arcNode tmpNode;

		//----------------正向存储每个点u的邻接表：即有哪些点由点u出----------------//
		tmpNode.node=v;
		tmpNode.weight=w1;

		std::vector<arcNode> tmpvec;
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
		std::cout<<iter1->first<<": \t"<<std::endl;
		std::vector<arcNode> tmp=iter1->second;
		for(int i=0;i<tmp.size();i++)
		{
			std::cout<<tmp[i].node.node_ID<<"_"<<tmp[i].node.net_ID<<"\t"<<tmp[i].weight<<std::endl;
		}
		iter1++;
	}*/
}
double PP::infProbCal(int nodeA,int nodeB)
{
    std::set<int> setA;
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
            std::cout<<v.node_ID<<"_"<<v.net_ID<<"\t"<<u.node_ID<<"_"<<u.net_ID<<std::endl;
            //计算点的传播概率，并记录传播路径
            subinf(u,v);
            iterA++;
        }
        iterB++;
    }
    return infval;
}

double PP::subinf(Node nodeA,Node nodeB)
{
    
}