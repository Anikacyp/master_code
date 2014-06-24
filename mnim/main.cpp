//
//  main.cpp
//  mnim
//
//  Created by Anika on 6/19/14.
//
//
#include <iostream>
#include "HBI.h"
int main(int agrc, char * argv[])
{
    HBI *hbi=new HBI();
    hbi->traversal(2);
    delete hbi;
    return 1;
}
