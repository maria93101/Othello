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
 * Takes in a legal move, and returns true if the move is adjacent to a corner piece, and false otherwise!
 */
bool Player::adjacent_to_corner(Move *move)
{
	// checking if move is top left adjacent corner
	bool tl = (move->getX() == 1 and move->getY() == 0) or (move->getX() == 0 and move->getY() == 1) or (move->getX() == 1 and move->getY() == 1);

	//bottom left etc......
	bool bl = (move->getX() == 0 and move->getY() == 6) or (move->getX() == 1 and move->getY() == 7) or (move->getX() == 1 and move->getY() == 6);

	bool tr =  (move->getX() == 6 and move->getY() == 0) or (move->getX() == 6 and move->getY() == 1) or (move->getX() == 7 and move->getY() == 1);

	bool br = (move->getX() == 6 and move->getY() == 7) or (move->getX() == 7 and move->getY() == 6) or (move->getX() == 6 and move->getY() == 6);
	return tl or bl or tr or br;
}

/*
 * Takes in a legal move, and returns a integer value representing the "goodness" of the move. 
 * This is calculated by subracting the number of pieces of your color and subtracting the number of 
 * pieces of your opponent's color, accounting for places on the board that are more or less desirable.
 */
int Player::evaluate(Move *move, Board board)
{
	//Create copy of board
	Board *copy = board.copy();
	

	// Making inputted move on the copy.
	copy->doMove(move, my_side);
	int my_points = copy->count(my_side);
	int their_points = copy->count(side_other);

	// If the move is one of the four corner pieces, add three to my score.
	if ((move->getX() == 0 and move->getY() == 0) or (move->getX() == 7 and move->getY() == 0) or (move->getX() == 0 and move->getY() == 7) or (move->getX() == 7 and move->getY() == 7))
	{
		my_points += 3;
	}

	// If it is adjacent to a corner piece, subtract three to my score. 
	// I'm calling a helper function in order to determine if I'm adjcent to a corner :)
	if(this->adjacent_to_corner(move))
	{
		my_points -= 3;
	}

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

    
    
	// Code for the AI that beats SimplePlayer
	
	/*
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
					int temp_value = this->evaluate(new Move(temp), board);
					moves_values.push_back(temp_value);
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
		board.doMove(&legal_moves[max_index], my_side);
		return new Move(legal_moves[max_index]);
	}
	else 
	{
		return nullptr;
	}
	*/
	
	
	// IMPLEMENTATION OF MINIMAX
	
	vector<Move> legal_moves;
	
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
				} 
			}
		}
		
		//Create a copy of board
		Board *copyboard = board.copy();
		
		// Go through our vector of possible moves that we can make and 
		// apply them to the copy of the board. Then evaluate all the 
		// possible moves of our opponent and minimize their gain. 

		vector<Move> opponents_moves;
		vector<int> opponents_values;
		vector<int> minimum_values;
		temp = Move(0, 0);
		
		for (int x = 0; x < legal_moves.size(); x++) {
			
			copyboard->doMove(&legal_moves[x], my_side);
			
			if (copyboard->hasMoves(side_other)) {
				// Evaluate the  possible moves of the opponent. 
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						temp = Move(i, j);
						if (copyboard->checkMove(&temp, side_other)) 
						{
							opponents_moves.push_back(temp);
							int temp_value = this->evaluate(new Move(temp), *copyboard);
							opponents_values.push_back(temp_value);
						} 
					}
				}
			} 	
			
			// Find the minimum value outputted by the heuristic helper 
			// function in order to consider the worst possible scenario 
			// that a particular move could result in. 
			
			int min_index = 0;
			for (int i = 0; i < opponents_values.size(); i++)
			{
				if(opponents_values[min_index] > opponents_values[i])
				{
					min_index = i;
				}
			}
			
			// Add the minimum value to the minimum_values vector
			minimum_values.push_back(opponents_values[min_index]);
			
			// Clear the vectors opponents_moves and opponents_values
			// before evaluating our next possible move. 
			
			opponents_moves.clear();
			opponents_values.clear();
			
			// Reset copyboard to the original state of the board
			copyboard = board.copy();
			
		}
		
		// Find the index of the maximum value in the minimum_values 
		// vector, which minimizes our loss. 
		
		int max_index = 0;
		for (int i = 0; i < minimum_values.size(); i++)
		{
			if(minimum_values[max_index] < minimum_values[i])
			{
				max_index = i;
			}
		}
		
		// Make the move that minimizes our losses on the real board
		board.doMove(&legal_moves[max_index], my_side);
		return new Move(legal_moves[max_index]);
	}
	
	else 
	{
		return nullptr;
	}
	
	
}
