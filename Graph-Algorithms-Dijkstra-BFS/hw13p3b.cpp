#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

class PuzzleBoard {
    private:
        int boardSize;
        vector< vector<int> > board;
        /*storing the distances ("jump values") for each cell in the grid*/
        int currentRow, currentCol;

        bool isValid(int row, int col) const {
            return row >= 0 && row < boardSize && col >= 0 && col < boardSize;
            /*checking whether the row and column are within the bounds*/
        }
    public:
        PuzzleBoard(int newBoardSize, vector< vector<int> > newBoardValues = {})
        /*parametherized constructor*/
        {
            boardSize = newBoardSize;
            currentRow = 0;
            currentCol = 0;

            if(!newBoardValues.empty()) {
                board = newBoardValues;
                /*use the given board if it was provided*/
            } else {
                srand(time(0));
                /*seed for random value*/
                board.resize(boardSize, vector<int>(boardSize));
                /*creating a 2D board grid with boardSize x boardSize cells
                this essential for accesing each cell like board[i][j]*/
                for(int i = 0; i < boardSize; i ++) {
                    for(int j = 0; j < boardSize; j ++) {
                        board[i][j] = rand() % (boardSize - 1) + 1;
                        /*filling the board with random values from 1 to 
                        boardSize - 1*/
                    }
                }
            }
        }
        bool makeMove(int direction) {
            int jump = board[currentRow][currentCol];
            /*getting the jump values at current row and current column*/
            int newRow = currentRow;
            int newCol = currentCol;

            switch (direction) {
                case 0: newRow = newRow - jump;/*north(up)*/
                        break;
                case 1: newCol = newCol + jump;/*west(right)*/
                        break;
                case 2: newRow = newRow + jump;/*south(down)*/
                        break;
                case 3: newCol = newCol - jump;/*east(left)*/
                        break;
                default: return false;/*invalid move*/
            }
            if(isValid(newRow, newCol)) 
            /*if the result is within bounds*/
            {
                currentRow = newRow;
                currentCol = newCol;
                return true;
                /*update and return true*/
            }
            return false;
        }
        bool getResult() {
            return currentRow == boardSize - 1 && currentRow == boardSize - 1;
            /*check if we reached our goal: last row last col*/
        }
        friend ostream& operator<<(ostream &os, const PuzzleBoard &puzzle)
        /*overloding the << operator to print the PuzzleBoard object*/
        {
            for (int i = 0; i < puzzle.boardSize; i ++) {
                for (int j = 0; j < puzzle.boardSize; j ++) {
                    if (i == puzzle.currentRow && j == puzzle.currentCol) {
                        os << "[" << puzzle.board[i][j] << "]";
                        /*printing current position within []*/
                    } else {
                        os << " " << puzzle.board[i][j] << " ";
                        /*printing regular cell*/
                    }
                }
                cout << endl;
            }
            return os;
            /*returning output stream*/
        }
        int solve() {
            vector< vector<bool> > visited(boardSize, vector<bool>(boardSize, 
                false));/*creating a 2D visited array initialized to false*/
            queue< pair<int, int> > queue;
            /*queue to store positions to explore*/

            queue.push({0, 0});
            visited[0][0] = true;
            /*start from (0, 0) marking it as visited*/
        
            while (!queue.empty()) {
                pair<int, int> position = queue.front();
                /*getting the current position*/
                int row = position.first;
                int col = position.second;
                /*extracting row and column from pair*/
                queue.pop();
                /*deleting the pair after accesing it*/
                int jump = board[row][col];
                /*getting the jump distance of the current position*/
        
                vector< pair<int, int> > directions = {
                    {row - jump, col}, {row + jump, col}, {row, col + jump},
                     {row, col - jump}
                };
        
                for (pair<int, int> direction : directions)
                /*looping through each possible direction*/
                {
                    int r = direction.first;
                    int c = direction.second;
        
                    cout << "checking position : (" << r << ", ";
                    cout << c << ")" << endl;
        
                    if (isValid(r, c) && !visited[r][c]) 
                    /*position is valid and not yet visited*/
                    {
                        visited[r][c] = true; /*mark as visited*/
                        if (r == boardSize - 1 && c == boardSize - 1) {
                            cout << "Goal reached!" << endl;
                            return 1;  
                        }
                        queue.push({r, c});
                        /*otherwise, we add the new position to the queue
                        for further exploration*/
                    }
                }
            }
        
            cout << "no solution found" << endl;
            return -1;  
        }
};
        
int main() {
    PuzzleBoard puzzle(4);

    cout << "Initial Puzzle Board : " << endl;
    cout << puzzle << endl;

    puzzle.makeMove(1);
    puzzle.makeMove(2);

    cout << "After moves : " << endl;
    cout << puzzle << endl;

    if(puzzle.getResult()) {
        cout << "You Solved the puzzle" << endl;
    } else {
        cout << "Not yet solved" << endl;
    }
    int result = puzzle.solve();
    if(result == 1) {
        cout << "solvable" << endl;
    } else {
        cout << "not solvable" << endl;
    }
    return 0;
}