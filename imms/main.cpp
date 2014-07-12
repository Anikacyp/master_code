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
    Seed *seed=new Seed();
    int mode;
    std::cout<<"choose mode:\n1 means greedy algorithm\n2 means the maximum propagation path"<<std::endl;
    std::cin>>mode;
    seed->run(mode);
    delete seed;
    return 1;
}