#include "Graph.h"

std::vector<Edge> Graph::edges;
std::vector<int> Graph::degree;
std::map<int,std::map<int,double> > Graph::index;
//Network Graph::network;

Graph::Graph(std::string fname)
{
	this->file_name=fname;
	this->node_num=0;
	this->edge_num=0;
}
Graph::~Graph(){}

void Graph::buildGraph()
{
	/*int node_u,node_v;
	double weight_w1,weight_w2;
	std::string line;
	std::string term;*/

	
	//std::istringstream iss;
	
	//std::ifstream::in indicate that only read operation was made.
	std::ifstream infile;
	infile.open(this->file_name.c_str(),std::ifstream::in);
	if(infile)
	{
		//get the information of the input file(network structure), which store the nodes and weight of the edge
		/*getline(infile,line);
		iss.str(line);
		iss>>term;
		this->node_num=std::atoi(term.c_str());
		iss>>term;
		this->edge_num=std::atoi(term.c_str());
		iss.clear();*/
		infile>>this->node_num>>this->edge_num;

		degree.resize(this->node_num);
		//edges.resize(this->edge_num*2);
		int count=0;

		//for(int i=0;i<this->edge_num;i++)
		while(!infile.eof())
		{
			Edge edge1,edge2;
			std::map<int,double> submap;

			infile>>edge1.u>>edge1.v>>edge1.w1>>edge1.w2;
			edges.push_back(edge1);
			edge2.u=edge1.v;
			edge2.v=edge1.u;
			edge2.w1=edge1.w2;
			edge2.w2=edge1.w1;
			edges.push_back(edge2);
			if(edge1.w1>0)
				degree[edge1.u-1]++;
			if(edge2.w1>0)
				degree[edge1.v-1]++;

			submap=index[edge1.u];
			submap[edge1.v]=edge1.w1;
			index[edge1.u]=submap;
			submap.clear();
			submap=index[edge1.v];
			submap[edge1.u]=edge1.w2;
			index[edge1.v]=submap;
			submap.clear();
			/*infile>>edges[count].u>>edges[count].v>>edges[count].w1>>edges[count].w2;
			
			edges[count+1].u=edges[count].v;
			edges[count+1].v=edges[count].u;
			edges[count+1].w1=edges[count].w2;
			edges[count+1].w2=edges[count].w1;

			degree[edges[count].u-1]++;
			degree[edges[count+1].u-1]++;
			//index[edges[count].u-1][edges[count].v-1]=w1;
			count+=2;*/
		}
	}
	else
	{
		std::cerr<<"error: unable to open input file:\t"<<this->file_name<<std::endl;
	}
	//print input information:
	/*std::cout<<" node and edge info: "<<this->node_num<<"\t"<<this->edge_num<<std::endl;
	std::vector<Edge>::iterator iter=edges.begin();
	while(iter!=edges.end())
	{
		std::cout<<iter->u<<"\t"<<iter->v<<"\t"<<iter->w1<<"\t"<<iter->w2<<std::endl;
		iter++;
	}
	std::vector<int>::iterator iterd=degree.begin();
	while(iterd!=degree.end())
	{
		std::cout<<*iterd<<std::endl;
		iterd++;
	}

	std::map<int, std::map<int,double> > ::iterator iter=index.begin();
	while(iter!=index.end())
	{
		//if(iter->first==5)
		//{
			std::map<int,double> tmp=iter->second;
			std::map<int,double>::iterator tmpiter=tmp.begin();
			while(tmpiter!=tmp.end())
			{
				std::cout<<iter->first<<"\t"<<tmpiter->first<<"\t"<<tmpiter->second<<std::endl;
				tmpiter++;
			}
		//}
		iter++;
	}*/

	this->ntk.edge=edges;
	this->ntk.index=index;
	this->ntk.degree=degree;
	infile.close();
}


int Graph::getNodeNum()
{
	return this->node_num;
}

int Graph::getEdgeNum()
{
	return this->edge_num;
}
int Graph::getDegree(int node_id)
{
	return degree[node_id-1];
}

NtkInfo Graph::getNetwork()
{
	return this->ntk;
}
