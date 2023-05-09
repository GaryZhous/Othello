#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <cstring>
using namespace std;

void initializing(char board[][26], int n){
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++){
      if(i == n/2 - 1 && j == n/2 - 1)
        board[i][j] = 'W';
      else if(i == n/2 - 1 && j == n/2)
        board[i][j] = 'B';
      else if(i == n/2 && j == n/2)
        board[i][j] = 'W';
      else if(i == n/2 && j == n/2 - 1)
        board[i][j] = 'B';
      else
        board[i][j] = 'U';
  }
}

void printBoard(char board[][26], int n) {
  cout << "  ";
  for(int i = 0;i<n;i++)
    printf("%c", 'a' + i);
  cout << "\n";
  int count = 0;
  for(int j = 0;j<n;j++){
    for(int g = 0;g < n + 2;g++){
      if(g==0)
        printf("%c", 'a' + count);
      else if(g==1)
        printf(" ");
      else
        printf("%c", board[j][g-2]);
    }
    count++;
    cout << "\n";
  }
}

bool positionInBounds(int n, int row, int col){
  return !(row < 0 || row > n-1 || col < 0 || col > n-1);
}

bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol){
            char opposite =(colour == 'W')?'B':'W';
  for(int i = 1;positionInBounds(n, row + deltaRow*i, col + deltaCol*i) && board[row + deltaRow*i][col + deltaCol*i] != 'U'&&board[row + deltaRow*i][col + deltaCol*i] != colour;){
    i++;
    if(positionInBounds(n, row + deltaRow * i, col + deltaCol * i)&&board[row + deltaRow*i][col + deltaCol*i] == opposite)
      continue;
    else if(positionInBounds(n, row + deltaRow * i, col + deltaCol * i)&&board[row + deltaRow*i][col + deltaCol*i] == colour)
      return true;
  }
  return false;               
}

bool valid(char board[][26], int n, int row, int col, char currentPlayer){
  bool ok = false;
  if (board[row][col] == 'U'){
      for(int deltaRow = -1; deltaRow <= 1; deltaRow++){
          for (int deltaCol = -1; deltaCol <= 1; deltaCol++){
              if (deltaRow == 0 && deltaCol == 0)
                      continue;
              else
                  if(checkLegalInDirection(board, n, row, col, currentPlayer, deltaRow, deltaCol))
                           ok = true;
                }  
            }
     }
  return ok;
}

void getMoveList(char board[][26], int n, int moveX[], int moveY[], int *numMoves, char color){
  *numMoves = 0;
	for (int x = 0; x < n; x++)
		for (int y = 0; y < n; y++){
			if (valid(board,n, x, y, color)){
				moveX[*numMoves] = x;
				moveY[*numMoves] = y;
				(*numMoves)++;
			}
		}
}

bool gameOver(char board[][26], int n){
	int numWMoves, numBMoves;
  for(int x = 0; x < n; x++)
    for(int y = 0;y<n;y++){
      if(valid(board, n, x, y, 'W'))
        numWMoves++;
      if(valid(board, n, x, y, 'B'))
        numBMoves++;
    }
  
	if (numWMoves == 0 && numBMoves == 0)
		return true;
	return false;
}

int score(char board[][26],int n, char color){
  int sum = 0;
	for (int x = 0; x < n; x++)
		for (int y = 0; y < n; y++)
			if (board[x][y] == color)
				sum++;
	return sum;
}

void copyBoard(char src[][26], char dest[][26], int n){
	memcpy(dest, src, sizeof(src[0])*n);
}

int heuristic(char board[][26], int n, char turn){
	char opponent = (turn == 'W')?'B':'W';
	int myScore = score(board, n, turn);
	int opponentScore = score(board, n, opponent);
	return myScore - opponentScore;
}

