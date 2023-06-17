#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;





// Define the game board as a 2D vector of characters
vector<vector<char>> board(7, vector<char>(7, 'O'));
vector<vector<char>> boardCopy(7, vector<char>(7, 'O'));

string directionStr(int k) {
    switch (k) {
        case 0:
            return "DOWN";
        case 1:
            return "UP";
        case 2:
            return "RIGHT";
        case 3:
            return "LEFT";
        default:
            return "invalid";
    }
}

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

// Check if a given move is valid
bool isValidMove(int x, int y, int dx, int dy) {
    // Check if the move is within the bounds of the board
    if (x+2*dx < 0 || x+2*dx >= 7 || y+2*dy < 0 || y+2*dy >= 7) {
        return false;
    }

    // Check if the current cell contains a piece to move
    if (board[x][y] != 'N') {
        return false;
    }

    // Check if the destination cell is empty
    if (board[x+2*dx][y+2*dy] != 'O') {
        return false;
    }

    // Check if the intermediate cell contains a piece to jump over
    if (board[x+dx][y+dy] != 'N') {
        return false;
    }

    // Check if the destination cell is not a forbidden cell
    if (board[x+2*dx][y+2*dy] == 'X') {
        return false;
    }

    return true;
}



void makeMove(int x, int y, int dx, int dy) {
    // Check if the move is valid
    if (!isValidMove(x, y, dx, dy)) {
        return;
    }

    // Store the current state of the board in boardCopy
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            boardCopy[i][j] = board[i][j];
        }
    }

    // Make the move
    board[x][y] = 'O';
    board[x+dx][y+dy] = 'O';
    board[x+2*dx][y+2*dy] = 'N';


}

void undoMove() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            board[i][j] = boardCopy[i][j];
        }
    }
}

// Function to print the board
void printBoard(vector<vector<char>>& board) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

// function to solve the game
bool solveGame() {
    // Check if there is only one piece left at the center
    int count = 0;
    for (int i = 2; i <= 4; i++) {
        for (int j = 2; j <= 4; j++) {
            if (board[i][j] == 'N') {
                count++;
            }
        }
    }
    if (count == 1 && board[3][3] == 'N') {
        return true;
    }
    
    // Try all possible moves
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == 'N') {
                // Check all possible directions
                for (int k = 0; k < 4; k++) {
                    if (isValidMove(i, j, dx[k], dy[k])) {
                        makeMove(i, j, dx[k], dy[k]);
                        if (solveGame()) {
							char row = j + 'A';
                            int col = i + 1;
                            cout <<row << col << " " << directionStr(k) << endl;
                            return true;
                        }
                        undoMove();
                    }
                }
            }
        }
    }
    
    // No solution found
    return false;
}



int main() {

    // read 7 lines of input
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            char c;
            cin >> c;
            board[i][j] = c;
        }
        // read and discard the newline character at the end of each line
        cin.ignore();
    }
	if(!solveGame())
	{
		cout<<"Loser"<<endl;
	}
	
	

    return 0;
}
