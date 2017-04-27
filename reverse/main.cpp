//
// Created by 胡笛 on 2017/4/27.
//

#include"board.h"
#include"player.h"
#include<iostream>
int main()
{
    board bd;
    bd=bd.oneStep(1,point(4,5));
    bd.print();
    std::cout<<bd.getAvaliable(1).size()<<std::endl;
    std::cout<<point(0,0).toString()<<std::endl;
    std::set<point>::iterator it;
    std::set<point> tmp=bd.getAvaliable(1);
    it=tmp.begin();
    while(it!=tmp.end())
    {
        std::cout<<it->toString()<<" ";
        it++;
    }
}