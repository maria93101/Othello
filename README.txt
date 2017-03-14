Describe how and what each group member contributed for the past two weeks. If you are solo, these points will be part of the next section.

We both contributed equally to implementing the random AI, as well as the AI that 
beats SimplePlayer (non-inclusive of the minimax). We then worked separately on the
minimax algorithm. Sasha implemented the minimax algorithm non-recursively, and Maria adapted it to make it recursive. 

Document the improvements that your group made to your AI to make it tournament-worthy. Explain why you think your strategy(s) will work. Feel free to discuss any ideas were tried but didn't work out.

We implemented a heuristic that takes into account the position of the move and 
weights the moves depending on whether they are adjacent to a corner piece, 
(disadvantageous), or a corner piece (advantageous). This works in tandem with the
minimax algorithm, which maximizes our minimum gain. Last week, we had seperately implemented the minimax and heuristic functions, and this week, we put together the two approaches. However, our code results in White winning most of the time; could you let us know what the bug was :)
