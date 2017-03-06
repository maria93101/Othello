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
 * Takes in a legal move, and returns a integer value representing the "goodness" of the move. 
 * This is calculated by subracting the number of pieces of your color and subtracting the number of 
 * pieces of your opponent's color.
 */
int Player::evaluate(Move *move)
{
	//Create copy of board
	Board *copy = board.copy();
	

	// Making inputted move on the copy.
	copy->doMove(move, my_side);
	int my_points = copy->count(my_side);
	int their_points = copy->count(side_other);

	// if the move is a corner piece, add three to my score.

	// if it is adjacent to a corner piece

	return my_points - their_points;

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

     /*
	THIS IS CODE FOR THE RANDOM AI!

     vector<Move> legal_moves;
    
     Move temp = Move(0, 0);
     board.doMove(opponentsMove, side_other);
	 if (board.hasMoves(my_side)) {
		 for (unsigned int i = 0; i < 8; i++) {
			 for (unsigned int j = 0; j < 8; j++) {
				 temp = Move(i, j);
				 if (board.checkMove(&temp, my_side)) {
					 legal_moves.push_back(temp);
					 board.doMove(&temp, my_side);
					 return new Move(temp);
				 } 
			 }
		 }
	 }
	 else {
		return nullptr;
	}
	*/

	/*
	if we have a possible legal move:
		Add legal moves to a vector
		Assign high values to moves that have opposite color circles adjacent to them and ...
		Make each possible move on a copy of the board and check how many circles are white/black and assign in a value in a vector. 
		Return the move with the highest value

	else:
		pass

	*/

	vector<Move> legal_moves;
	vector<int> moves_values;
    

     Move temp = Move(0, 0);
     // Keeping track of board state.
     board.doMove(opponentsMove, side_other);

	if (board.hasMoves(my_side)) 
	{
		 for (int i = 0; i < 8; i++) 
		 {
			for (int j = 0; j < 8; j++) 
			{
				temp = Move(i, j);
				 
				if (board.checkMove(&temp, my_side)) 
				{
					legal_moves.push_back(temp);
					int temp_value = this->evaluate(new Move(temp));
					moves_values.push_back(temp_value);
					std::cerr << "blah " << temp_value << std::endl;
				} 
			}
		}

		// Looks for the move with the best value
		int max_index = 0;
		for (int i = 0; i < moves_values.size(); ++i)
		{
			if(moves_values[max_index] < moves_values[i])
			{
				max_index = i;
			}
		}
		std::cerr << "best value " << moves_values[max_index] << std::endl;
		board.doMove(&legal_moves[0], my_side);
		return new Move(legal_moves[0]);
	}
	else 
	{
		return nullptr;
	}
	
}
