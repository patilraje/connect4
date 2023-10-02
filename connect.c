#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "slist.h"

#define ROWS 6
#define COLS 7

char board[ROWS][COLS];
int isWin=0;   //will play until the game has specified no. of tokens to declare a winner
char current='R';
int full=0; //to check if the board is full which would cause it to be a draw

slist list={NULL, NULL};

/*------------------------------------------------------
 *Initializing the board with spaces to print the grid
-------------------------------------------------------- */
void initializegrid()
{
	for(int i=0; i<ROWS; i++)
	{
		for(int j=0;  j<COLS; j++)
		{
			board[i][j]= ' ';
		}
	}
}



/*--------------------------------------
 *Function to display the game board
---------------------------------------- */
void displayBoard()
{
    // Print the board row by row
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }

    printf("------------------------------ \n");
}


/*--------------------------------------------------
 * Checks if the the board is full to declare a tie
---------------------------------------------------- */
int isFull()
{
	int n=0;

	 for (int i = 0; i < ROWS; i++)
	 {
		 for (int j = 0; j < COLS; j++)
		 {
			 if(board[i][j]!= ' ')
			 {
				 n++;
			 }
		 }
	 }

	 if(n== (ROWS*COLS))
	 {
		 full=1;
	 }

	return 0;
}




void addlist(int rows, int cols , char player)
{
	insertTail(&list, player, rows, cols);
}



/*----------------------------------------------------------------------
 * Will clear the list by iterating through it and freeing every node
------------------------------------------------------------------------ */
void clearList()
{
    struct node* current = list.head;
    while (current != NULL)
    {
        struct node* temp = current;
        current = current->next;
        free(temp);
    }
    list.head = NULL;
    list.tail = NULL;
}



/*----------------------------------------------------------------------
 * Replays all the moves from the beginning by emptying the grid then
 * iterating through the list that has the row and column number in the node
 * and adding that to the new empty board and printing it in a timely manner
------------------------------------------------------------------------ */
int replay()
{
	initializegrid();
	displayBoard();

	struct node* currentMove = list.head;

	while (currentMove != NULL)
	{
		sleep(2);
		board[currentMove->rows][currentMove->cols] = currentMove->player;
	    displayBoard();
	    currentMove = currentMove->next;
	}

	clearList();

	return 0;

}



/*--------------------------------------------------
 *1. checks the vacancy of column
 *2. adds the token on the board
---------------------------------------------------- */
int PlayGame(int n, char c)
{
	char a= c;

	if (n < 1 || n > COLS || isalpha((unsigned char)n) != 0)
	{
		printf("Invalid column number. Please pick a column between 1 and %d.\n", COLS);
		current = (current == 'R') ? 'Y' : 'R';
	    return -1; // Return an error code to indicate an invalid move
	}

    for (int i = ROWS - 1; i >= 0; i--)
    {
        if (board[i][n - 1] == ' ')
        {
            board[i][n - 1] = a;
            addlist(i, n-1, a);   //add this to the  linked list so we can replay it when needed
            return 0;
        }

    }


    printf("Column %d is already full. Please pick another column.\n", n);
    current = (current == 'R') ? 'Y' : 'R';   //switching here because in the main method it will swap
    										  //again so the player can continue with their second turn
    return -1;
}


void horizontal(char c, int token) //checking horizontal sequence
{
    int count = 0; // Initialize count to 0 to keep track of token sequence
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j <= COLS - token; j++)
        {
            count = 0; // Reset count for each potential sequence
            for (int k = 0; k < token; k++)
            {
                if (board[i][j + k] == c)
                {
                    count++;
                }
                else
                {
                    count = 0; // Reset count if the sequence is broken
                    break;
                }
            }
            if (count == token)
            {
                isWin = 1; // Set isWin to 1 if the desired sequence is found
                return;
            }
        }
    }
}


