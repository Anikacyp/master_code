//
//  Seed.h
//  mnim
//
//  Created by Anika on 6/23/14.
//
//

#ifndef __mnim__Seed__
#define __mnim__Seed__

#include <iostream>


class Seed
{
private:
    std::map<int,std::map<int,double> > GlobalInf;
    std::map<int,std::map<NODE,infPath> > GIP;
    std::map<int,double> naive;
    
public:
    Seed();
    ~Seed();
    void topkSeed();
    
};

#endif /* defined(__mnim__Seed__) */
