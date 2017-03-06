#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
	// Changes made by Sasha. 
	
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     
     board = Board();
     my_side = side;
     if (side == BLACK) {
		 side_other = WHITE;
	 }
	 else 
		side_other = BLACK;

}

/*
 * Destructor for the player.
 */
Player::~Player() {
	
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
     
     // Initialize a vector with all 64 moves
     vector<Move> legal_moves;
     for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 8; j++) {
			legal_moves.push_back(Move(i, j));
		}
	}
     
    std::cerr << legal_moves.size() << std::endl; 

    for (int i = legal_moves.size() - 1; i >= 0; i--) {
		if (! board.checkMove(&legal_moves[i], my_side)) {
			legal_moves.pop_back();
			std::cerr << "blah" << i << std::endl;
		}
	}
	
	if (legal_moves.size() != 0) {
		board.doMove(&legal_moves[0], my_side);
		return &legal_moves[0];
	}
		
	else {
		return nullptr;
	}
		
			
    
   /*
     Move temp = Move(0, 0);
     board.doMove(opponentsMove, side_other);
	 if (board.hasMoves(my_side)) {
		 for (unsigned int i = 0; i < 8; i++) {
			 for (unsigned int j = 0; j < 8; j++) {
				 temp = Move(i, j);
				 if (board.checkMove(&temp, my_side)) {
					 // legal_moves.push_back(temp);
					 board.doMove(&temp, my_side);
					 return &temp;
				 } 
			 }
		 }
		 // board.doMove(&legal_moves[0], my_side);
		 // return &legal_moves[0];
	 }
	 else {
		return nullptr;
	}
	*/
	
}
