#include "Graph.h"

std::vector<Edge> Graph::edges;
std::set<int> Graph::nodes;
std::map<int,std::set<std::string> > Graph::node_set;
std::map<int,std::set<int> > Graph::net_node_set;

Graph::Graph(int file_num)
{
	this->net_num=file_num;
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
}

//build the graph of the network, which store the edge information in or among networks. 
//and for a specific node, store its nodes in different networks.
void Graph::buildGraph()
{
	std::ifstream ifile;
	std::string net;
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
				ifile>>edge.u>>edge.v>>edge.w1>>edge.w2;
				int_u=std::atoi(edge.u.c_str());
				int_v=std::atoi(edge.v.c_str());
				net=std::to_string(i+1);

				edge.u=edge.u+"_"+net;
				edge.v=edge.v+"_"+net;
				edges.push_back(edge);
				
				if(!nodes.count(int_u))
				{
					nodes.insert(int_u);
				}
				if(!nodes.count(int_v))
				{
					nodes.insert(int_v);
				}
				if(!tmp_nodes.count(int_u))
				{
					node_set[int_u].insert(edge.u);
					tmp_nodes.insert(int_u);
				}
				if(!tmp_nodes.count(int_v))
				{
					node_set[int_v].insert(edge.v);
					tmp_nodes.insert(int_v);
				}
			}
			net_node_set[i+1]=tmp_nodes;
			
			ifile.close();
		}
		else
		{
			std::cerr<<"error, unable to open file "<<files[i]<<std::endl;
		}
	}

	for(int i=1;i<=this->net_num;i++)
	{
		for(int j=1;j<=this->net_num;j++)
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
						std::string tmp_u=std::to_string(*iter)+"_"+std::to_string(i);
						std::string tmp_v=std::to_string(*iter)+"_"+std::to_string(j);
						Edge edge;
						edge.u=tmp_u;
						edge.v=tmp_v;
						edge.w1=tinf;
						edge.w2=tinf2;
						edges.push_back(edge);
					}
					iter++;
				}
			}
		}
	}
}

void Graph::printGraph()
{
	//std::cout<<"node number: "<<node_set.size()<<std::endl;
	std::cout<<"graph information: "<<std::endl;
	for(int i=0;i<edges.size();i++)
	{
		std::cout<<edges[i].u<<"\t"<<edges[i].v<<"\t"<<edges[i].w1<<"\t"<<edges[i].w2<<"\t"<<std::endl;//edges[i].net_u<<"\t"<<edges[i].net_v<<std::endl;
	}
	//std::cout<<"there are total "<<nodes.size()<<" nodes!"<<std::endl;
	/*std::cout<<"node and its corresponding set: "<<std::endl;
	std::map<int, std::set<std::string> >::iterator iter1=node_set.begin();
	while(iter1!=node_set.end())
	{
		std::set<std::string> tmpset=iter1->second;
		std::cout<<iter1->first<<"\t";
		std::set<std::string>::iterator iters=tmpset.begin();
		while(iters!=tmpset.end())
		{
			std::cout<<*iters<<"\t";
			iters++;
		}
		std::cout<<std::endl;
		iter1++;
	}
	std::map<std::string,double>::iterator iternet=net_inf.begin();
	while(iternet!=net_inf.end())
	{
		std::cout<<iternet->first<<"\t"<<iternet->second<<std::endl;
		iternet++;
	}*/
}