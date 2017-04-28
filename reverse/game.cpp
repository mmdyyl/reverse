//
// Created by 胡笛 on 2017/4/27.
//

#include "game.h"
board& game::geiboard()
{
    return bd;
}
void game::peoplemove(point a)
{
    bd=bd.oneStep(whoseTurn,a);
    whoseTurn=!whoseTurn;
}
void game::checknextmove()
{
    if(bd.getAvaliable(whoseTurn).size()==0)
    {
        whoseTurn=!whoseTurn;
    }
    if(blackIsAi==1)
    {
        if(whoseTurn==1)
        {
            bd=bd.oneStep(1,AI->nextMove(bd));
        }
    }
    if(whiteIsAi==1)
    {
        if(whoseTurn==0)
        {
            bd=bd.oneStep(0,AI->nextMove(bd));
        }
    }
}

void game::initialAI() {
    if(blackIsAi)
    {
        AI=new player(1);
    }
    if(whiteIsAi==1)
    {
        AI=new player(0);
    }
}

int game::getWhoseTurn() const {
    return whoseTurn;
}

double game::getTimeCost() const {
    return timeCost;
}


