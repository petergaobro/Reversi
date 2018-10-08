/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : Peng Gao
 * Student Number   : s3457558
 * Course Code      : COSC1076
 * Program Code     : BP162
 * Start up code provided by Paul Miller 
 **********************************************************************/
#include "player.h"
#include "game.h"
/**
 * These two functions initialise the player structure at the beginning of the 
 * game. In both cases, you should initialise the whole structure to known safe
 * values and then prompt the user for their name. In the init_first_player() 
 * function you should then select a color at random for this player using the 
 * rand() function. This token should be assigned to the first player's token and
 * also returned via the token pointer. In init_second_player() you should just
 * test the value of token and assign the opposite color to the second player.
 **/
BOOLEAN init_first_player(struct player* first, enum cell * token)
{
	int inputLength;
	int colorFlag;
	first->score = 0;
	setbuf(stdout, NULL);

	/* Player input the name */
	/* TO DO */
	do {
		printf("Please enter the first player's name: ");
		fgets(first->name, NAMELEN + 1, stdin);
		inputLength = strlen(first->name);
		if (first->name[0] == '\n')
		{
			continue;
		}
		break;

	} while (TRUE);

	if (first->name[inputLength - 1] != '\n')	/* delete \n from user input */
	{
		read_rest_of_line();
	}
	else
	{
		first->name[inputLength - 1] = '\0';
	}
	colorFlag = ((rand() * 10) % 2) + 1;	/* Use the rand() function to change the color of chess for */
	first->token = colorFlag;				/* player 1 or player 2 with 50% percentage */
	return TRUE;
}

BOOLEAN init_second_player(struct player * second, enum cell token)
{
	int inputLength;
	second->score = 0;
	setbuf(stdout, NULL);

	/* Player enter the name */
	/* TO DO */
	do {
		printf("Please enter the second player's name: ");
		fgets(second->name, NAMELEN + 1, stdin);
		inputLength = strlen(second->name);
		if (second->name[0] == '\n')
		{
			continue;
		}
		break;

	} while (TRUE);

	if (second->name[inputLength - 1] == '\n')	/* delete \n from user input because fgets*/
	{
		second->name[inputLength - 1] = '\0';
	}
	else
	{
		read_rest_of_line();
	}

	if (token == RED)				/* according to player 1 opinion, if player 1 get RED */
	{								/* so player 2 get BLUE, rather than opposition */
		second->token = BLUE;
	}
	else
	{
		second->token = RED;
	}
	return TRUE;

}

/**
 * prompts the user for a comma-separate pair of coordinates for a move in the
 * game. Each move, if valid, must capture at least one enemy piece by 
 * surrounding a sequence of one or more enemy pieces with two pieces of our 
 * own: one being the new piece to be placed and the other a piece already 
 * on the board. This function then validates that a valid move has been entered
 * calls the apply_move function to do the actual work of capturing pieces.
 **/
BOOLEAN make_move(struct player * human, game_board board)
{
	/* define the variable */
	char *inputX, *inputY;
	char *endofString;
	char counter[20];
	unsigned x, y;
	int i;
	int dirArray[2];/* two direction array---x,y */
	unsigned short ex, ey;    /* end X and end Y */
	BOOLEAN move = FALSE;

	setbuf(stdout, NULL);
	printf("\nIt is %s's turn.\n", human->name);		/* display the turn---player 1 or player 2 */

	while (1) {
		printf("Please enter x and y coodinates separated by a comma for the piece you wish to place: ");

		/* if enter nothing, 'Ctrl + D' or 'Enter' can quit the game and go back menu */
		if (fgets(counter, 20, stdin) != NULL)
		{
			if (counter[0] == '\n')
			{
				return FALSE;
			}
			if (counter[strlen(counter) - 1] == '\n')	/* delete \n from user input*/
			{
				counter[strlen(counter) - 1] = '\0';
			}



			if (strlen(counter) >= 4)					/* if input > 4 length of array */
			{											/* display the error*/
				printf(
						"\nError: buffer overflow. Please try again, entering less data.\n");
				continue;
			}

			/* get the token */
			inputX = strtok(counter, ",");				/* if input is not devided by comma */
			if (inputX != NULL)							/* or if input is not correct format, like (x,y) */
			{											/* display the error */
				x = strtol(inputX, &endofString, 10);
			}
			else
			{
				printf("\nError: invalid coordinates.");
				printf("Error: you did not enter valid coordinates. Please try again.\n");
				continue;
			}

			inputY = strtok(NULL, ",");
			if (inputY != NULL)
			{
				y = strtol(inputY, &endofString, 10);
			}
			else
			{
				printf("\nError: invalid coordinates.");
				printf("Error: you did not enter valid coordinates. Please try again.\n");
				continue;
			}

			/* there are 8 directions
			 * use switch to choose
			 * 0 NORTH, 1 SOUTH, 2 EAST, 3 WEST, 4 NORTH-EAST
			 * 5 NORTH-WEST, 6 SOUTH-EAST, 7 SOUTH-WEST
			 * Main Feature: when the current player finished the chess
			 * and it's time to other turn by apply_move (game.c)
			 * upload the game, including the position of chess and main
			 * game board. */
			for (i = 0; i < 8; i++)
			{
				switch (i) {
				case 0:
					dirArray[0] = 0;
					dirArray[1] = -1;
					break;
				case 1:
					dirArray[0] = 0;
					dirArray[1] = 1;
					break;
				case 2:
					dirArray[0] = 1;
					dirArray[1] = 0;
					break;
				case 3:
					dirArray[0] = -1;
					dirArray[1] = 0;
					break;
				case 4:
					dirArray[0] = 1;
					dirArray[1] = -1;
					break;
				case 5:
					dirArray[0] = -1;
					dirArray[1] = -1;
					break;
				case 6:
					dirArray[0] = 1;
					dirArray[1] = 1;
					break;
				case 7:
					dirArray[0] = -1;
					dirArray[1] = 1;
					break;
				default:
					break;
				}

				/* CALL the sampleMove function to check which position is vaild */
				move = sampleMove(human->token, board, dirArray, x, y, &ex, &ey);

				if (move == FALSE)
				{
					continue;
				}
				else
				{
					move = TRUE;
					break;
				}
			}

			/* if input is incorrect, display the error */
			if (move == FALSE)
			{
				printf("\nError: the move you attempted was not valid.\n");
				continue;
			}
			/* rather than continue to play and swap player
			 * with color chess. */
			else
			{
				apply_move(board, x, y, human->token);
				break;
			}
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}

/* create the new function
 * display all the detail
 * It will be called by display_board function
 * in my opinion, players' detail is belong to
 * initial board, so making new functoin and check clearly
 **/
void allDetail(struct player *detail)
{
	printf("--------------------\n");
	printf("Name: %-11s", detail->name);
	printf("Score: %-8d", detail->score);
	printf("Token Color: ");

	if (detail->token == BLUE)
	{
		printf(COLOR_BLUE);
		printf("0");
		printf(COLOR_RESET);
	}
	else
	{
		printf(COLOR_RED);
		printf("0");
		printf(COLOR_RESET);
	}
	printf("\n");
}
