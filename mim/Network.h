#ifndef NETWORK_H
#define NETWORK_H
#include <map>
#include <iostream>
#include "Graph.h"


struct NtkInfCoef
{
	int ntk1;
	int ntk2;
	double infcoef;
};

class Network
{
private:
	int num_of_network;
	int num_of_argment;
	//std::map<int,std::map<int,double> > inf_coef;
	std::map<std::string,double> net_inf;
	std::map<int,NtkInfo> networks;

public:
	Network(int network_num);
	~Network();
	void infoInput();
	std::map<std::string,double> getNetInf();
	std::map<int,NtkInfo> getNetworks();
	int getNtkNum();
};
#endif