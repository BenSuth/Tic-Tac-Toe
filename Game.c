#include <stdio.h>

/*
* Ben Sutherland
*/
void InitializeBoard(int m, int n , char board[][n]);
void PrintBoard(int m, int n, char board[][n]);
void CreateBoard(int m, int n, char board[][n]);
int IsValidBoard(int m, int n, char board[][n]);
void ListWinningCells(int m, int n, char board[][n]);
char WhoIsTheWinner(int m, int n, char board[][n]);
char RowWinner(int, int, char [], char);
char ColumnWinner(int, int, char col[], char);
char DiagonalWinnerL(int, int, char [], char);
char DiagonalWinnerR(int, int, char [], char);

int main (void)
{
  char temp; //temporary storage variable
  char menu = '0';
  char marker; //stores the markers 'X' and 'O'
  int cell; //stores the index of the char board

  char board[3][3];//3x3 
  InitializeBoard(3,3,board);
  
  do 
  {
    //menu prompt
    puts("\npress 'p' to print the tic-tac-toe board\npress 'c' to create a tic-tac-toe board with some X and O cells\npress 't' to test if a tic-tac-toe board is valid or invalid\npress 'w' to predict winning cell for for player X or O\npress 'f' to check the board for a winner\npress 'e' to exit");

    scanf ("%s", &menu);

    switch (menu)
    {
      //print board
      case 'p':
        PrintBoard(3,3,board);
        break;

      //Prompt for inserting Xs and Os, -1 to exit loop
      case 'c':
        cell = 0;
        //-1 is the exit condition 
        while (cell != -1)
        {  
          //prompt for position on the board
          //loop if invalid input
          do
          {
            puts("Enter a number of the cell where you want to insert X or 0 or enter -1 to exit");
            scanf("%d", &cell);
          } 
          while (cell > 9 || cell < -1);

          if (cell == -1) continue;
  
          //prompt for inputting 'X' or 'O' onto the board
          //loop if invalid input
          do 
          {
            puts("Type X or O");
            scanf("%s", &marker);
          } 
          while (marker != 'X' && marker != 'O');

          //assign the marker to the position inputted by user
          for (int i = 0; i < 3; i++)
          {
            for (int j = 0; j < 3; j++)
            {
              if (cell +'0' == board[i][j]) board[i][j] = marker; 
            }
          }  
          PrintBoard(3,3,board);
        }
        break;
      //checks if board is valid
      case 't': 
        (IsValidBoard(3,3,board)) ? puts("The Board is Valid"):puts("The Board is Invalid");
        break;

      //lists each players winning moves
      case 'w':
        ListWinningCells(3,3,board);
        break;

      //checks if either player has won the game 
      case 'f':
        //if temp == 'D' no winner was found 
        temp = WhoIsTheWinner(3, 3, board);
        if (temp == 'D') 
        {
          puts("There is no winner");
          break;
        }
        else 
        {
          printf("Player %c is the winner\n", temp);
          break;
        } 

      case 'e':
        break;
      default:
        puts("Invalid input");
        continue;
    }
  } while (menu != 'e');
return 0; 
}

/*
* initializes board with number 1-9 corresponding to there position
* INPUT: a 2D array, 2 integers for row and column size of array
* OUTPUT: VOID
*/
 void InitializeBoard(int m, int n , char board[][n])
{
  int c =1;

  for(int i =0; i<m; i++)
  {
    for(int j=0; j< n; j++){
    board[i][j] = c+'0';
    c++;
    }
  }
}//end InitializeBoard

/*
* prints the gameboard
* INPUT: a 2D array, 2 integers for row and column size of array
* OUTPUT: VOID
*/
void PrintBoard(int m, int n, char board[][n])
{

    for(int i =0; i<m; i++)
    {
      puts("     |     |     ");

      for(int j=0; j< n; j++){
      (j == n - 1) ? printf("  %c  \n", board[i][j]): printf("  %c  |", board[i][j]);
    }

    ( i < m - 1) ? puts("_____|_____|_____") : puts("     |     |     ");
  }
}

/*
* checks if the number of 'X's and 'O's are the same or 1 greater than the other
* if they are, the board is valid, ie. X=3, O = 2 -> valid board
* INPUT: a 2D array, 2 integers for row and column size of array
* OUTPUT: VOID
*/
int IsValidBoard(int m, int n, char board[][n])
{
  int counter=0;

  /* 
  loops through each position of array and adds 1 to counter for 'X' 
  and subtracts 1 for each 'O' 
  */
  for(int i =0; i<m; i++)
  {
    for(int j=0; j< n; j++)
    {
      if (board[i][j] == 'X') ++counter;
      if (board[i][j] == 'O') --counter;
    }
  }
  if (counter == 1 || counter == 0) return 1;
  return 0;
}