void vertical(char c, int token) //checking vertical sequence
{
    int count = 0; // Initialize count to 0 to keep track of token sequence
    for (int i = 0; i <= ROWS - token; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            count = 0; // Reset count for each potential sequence
            for (int k = 0; k <token; k++)
            {
                if (board[i + k][j] == c)
                {
                    count++;
                }
                else
                {
                    count = 0; // Reset count if the sequence is broken
                    break;
                }
            }
            if (count == token)
            {
                isWin = 1; // Set isWin to 1 if the desired sequence is found
                return;
            }
        }
    }
}



void diagonall(char c, int token)  //top left to bottom right sequence
{
	int count = 0; // Initialize count to 0 to keep track of token sequence
	for (int i = 0; i <= ROWS - token; i++)
	{
		for (int j = 0; j <= COLS-token; j++)
	    {
			count = 0; // Reset count for each potential sequence
	        for (int k = 0; k <token; k++)
	        {
	        	if (board[i + k][j + k] == c)
	            {
	        		count++;
	            }
	            else
	            {
	                count = 0; // Reset count if the sequence is broken
	                break;
	            }
	        }
	        if (count == token)
	        {
	        	isWin = 1; // Set isWin to 1 if the desired sequence is found
	            return;
	        }
	    }
	}
}




void diagonalr(char c, int token)  //bottom left to top right sequence
{
	int count = 0; // Initialize count to 0 to keep track of token sequence
	for (int i = ROWS-1; i >= token-1; i--)
	{
		for (int j = 0; j <= COLS-token; j++)
	    {
			count = 0; // Reset count for each potential sequence
	        for (int k = 0; k <token; k++)
	        {
	        	if (board[i - k][j + k] == c)
	            {
	        		count++;
	            }
	            else
	            {
	                count = 0; // Reset count if the sequence is broken
	                break;
	            }
	        }
	        if (count == token)
	        {
	        	isWin = 1; // Set isWin to 1 if the desired sequence is found
	            return;
	        }
	    }
	}
}



int main()
{

    char player1[50];
    char player2[50];
    int a=0;
    int token=0;
    char playag=a;   //play again command

    while(playag!='q')  //play again flagged to true for the game
    {
    	printf("How many tokens are needed to win: \n");
    	scanf("%d", &token);

    	getchar();

    	while(token != 3 && token != 4 && token != 5)
    	{
    		printf("Invalid token number. Please choose 3, 4, or 5.\n");
    		scanf("%d", &token);
    		getchar(); //consuming the newline input in buffer
    	}




    	printf("Enter the name of Player 1: \n");
    	fgets(player1,sizeof(player1), stdin);
    	player1[strlen(player1) - 1] = '\0';  // Remove the newline character

    	printf("Enter the name of Player 2: \n");
    	fgets(player2,sizeof(player2), stdin);
    	player2[strlen(player2) - 1] = '\0';  // Remove the newline character

    	printf("%s is assigned the color Red.\n", player1);
    	printf("%s is assigned the color Yellow.\n", player2);

    	initializegrid();
    	displayBoard();

    	while(1)
    	{
    		printf("%s to play, pick column (1-7): ", (current == 'R') ? "Red" : "Yellow");
    		scanf("%d", &a);
    		PlayGame(a, current);
    		getchar();
    		displayBoard();//consuming the newline input in buffer
    		horizontal(current, token);
    		vertical(current, token);
    		diagonall(current, token);
    		diagonalr(current, token);
    		isFull();

    		if (isWin)
    		{
    			printf("%s is the winner. \n", (current == 'R') ? "Red" : "Yellow");
    			break; // Exit the loop when there's a winner
    		}

    		else if (full)
    		{
    			printf("It's a draw.");  //if board is full it is a draw
    			break;
    		}


    		current = (current == 'R') ? 'Y' : 'R';  // Switch to the next player's turn

    	}

    	isWin=0;
    	printf("Press 'q' to quit or 'r' to replay or any other key to continue: " );  //will not take just whitespace to trigger the code
    	scanf(" %c", &playag);


    	if(playag=='r')
    	{
    		replay();
    		printf("Press 'q' to quit or any other key to continue: " );  //will not take just whitespace to trigger the code
    		scanf(" %c", &playag);
    	}


    }


    return 0;
}
