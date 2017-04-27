#include "player.h"


int player::showColor() {
    return colorflag;
}

point player::nextMove(const board &bd) {

    return tryMonteCarloTreeSearch(bd, maxTries);
}

point player::tryMonteCarloTreeSearch(const board &bd, int maxTries) {


}
