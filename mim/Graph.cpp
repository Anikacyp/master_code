#include "Graph.h"

std::vector<Edge> Graph::edges;
std::set<int> Graph::nodes;
//std::map<int,std::set<std::string> > Graph::node_set;
std::map<int, std::set<int> > Graph::node_set;
std::map<int,std::set<int> > Graph::net_node_set;

Graph::Graph(int file_num)
{
	this->net_num=file_num;
	netInfo.net_num=this->net_num;
}

Graph::~Graph(){}

//get the networks' information, which include the network number and the influence between each other.
void Graph::inputNet()
{
	std::string file="";
	for(int i=0;i<this->net_num;i++)
	{
		std::cout<<"input file "<<i<<std::endl;
		std::cin>>file;
		files.push_back(file);
	}
	if(this->net_num>0)
	{
		for(int i=1;i<=this->net_num;i++)
		{
			
			std::string s1=std::to_string(i);
			int j=1;
			while(j<=this->net_num)
			{
				if(i!=j)
				{
					std::string s2=std::to_string(j);
					std::string key=s1+"#"+s2;
					std::cout<<"please input the influece of network "<<i<<" to network "<<j<<std::endl;
					std::cin>>net_inf[key];
				}
				j++;
			}
		}
	}
	netInfo.net_inf=this->net_inf;
}

//build the graph of the network, which store the edge information in or among networks. 
//and for a specific node, store its nodes in different networks.
void Graph::buildGraph()
{
	std::ifstream ifile;
	//std::string net;
	int net;
	for(int i=0;i<files.size();i++)
	{
		ifile.open(files[i].c_str(),std::istream::in);
		if(ifile)
		{
			Edge edge;
			std::set<int> tmp_nodes;
			tmp_nodes.clear();
			int int_u,int_v;
			while(!ifile.eof())
			{
				ifile>>edge.u.node_ID>>edge.v.node_ID>>edge.w1>>edge.w2;

				//int_u=std::atoi(edge.u.c_str());
				//int_v=std::atoi(edge.v.c_str());
				//net=std::to_string(i+1);
				net=i+1;

				edge.u.net_ID=net;
				edge.v.net_ID=net;
				//edge.u=edge.u+"_"+net;
				//edge.v=edge.v+"_"+net;
				edges.push_back(edge);
				
				if(!nodes.count(edge.u.node_ID))
				{
					nodes.insert(edge.u.node_ID);
				}
				if(!nodes.count(edge.v.node_ID))
				{
					nodes.insert(edge.v.node_ID);
				}
				if(!tmp_nodes.count(edge.u.node_ID))
				{
					node_set[edge.u.node_ID].insert(net);
					tmp_nodes.insert(edge.u.node_ID);
				}
				if(!tmp_nodes.count(edge.v.node_ID))
				{
					node_set[edge.v.node_ID].insert(net);
					tmp_nodes.insert(edge.v.node_ID);
				}
			}
			net_node_set[net]=tmp_nodes;
			
			ifile.close();
		}
		else
		{
			std::cerr<<"error, unable to open file "<<files[i]<<std::endl;
		}
	}


	for(int i=1;i<=this->net_num;i++)
	{
		for(int j=i;j<=this->net_num;j++)
		{
			if(j!=i)
			{
				std::string tkey=std::to_string(i)+"#"+std::to_string(j);
				double tinf=net_inf[tkey];
				std::string tkey2=std::to_string(j)+"#"+std::to_string(i);
				double tinf2=net_inf[tkey2];
				std::set<int> net1=net_node_set[i];
				std::set<int> net2=net_node_set[j];
				std::set<int>::iterator iter=net1.begin();
				while(iter!=net1.end())
				{
					if(net2.count(*iter))
					{
						//std::string tmp_u=std::to_string(*iter)+"_"+std::to_string(i);
						//std::string tmp_v=std::to_string(*iter)+"_"+std::to_string(j);
						Edge edge;
						edge.u.node_ID=*iter;
						edge.u.net_ID=i;
						edge.v.node_ID=*iter;
						edge.v.net_ID=j;
						edge.w1=tinf;
						edge.w2=tinf2;
						edges.push_back(edge);
					}
					iter++;
				}
			}
		}
	}

	//存储对应的信息到netInfo里
	netInfo.net_node_set=this->net_node_set;
	netInfo.node_set=this->node_set;
	netInfo.nodes=this->nodes;
	netInfo.edges=this->edges;
}

void Graph::printGraph()
{
	//std::cout<<"node number: "<<node_set.size()<<std::endl;
	std::cout<<"graph information: "<<std::endl;
	for(int i=0;i<edges.size();i++)
	{
		std::cout<<edges[i].u.node_ID<<"@"<<edges[i].u.net_ID<<"\t"
		<<edges[i].v.node_ID<<"@"<<edges[i].v.net_ID<<"\t"<<edges[i].w1<<"\t"<<edges[i].w2<<"\t"<<std::endl;
	}
	//std::cout<<"there are total "<<nodes.size()<<" nodes!"<<std::endl;
	std::cout<<"node and its corresponding set: "<<std::endl;
	std::map<int, std::set<int> >::iterator iter1=node_set.begin();
	while(iter1!=node_set.end())
	{
		std::set<int> tmpset=iter1->second;
		std::cout<<iter1->first<<": \t";
		std::set<int>::iterator iters=tmpset.begin();
		while(iters!=tmpset.end())
		{
			std::cout<<*iters<<"\t";
			iters++;
		}
		std::cout<<std::endl;
		iter1++;
	}
	/*std::map<std::string,double>::iterator iternet=net_inf.begin();
	while(iternet!=net_inf.end())
	{
		std::cout<<iternet->first<<"\t"<<iternet->second<<std::endl;
		iternet++;
	}*/
}

NETINFO Graph::getNetInfo()
{
	return this->netInfo;
}