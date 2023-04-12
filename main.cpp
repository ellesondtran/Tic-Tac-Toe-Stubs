//Elleson Tran
//Roberts
//Matrix

#include <iostream>
#include<vector>
#include "m/matrix.h"

using namespace std;

//what's initially in the board
const char ORIG = ' '; 

/*Loops over the game board.
Displays the contents of each element.
Elements on same row have a | between them.
Each row is on a new line.
The board contains no horizontal lines
*/
void show(matrix<char>&board)
{
  for(int row = 0; row < board.numRows(); row++){
    cout<<"|";
    for(int col = 0; col < board.numCols(); col++){
      cout<<board[row][col]<<"|";
    }
    cout<<endl;
  }
}

/*Determines if the row(r) and column(c) are valid.
If valid, the function returns true, and if not, false.
Validation should make sure the specified row and column actually exist on the board.
It should also make sure someone has not already played inside the element.
*/

bool validMove(matrix<char>&board, int r, int c)
{
  if(r < 0  || r > 2){//if the row is out of bounds
    return false;
  }
  if(c < 0 || c > 2){//if the column is out of bounds
    return false;
  }

  if(board[r][c] == 'o' || board[r][c] == 'x'){//if there is something in the spot already
    return false;
  }

  return true;
}

/*Asks the user for the row and column
until a valid move has been specified.
Calls validMove to verify this (and control a loop).
Once a valid move is specified, marks the 
board with the player's symbol, which is inside p
*/
void makeMove(matrix<char>&board, char p)
{
  int row, column;

  do{//keeps going if the player chooses wrong rows or columns
    cout<<"Row (0-2): ";
    cin>>row;

    cout<<"Column (0-2): ";
    cin>>column;

  }while(validMove(board, row, column) == false);

  //marks it once it has a valid move
  board[row][column] = p;

}

/*Determines if the game is over.
Checks for vertical, horizontal and diagonal wins.
Also checks for the game ending in a draw (tie). If a tie is detected,
Set moves equal to 99.
Returns true when win has occurred or tie has occurred.
*/
bool checkWin(const matrix<char>&board, char p, int &moves)
{ 
  int marks = 0;
  //checks for vertical wins
  for(int col = 0; col < board.numCols(); col++){
    for(int row = 0; row < board.numRows(); row++){//goes through the entire column
      if(board[row][col] == p){//if the current spot has players mark
        marks = marks + 1; //adds to win
      }
    }
    //after this column is checked for markings of the player

    if(marks == 3){//if all three spots were marked, player wins
      return true;
    }
    else{//if all three spots were not marked by the player
      marks = 0; //sets the wins to 0 again
    }
  }

  //checks for horizontal wins
  for(int row = 0; row < board.numRows(); row++){
    for(int col = 0; col < board.numCols(); col++){//goes through the entire row 
      if(board[row][col] == p){//if the current spot has players mark
        marks = marks + 1; //adds to win
      }
    }
    //after this row is checked for markings of the player

    if(marks == 3){//if all three spots were marked, player wins
      return true;
    }
    else{//if all three spots were not marked by the player
      marks = 0; //sets the wins to 0 again
    }
  }

  //checks for diagnol wins

  for(int x = 0; x < 3; x++){//top left to bottom right diagnol check
    if(board[x][x] == p){
      marks = marks + 1;
    }
  }
  if(marks == 3){//if all three spots were marked, player wins
      return true;
    }
  else{//if all three spots were not marked by the player
      marks = 0; //sets the wins to 0 again
  }

  int row = 0;
  int col = 2;
  for(int x = 0; x < 3; x++){//top right to bottom left diagnol check
    if(board[row][col] == p){
      marks = marks + 1;
    }
    row = row + 1;//goes down one row;
    col = col - 1;//goes back one column
  }
  if(marks == 3){//if all three spots were marked, player wins
      return true;
    }
  else{//if all three spots were not marked by the player
      marks = 0; //sets the wins to 0 again
  }

  //if non of the checks go through
  if(moves == 9){//checks if all the spots are filled and no winners
    moves = 99;
    return true;
  }

  //if goes through EVERYTHING returns false
  return false;
}



int main()
{

  //ORIG is a constant for the character marking empty spots on the board
	matrix<char>brd(3,3,ORIG);


  //symbol representing current player
  char player='o'; 

  //total number of moves made so far (9 moves without a win means a tie)
	int moves=0; 

	do{

    //count the move
		moves++; 

    //toggle between players so turns alternate
		if(player=='x') 
			player='o';
		else
			player='x';

    //draw the board
		show(brd); 

    //work through player's move
		makeMove(brd,player); 

  //see if the game is over
	}while(!checkWin(brd,player, moves)); 

  //tie game - no one wins
	if(moves==99)
		cout<<"Draw"; 
	else
  {
    //current player wins
		cout<<"Player: "<<player<<" Wins!"; 
  }

	return 0;
}

