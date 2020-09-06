# Chess-C

Features: 

A. 2-player chess, creates chessboard for two players to play chess on. Win-check algorithm checks for winner every turn.

B. 1-player chess, creates chessboard for one player to play chess on with an AI. 

          > AI first generates all of the possible moves it can make given the current board condition. 
             > Iterates over each piece and runs math to see which places it can move to. 
          > Runs position-evaluation. Checks to see which move is the highest valuation (based on pieces on the board) and runs that.
             > In each iteration, see value of board based on own pieces (- value) and opponent pieces (+ value)
             > Based on position on board, each piece has different valuations.
          > Run Minimax algorithm and use valuation function to determine best move to make.
             > Recursively see what each move will do on the board. Each leaf will result in a valuation -- choose the leaf that either
               minimizes loss or maximizes win.
             > Use Alpha-beta pruning to reduce amount of branches to be scanned. Effectively, if given branch is lower in value than 
               an already found branch, discard the branch.
          > Make move. 

C.0-player chess, steps through a sample match of two AI players. 

          > Uses above discussed algorithm with two AI at the same time. 













