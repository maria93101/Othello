#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    int evaluate(Move *move, Board board);
    int better_evaluate(vector<Move>  legal_moves);
    int minimax(Side side, Board board, int depth);
    bool adjacent_to_corner(Move *move);
    bool corner(Move *move2);
    Board board;

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
protected:
	Side side_other;
	Side my_side;
	Move best_move = Move(0, 0);
};

#endif
