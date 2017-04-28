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
    whoseTurn(whofirst),blackIsAi(blackAi),whiteIsAi(whiteAi),bd()
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
    int whiteIsAi;

};


#endif //REVERSE1_GAME_H