void changecolor(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){
    for(int i = 1;positionInBounds(n, row + deltaRow*i, col + deltaCol*i) && board[row + deltaRow*i][col + deltaCol*i] != colour;i++)
      board[row + (deltaRow * i)][col + (deltaCol * i)] = colour;
}

void testMove(char board[][26], int n, int row, int col, char color){
  if ((positionInBounds(n, row, col)) && (board[row][col] == 'U')){
    for (int deltaRow = -1; deltaRow < 2; deltaRow++)
      for (int deltaCol = -1; deltaCol < 2; deltaCol++){
        if(deltaCol == 0 && deltaRow == 0)
          continue;
        if(checkLegalInDirection(board, n, row, col, color, deltaRow, deltaCol)){
          board[row][col] = color;
          changecolor(board, n, row, col, color, deltaRow, deltaCol);
       }
        }
}
}

int minimaxValue(char board[][26], int n, char originalTurn, char currentTurn, int depth){
	if (depth == 2 || gameOver(board, n))
		return heuristic(board, n, originalTurn);
	int moveX[60], moveY[60];
	int numMoves;
	char opponent = (currentTurn == 'W')?'B':'W';

	getMoveList(board, n, moveX, moveY, &numMoves, currentTurn);
	if (numMoves == 0)
		return minimaxValue(board, n, originalTurn, opponent, depth + 1);
	else{
		int bestMoveVal = -99999;
		if (originalTurn != currentTurn)
			bestMoveVal = 99999;
		for (int i = 0; i < numMoves; i++){
			char tempBoard[26][26];
			copyBoard(board, tempBoard, n);
			testMove(tempBoard, n, moveX[i], moveY[i], currentTurn);
			int val = minimaxValue(tempBoard, n, originalTurn, opponent, depth + 1);
			if (originalTurn == currentTurn){
				if (val > bestMoveVal)				
					bestMoveVal = val;				
			}
			else{
				if(val < bestMoveVal)
					bestMoveVal = val;
			}
		}
		return bestMoveVal;
	}
	return -1;
}

int makeMove(char board[][26], int n, char turn, int *row, int *col){
  int moveX[60], moveY[60];
	int numMoves;
	char opponent = (turn == 'W')?'B':'W';
	getMoveList(board, n, moveX, moveY, &numMoves, turn);
	if (numMoves == 0){
		*row = -1;
		*col = -1;
	}else{
		int bestMoveVal = -99999;
		int bestX = moveX[0], bestY = moveY[0];
		for (int i = 0; i < numMoves; i++){
			char tempBoard[26][26];
			copyBoard(board, tempBoard, n);
			testMove(tempBoard, n, moveX[i], moveY[i], turn);
			int val = minimaxValue(tempBoard, n, turn, opponent, 1);
			if (val > bestMoveVal)
			{
				bestMoveVal = val;
				bestX = moveX[i];
				bestY = moveY[i];
			}
		}
		*row = bestX;
		*col = bestY;
	}
  return 0;
}

int main(){
	char board[26][26];
        int n;
	char computerColor;
  cout << "Enter the board dimension: ";
  cin >> n;
  cout << "Computer plays (B/W): ";
  cin >> computerColor;
  char turn = 'B';
  char humanColor = (computerColor == 'W')?'B':'W';
	initializing(board, n);
	while (!gameOver(board, n)){
		printBoard(board, n);
		char row, col;
		if (turn == humanColor){
			cout << "Enter move for colour " << humanColor <<" (RowCol): ";
      cin >> row;cin >> col;
    }
		else{
      int trow = row - 'a', tcol = col - 'a';
			makeMove(board, n, turn, &trow, &tcol);
    }
		if (valid(board, n, row - 'a', col - 'a', turn) || (row == 'a' - 1)){
			if (row != 'a' - 1)
				testMove(board,n, row - 'a', col - 'a', turn);
			turn = (turn == humanColor)?computerColor:humanColor;
		}
		else{
      cout << "invalid move. Game over!" <<endl;
      break;
    }
	}
	return 0;
}
