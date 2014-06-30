//
//  main.cpp
//  mnim
//
//  Created by Anika on 6/19/14.
//
//
#include <iostream>
#include "Model.h"
#include "Seed.h"

int main(int agrc, char * argv[])
{
    //Model *model=new Model(3);
    //model->spread();
    //delete model;
    Seed * seed=new Seed(1);
    delete seed;
    return 1;
}
