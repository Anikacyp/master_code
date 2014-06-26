//
//  main.cpp
//  mnim
//
//  Created by Anika on 6/19/14.
//
//
#include <iostream>
#include "Model.h"
int main(int agrc, char * argv[])
{
    Model *model=new Model(3);
    model->spread();
    delete model;
    return 1;
}
