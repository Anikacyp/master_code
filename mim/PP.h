#ifndef PP_H
#define PP_H
#include <map>
#include <set>
#include "Graph.h"

struct InfProb
{
	int u,v;
	double w;
	std::set<std::string> pathes;
};
class PP
{
private:
	NETINFO netInfo;
	map<
public:
	PP();
	~PP();
	void setNetInfo(NETINFO ntf);
	void infProbCal();
	void DFS();
};

#endif