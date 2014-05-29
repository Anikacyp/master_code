#include "PP.h"

PP::PP(){}
PP::~PP(){}

void PP::ppCal()
{

	std::map<int,NtkInfo>::iterator iter=networks.begin();
	
	while(iter!=networks.end())
	{
		std::cout<<"network \t"<<iter->first<<std::endl;
		std::map<int,double> tmap;
		NtkInfo net=iter->second;
		std::vector<Edge> edges=net.edge;
		std::vector<Edge>::iterator viter=edges.begin();
		while(viter!=edges.end())
		{
			std::cout<<viter->u<<"\t"<<viter->v<<"\t"<<viter->w1<<"\t"<<viter->w2<<std::endl;
			for(int i=1;i<=net_inf.size();i++)
			{
				if(i!=iter->first)
				{
					std::string tkey=std::to_string(iter->first)+"#"+std::to_string(i);
					std::cout<<tkey<<"\t"<<net_inf[tkey]<<std::endl;				}
			}
			viter++;
		}
		iter++;
	}

	/*std::map<std::string,double>::iterator infiter=net_inf.begin();
	while(infiter!=net_inf.end())
	{
		std::cout<<infiter->first<<"\t"<<infiter->second<<std::endl;
		infiter++;
	}*/

}
void PP::setNetworks(std::map<int,NtkInfo> tnet)
{
	this->networks=tnet;
}

void PP::setNetInf(std::map<std::string,double> ninf)
{
	this->net_inf=ninf;
}