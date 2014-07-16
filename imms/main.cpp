//
//  main.cpp
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#include "Seed.h"
int main(int argc,char * argv[])
{
    std::cout<<"1 means greedy algorithm\n2 means the maximum propagation path"<<std::endl;
    std::vector<std::string> files;
    for (int i=1; i<argc-1; i++) {
        files.push_back(argv[i]);
    }
    int mode=atoi(argv[argc-1]);
    Seed *seed=new Seed(files);
    seed->run(mode);
    delete seed;
    return 1;
}