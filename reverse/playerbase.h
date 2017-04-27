//
// Created by 胡笛 on 2017/4/27.
//

#ifndef REVERSE1_PLAYERBASE_H
#define REVERSE1_PLAYERBASE_H
#include"board.h"

class playerbase {
    virtual point nextMove(const board& bd);
};


#endif //REVERSE1_PLAYERBASE_H
