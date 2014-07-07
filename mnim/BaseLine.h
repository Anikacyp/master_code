//
//  BaseLine.h
//  mnim
//
//  Created by Anika on 7/7/14.
//
//

#ifndef __mnim__BaseLine__
#define __mnim__BaseLine__

#include <iostream>
#include "BaseObj.h"
#include <vector>
#include <set>
#Include "limit.h"

class BaseLine
{
private:
    std::vector<NODE> seedsvec;
    std::set<NODE> seedsset;
    
public:
    void run();
	NODE nextSeed();
};

#endif /* defined(__mnim__BaseLine__) */
