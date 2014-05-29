#include "Graph.h"
#include "Network.h"
#include "PP.h"

int main(int argc, char * argv[])
{
	int network_num=0;
	std::cout<<"number of networks:"<<std::endl;
	std::cin>>network_num;
	Network *ninfor=new Network(network_num);
	ninfor->infoInput();
	PP *tpp=new PP();
	tpp->setNetworks(ninfor->getNetworks());
	tpp->setNetInf(ninfor->getNetInf());
	tpp->ppCal();
	delete ninfor;
	delete tpp;
	return 0;
}