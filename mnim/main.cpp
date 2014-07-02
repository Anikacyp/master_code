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
	int mode;
    std::cout<<"please input the mode: \nyou can choose 0,1,2,3"<<std::endl;
    std::cin>>mode;
    Seed * seed=new Seed(mode);
    delete seed;
    /*std::vector<int> numbers;
    for (int i=0; i<10; i++) {
        int val;
        std::cin>>val;
        numbers.push_back(val);
    }
    std::srand(unsigned(time(0)));
    for (int i=0; i<10; i++) {
        std::cout<<numbers.size()<<"\t";
        int pos=std::rand()%(numbers.size());
        std::cout<<pos<<"\t"<<numbers[pos]<<std::endl;
        if (numbers.size()>0) {
            std::vector<int>::iterator iter=numbers.begin();
            iter+=pos;
            numbers.erase(iter);
        }
    }
    std::cout<<numbers.size()<<std::endl;*/
    return 1;
}
