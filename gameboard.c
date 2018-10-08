/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : Peng Gao
 * Student Number   : s3457558
 * Course Code      : COSC1076
 * Program Code     : BP162
 * Start up code provided by Paul Miller 
 **********************************************************************/
#include "gameboard.h"
#include "player.h"

/**
 * initialise the game board to be consistent with the screenshot provided
 * in your assignment specification. 
 *
 * All squares should be initialised to be blank other than the four
 * squares in the middle of the board. In that case they are initialised to 
 * appropriate colored tokens
 **/
void init_game_board(game_board board)
{
	int i, j;

	for (i = 0; i < BOARD_WIDTH; i++)
	{
		for (j = 0; j < BOARD_HEIGHT; j++)
		{
			board[i][j] = BLANK;
		}
	}
	board[3][3] = RED;
	board[4][4] = RED;
	board[3][4] = BLUE;
	board[4][3] = BLUE;
}

/**
 * display the board as specified in the assignment specification. You should 
 * make every effort to create a board consistent with the screenshots in the 
 * assignment specification. 
 **/
void display_board(game_board board, struct player * first,
		struct player * second)
{

	int x = 0;
	int y = 0;
	setbuf(stdout,NULL);

	/* display two player details */
	printf("================================================================================\n");
	printf("Player One's Details\n");
	allDetail(first);
	printf("--------------------------------------------------------------------------------\n");
	printf("Player Two's Details\n");
	allDetail(second);
	printf("--------------------------------------------------------------------------------\n");

	for (x = 0; x <= BOARD_WIDTH; x++)		/* Design the game board */
	{
		if (x == 0)
		{
			printf("    ");
		}
		else
		{
			printf(" %-3d", x);
		}
	}
	printf("\n====================================\n");

	for (x = 0; x < BOARD_WIDTH; x++)		/* every row are devided by '|' */
	{
		printf(" %d |", x + 1);
		for (y = 0; y < BOARD_HEIGHT; y++)	/* every '| |', will be contained 1 char, like '0' */
		{
			if (board[x][y] == RED)
			{
				printf(COLOR_RED);
				printf(" %c ", '0');
				printf(COLOR_RESET);
				printf("%c", '|');
			}
			else if (board[x][y] == BLUE)
			{
				printf(COLOR_BLUE);
				printf(" %c ", '0');
				printf(COLOR_RESET);
				printf("%c", '|');

			}
			else
			{
				printf(" %c |", ' ');
			}
		}
		printf("\n");
		printf("------------------------------------\n");
	}
	printf("====================================");
}
