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
     best_move = Move(0,0);
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

bool Player::corner(Move *move)
{
	return (move->getX() == 0 and move->getY() == 0) or (move->getX() == 7 and move->getY() == 0) or (move->getX() == 0 and move->getY() == 7) or (move->getX() == 7 and move->getY() == 7);
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
	if(this->corner(move))
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
 * Go through all the moves in the board and calculate our own "count" value 
 * given a vector of the legal moves.
 */
int Player::better_evaluate(vector<Move> legal_moves)
{
	int my_points = board.count(my_side);
	int their_points = board.count(side_other);
	for (int i = 0; i < legal_moves.size(); ++i)
	{
		if(this->corner(new Move(legal_moves[i])))
		{
			my_points += 3;
		}

	
		if(this->adjacent_to_corner(new Move(legal_moves[i])))
		{
			my_points -= 3;
		}
	}
	return my_points - their_points;
}

/*
 * Takes in a side, board object, and depth to search to
 * and returns the maximum value of the board (not optimizing for corners and edges).
 * Also sets best_move to the highest value move.
 */
int Player::minimax(Side side, Board board, int depth)
{
    Side other;
    if (side == BLACK) {
		 other = WHITE;
	}
	else 
		other = BLACK;

	vector<Move> legal_moves;
	Move temp = Move(0, 0);
	// Adding all the moves to a vector
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++) 
		{
			temp = Move(i, j);
				 
			if (board.checkMove(&temp, side)) 
			{
				legal_moves.push_back(temp);
			} 
		}
	}

	if (depth == 0) // base case
	{
		return better_evaluate(legal_moves);
		//int my_points = board.count(side);
		//int their_points = board.count(other);
		//return my_points - their_points;
	}

	if (!board.hasMoves(side)) // There are no moves to be made
	{
		if (!board.hasMoves(other)) // opponent also has no moves.. game over
		{
			return better_evaluate(legal_moves);
			//int my_points = board.count(side);
			//int their_points = board.count(other);
			//return my_points - their_points;  // do we ever need to do anything with this value?
		}
		// means we have to pass this turn
		return -minimax(other, board, depth - 1);
	}

	// Maximize the value of the resulting boards
	Board copyboard = *board.copy();
	vector<Move> values;
	int max_value = -10000000;
	Move max_move = Move(0,0);
	for (int i = 0; i < legal_moves.size(); ++i)
	{
		copyboard.doMove(&legal_moves[i], side);

		int temp = -minimax(other, board, depth - 1);
		if (temp > max_value)
		{
			max_value = temp;
			max_move = legal_moves[i];
		}

		copyboard = *board.copy();
	}

	//return move with max value
	best_move = max_move;
	return max_value;
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

    
    /*
	// Code for the AI that beats SimplePlayer

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
		minimax(my_side, board, 2);
		board.doMove(&best_move, my_side);
		return new Move(best_move);

	}
	
	else 
	{
		return nullptr;
	}
	
}
