#pragma once
#include <cstdlib>
#include <list>
#include"Socket.h"
#include"board.h"
#include "vector"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>

using namespace std;

class Node{


public:
    board bd;
    int color;
    std::vector<point> untriedMoves;
    std::vector<Node*> childNodes;
    Node *parentNode;
    int visits;
    int wins;
    point move;

    Node(){

    }
    Node(board bd, int color):
            bd(bd),color(color){
        visits=0;
        wins=0;
        this->move=point(0,0);
        this->untriedMoves=bd.getAvaliable(color);
        this->parentNode=NULL;
    }
    Node &operator=(const Node &nodetmp){

        if(this!=&nodetmp){

            this->bd=nodetmp.bd;
            this->color=nodetmp.color;
            this->untriedMoves=nodetmp.untriedMoves;
            this->parentNode=nodetmp.parentNode;
            this->childNodes=nodetmp.childNodes;
            this->wins=nodetmp.wins;
            this->visits=nodetmp.visits;
            this->move=nodetmp.move;

        }
        return *this;
    }

    void update(double won);
    Node* treePolicy();
    Node* expand();
    Node* bestChild();
    double defaultPolicy(board bd);
    void backup(double score);


};

class player {
public:
    player(int color) : colorflag(color) {}

    int showColor();

    point nextMove(const board &bd);

    point tryMonteCarloTreeSearch(const board &bd, int maxTries);


private:
    int colorflag;
    int maxTries = 1500;
};