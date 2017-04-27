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
    Node node;

};

class Node{
private:
    board bd;
    point parentpoint;
    int wins=0;
    int visits=0;
    std::set<point> move;
    std::set<point> children;
    std::set<point> untriedMoves;
    int color;
public:
    Node(){

    }
    Node(const board& bd, point parentNode, const std::set<point> move){
        this->bd=bd;
        this->parentpoint=parentNode;
        this->move=move;
        this->children=NULL;
        this->wins=0;
        this->visits=0;
        this->untriedMoves=bd.getAvaliable(color);

    }
};

