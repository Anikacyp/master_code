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

struct InfPath
{
	
};

class PP
{
private:
	NETINFO netInfo;

public:
	PP();
	~PP();
	void setNetInfo(NETINFO ntf);
	void indexing();
	void infProbCal();
	void DFS();
};

#endif