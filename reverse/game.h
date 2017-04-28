//
// Created by 胡笛 on 2017/4/27.
//

#ifndef REVERSE1_GAME_H
#define REVERSE1_GAME_H
#include"board.h"
#include "Socket.h"
#include "playerbase.h"
#include "player.h"
class game {
public:
    game(int whofirst,int blackAi,int whiteAi):
    whoseTurn(whofirst),blackIsAi(blackAi),whiteIsAi(whiteAi),bd(),timeCost(0)
    {
        AI=NULL;
    }

    board& geiboard();

    int getWhoseTurn() const;

    void peoplemove(point a);
    void checknextmove();
    void initialAI();
private:
    player* AI;
    board bd;
    int whoseTurn;
    int blackIsAi;
public:
    double getTimeCost() const;

private:
    int whiteIsAi;
    double timeCost;
};


#endif //REVERSE1_GAME_H
