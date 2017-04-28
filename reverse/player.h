#pragma once
#include"Socket.h"
#include"board.h"
class player
{
public:
    player(int color):
            colorflag(color)
    {}

    int showColor();
    point nextMove(const board& bd);
    point tryMonteCarloTreeSearch(const board& bd, int maxTries);

private:
    int colorflag;
    int maxTries=4096;


};
