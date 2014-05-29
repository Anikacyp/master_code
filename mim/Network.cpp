#include "Network.h"

Network::Network(int network_num)
{
	this->num_of_network=network_num;
}
Network::~Network(){}

void Network::infoInput()
{

	for(int i=1;i<=this->num_of_network;i++)
	{
		std::string file("");
		NtkInfo tmpntk;
		std::cout<<"please input the "<<i<<"th network files"<<std::endl;
		std::cin>>file;
		Graph *graph=new Graph(file);
		graph->buildGraph();
		tmpntk=graph->getNetwork();
		networks[i]=tmpntk;
		delete graph;
	}


	if(this->num_of_network>0)
	{
		this->num_of_argment=this->num_of_network*(this->num_of_network-1);
		for(int i=1;i<=this->num_of_network;i++)
		{
			//char *p1=itoa(i);
			std::string s1=std::to_string(i);
			int j=1;
			//std::map<int, double> submap;
			while(j<=this->num_of_network)
			{
				if(i!=j)
				{
					//char * p2=itoa(j);
					std::string s2=std::to_string(j);
					std::string keys=s1+"#"+s2;
					std::cout<<"please input the influence of network "<<i<<" to network "<<j<<std::endl;
					//std::cin>>submap[j];
					std::cin>>net_inf[keys];
				}
				j++;
			}
			//inf_coef[i]=submap;
			//submap.clear();
		}
	}
	//output the influence coefficient between the network.
	/*std::map<int,std::map<int,double> >::iterator iter=inf_coef.begin();
	while(iter!=inf_coef.end())
	{
		std::map<int,double> tmp=iter->second;
		std::map<int,double>::iterator tmpiter=tmp.begin();
		while(tmpiter!=tmp.end())
		{
			std::cout<<iter->first<<"\t"<<tmpiter->first<<"\t"<<tmpiter->second<<std::endl;
			tmpiter++;
		}
		iter++;
	}*/
}


std::map<std::string,double> Network::getNetInf()
{
	return net_inf;
}

std::map<int,NtkInfo> Network::getNetworks()
{
	return networks;
}
int Network::getNtkNum()
{
	return this->num_of_network;
}