/*
* finds all winning moves for each player
* INPUT: a 2D array, 2 integers for row and column size of array
* OUTPUT: VOID
*/
void ListWinningCells(int m, int n, char board[m][n])
{
  //winning moves cannot exist if board is invalid
  if (!(IsValidBoard(3,3,board)))
  {
    puts("No winning moves, board is invalid");
    return;
  } 
  char swap; //used for swapping markers

  /*
  marker is the variable being checked and counter the variable that cannot be in the position of the winning move
  */
  char marker = 'O'; 
  char counter = 'X';

  // loop twice to check for player X and player O 
  for (int j = 0; j < 2; j++)
  {
    //swaps counter and marker
    swap = marker;
    marker = counter;
    counter = swap;

    printf("\nThe winning moves for %c are in cells: ", marker);
      for (int i = 0; i < m; i++)
      {
        //Check Rows for winners and prints all winning moves
        if (board[i][0] == marker)
        {
          if (board[i][1] == marker && board[i][2] != counter) printf("%c ", board[i][2]);
          if (board[i][2] == marker && board[i][1] != counter) printf("%c ", board[i][1]);          
        }
        else if (board[i][0] != counter && board[i][0] != marker)
        {
          if (board[i][1] == marker && board[i][2] == marker) printf("%c ", board[i][0]);
        }
        //Check Columns for winners and prints all winning moves
        if (board[0][i] == marker)
        {
          if (board[1][i] == marker && board[2][i] != counter) printf("%c ", board[2][i]);
          if (board[2][i] == marker && board[1][i] != counter) printf("%c ", board[1][i]);
        }
        else if (board[0][i] != marker && board[0][i] != counter)
        {
          if (board[1][i] == marker && board[2][i] == marker) printf("%c ", board[0][i]);
        }
      }// end for loop

      //Check diagnonals for winners and prints all winning moves
        if (board[0][0] == marker)
        {
          if (board[1][1] == marker && board[2][2] != counter) printf("%c ", board[2][2]);
          if (board[2][2] == marker && board[1][1] != counter) printf("%c ", board[1][1]); 
        }
          else if (board[0][0] != marker && board[0][0] != counter) 
        {
          if (board[1][1] == marker && board[2][2] == marker) printf("%c ", board[0][0]);
        }
        if (board[0][2] == marker)
        {
          if (board[1][1] == marker && board[2][0] != counter) printf("%c ", board[2][0]);
          if (board[2][0] == marker && board[1][1] != counter) printf("%c ", board[1][1]); 
        }
          else if (board[0][2] != marker && board[0][2] != counter) 
        {
          if (board[1][1] == marker && board[2][0] == marker) printf("%c ", board[0][2]);
        }

        puts("");
  }//end for loop j     
}//end function


/*
* Recursion
* checks each row for a winner
* INPUT: a 2D array, 2 integers for row and column size of array, 1 char for the marker
* OUTPUT: a char for who won or no winner
*/
char RowWinner(int m, int n, char board[], char marker)
{
  if (n == 0) return marker;
  if (board[0] == marker) return RowWinner(m,--n,&board[1],marker);
  if (board[0] != marker) return 'D';

  return '\0';
}

/*
* Recursion
* checks each column for a winner
* INPUT: a 2D array, 2 integers for row and column size of array, 1 char for the marker
* OUTPUT: a char for who won or no winner
*/
char ColumnWinner(int m, int n, char col[], char marker)
{
  if (m == 0) return marker;
  if (col[0] != marker) return 'D';
  if (col[0] == marker) return ColumnWinner(--m, n, &col[3], marker);
  return '\0';
}

/*
* Recursion
* checks diagonal for a winner
* INPUT: a 2D array, 2 integers for row and column size of array, 1 char for the marker
* OUTPUT: a char for who won or no winner
*/
char DiagonalWinnerL(int m, int n, char diag[], char marker)
{
  if (m == 0) return marker;
  if (diag[0] != marker) return 'D';
  if (diag[0] == marker) return DiagonalWinnerL(--m, n, &diag[4], marker);
  return '\0';
}

/*
* Recursion
* checks other diagonal for a winner
* INPUT: a 2D array, 2 integers for row and column size of array, 1 char for the marker
* OUTPUT: a char for who won or no winner
*/
char DiagonalWinnerR(int m, int n, char diag[], char marker)
{
  if (m == 0) return marker;
  if (diag[0] != marker) return 'D';
  if (diag[0] == marker) return DiagonalWinnerR(--m, n, &diag[2], marker);
  return '\0';
}

/*
* checks all potential rows, columns, and diagonals are checked for winners
* INPUT: a 2D array, 2 integers for row and column size of array, 1 char for the marker
* OUTPUT: a char for who won or no winner
*/
char WhoIsTheWinner(int m, int n, char board[][n])
{
  //checks row 0, column 0, and diagonal 0
  char marker = board[0][0];
  if (RowWinner(m, n, &board[0][0], marker) != 'D') return marker;
  if (ColumnWinner(m, n, &board[0][0] , marker) != 'D') return marker;
  if (DiagonalWinnerL(m, n, &board[0][0] , marker) != 'D') return marker;

  //checks row 1
  marker = board[1][0];
  if (RowWinner(m, n, &board[1][0], marker) != 'D') return marker;

  //checks row 2
  marker = board[2][0];
  if (RowWinner(m, n, &board[2][0], marker) != 'D') return marker;

  //checks column 1
  marker = board[0][1];
  if (ColumnWinner(m, n, &board[0][1] , marker) != 'D') return marker;

  //checks for column 2 and diagonal 2
  marker = board[0][2];
  if (ColumnWinner(m, n, &board[0][2] , marker) != 'D') return marker;
  if (DiagonalWinnerR(m, n, &board[0][2], marker) != 'D') return marker;
 
  //if no winner is found return 'D'
  return 'D';
}
