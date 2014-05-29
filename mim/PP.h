#ifndef PP_H
#define PP_H
#include <map>
#include "Graph.h"

//PP means the propagation probability between nodes; 
//and in this file, propagation probability between nodes among multiple networks will be calculated.
class PP
{
private:
	std::map<int,NtkInfo> networks;
	std::map<std::string,double> net_inf;
	std::map<int,std::map<int,double> > NodeInf;

public:
	PP();
	~PP();
	void ppCal();
	void setNetworks(std::map<int,NtkInfo> tnet);
	void setNetInf(std::map<std::string,double> ninf);
};
#endif