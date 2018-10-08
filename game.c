/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : Peng Gao
 * Student Number   : s3457558
 * Course Code      : COSC1076
 * Program Code     : BP162
 * Start up code provided by Paul Miller 
 **********************************************************************/
#include "game.h"

/**
 * The heart of the game itself. You should do ALL initialisation required 
 * for the game in here or call function required for that purpose. For example
 * both players should be initialised from here, you should seed the random 
 * number generator, that kind of thing. 
 *
 * Next, you should set the initial player - the initial player is the player 
 * whose token was set by initialisation to RED. 
 *
 * Next, you will need to manage the game loop in here. In each loop of the 
 * game, you should display the game board, including player scores 
 * display whose turn it is, etc in the format specified in the assignment
 * specification. Finally at the end of each turn you will calculate the score 
 * for each player you will calculate their score and store it and then you 
 * will need to swap the current player and other player 
 * using the swap_player() function. 
 * 
 * A game will end when either player presses enter or ctrl-d on a newline. 
 * 
 * When you detect a request to end the game, you should do a final calculation
 * of the scores for the two players and return the player with the highest
 * score.
 **/
struct player * play_game(game_board board, struct player * first,
		struct player * second)
{
	struct player * current, *other, *winner;

	init_first_player(first, &(first->token));		/* call the functions in player.c--player 1 and player 2 */
	init_second_player(second, first->token);

	if (first->token == RED)						/* If player 1 get the RED, so player 2 get the BLUE completely */
	{												/* by rand function */
		current = first;
		other = second;
	}
	else
	{
		current = second;
		other = first;
	}

	/* TO DO */
	do {
		display_board(board, current, other);


		if (make_move(current, board))				/* CALL the make_move function and display the game information*/
		{
			current->score = game_score(board, current->token);		/* get the score from current player */
			other->score = game_score(board, other->token);			/* and other player with pointer (->) */
			swap_players(&current, &other);			/* when the current player done the chess, call the */
			continue;								/* swap_players function to swap other player and keep play*/
		}
		else
		{
			current->score = game_score(board, current->token);		/* when the player want to quit game calculate the */
			other->score = game_score(board, other->token);			/* score and add the latest score into score-board */

			if (current->score >= other->score)		/* ensure who is the winner */
			{
				winner = current;
			}
			else
			{
				winner = other;
			}
			break;
		}
	} while (1 == 1);
	return winner;
}

/**
 * does the work of applying the move requested by the user to the game board.
 * It iterates over all the directions from the coordinate specified to see
 * whether there are any pieces that can be captured. If there are no pieces
 * that can be captured in any direction, it is an invalid move.
 **/
BOOLEAN apply_move(game_board board, unsigned x, unsigned y,
		enum cell player_token) {
	int dirArray[2];
	/* because this is board with coordinate
	 * so startX and startY will be substracted '1' */
	unsigned short sx = x - 1, sy = y - 1;
	unsigned short ex, ey;
	unsigned short t;
	int m;
	int i;
	BOOLEAN move = FALSE;

	for (i = 0; i < 8; i++)					/* 0 NORTH, 1 SOUTH, 2 EAST, 3 WEST, 4 NORTH_EAST */
	{										/* 5 NORTH_WEST, 6 SOUTH_EAST, 7 SOUTH_WEST */
		switch (i)
		{
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

		move = sampleMove(player_token, board, dirArray, x, y, &ex, &ey);

		if (move == FALSE)					/* if input is wrong, display error--continue */
		{
			continue;
		}
		else
		{
			switch (i)						/* 8 direction arithmetic */
			{
			case 0:/* NORTH */
				for (m = sy; m >= ey; m--)
				{
					board[m][sx] = player_token;
				}
				break;

			case 1:/* SOUTH */
				for (m = sy; m <= ey; m++)
				{
					board[m][sx] = player_token;
				}
				break;

			case 2:/* EAST */
				for (m = sx; m <= ex; m++)
				{
					board[sy][m] = player_token;
				}
				break;

			case 3:/* WEST */
				for (m = sx; m >= ex; m--)
				{
					board[sy][m] = player_token;
				}
				break;

			case 4:/* NORTH_EAST */
				t = 0;
				for (m = sx; m <= ex; m++)
				{
					board[sy - t][m] = player_token;
					t++;
				}
				break;

			case 5:/* NORTH_WEST */
				t = 0;
				for (m = sx; m >= ex; m--)
				{
					board[sy - t][m] = player_token;
					t++;
				}
				break;

			case 6:/* SOUTH_EAST */
				t = 0;
				for (m = sy; m <= ey; m++)
				{
					board[m][sx + t] = player_token;
					t++;
				}
				break;

			case 7:/* SOUTH_WEST */
				t = 0;
				for (m = sy; m <= ey; m++)
				{
					board[m][sx - t] = player_token;
					t++;
				}
				break;

			default:
				break;
			}
		}
	}
	return TRUE;
}

/**
 * The sample_move describe the Reversi Rules.
 * For example, when RED player will move them into direct
 * position,according to reversi rules, from current position
 * to direct position, in this region, the RED chess will
 * instead of BLUE color chess in the 8 * 8 game board
 **/
BOOLEAN sampleMove(enum cell token, game_board board, int direct[2], unsigned x,
		unsigned y, unsigned short *ex, unsigned short *ey) {
	BOOLEAN tmpChess = FALSE;
	BOOLEAN opponent = FALSE;
	int initX = direct[0];
	int initY = direct[1];
	unsigned arrayX = x - 1;
	unsigned arrayY = y - 1;
	unsigned dirX = arrayX;
	unsigned dirY = arrayY;
	enum cell dirToken;

	do {
		dirX = dirX + initX;				/* direct X,Y must be plused initial X,Y */
		dirY = dirY + initY;

		if (dirX < 0 || dirX > 7 || dirY < 0 || dirY > 7)	/* if chess played out of game board [8 * 8]---Error*/
		{
			tmpChess = FALSE;
			break;
		}
		else
		{
			dirToken = board[dirY][dirX];			/* the color of chess will be in the relative position */

			/* if move to other position with BLANK
			 * --Againest rules
			 * Error */
			if (dirToken == BLANK)
			{
				tmpChess = FALSE;
				break;
			}

			/* if move to other position with same color chess
			 * --Againest rules
			 * Error */
			if (dirToken == token)
			{
				if (opponent == FALSE)
				{
					tmpChess = FALSE;
					break;
				}
				else
				{
					/* if move to other position with different color chess
					 * correct*/
					tmpChess = TRUE;
					*ex = dirX;
					*ey = dirY;
					break;
				}
			}
			else
			{
				opponent = TRUE;
				continue;
			}
		}
	} while (TRUE);
	return tmpChess;
}

/**
 * simply count up how many locations contain the player_token
 * specified on the game_board.
 **/
unsigned game_score(game_board board, enum cell player_token)
{
	int i, j;
	unsigned score = 0;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (board[j][i] == player_token)
				score++;
		}
	}
	return score;
}

/**
 * swap the two player pointers passed in so that first points to the player
 * pointer that originally contained the second player and vice versa.
 **/
void swap_players(struct player ** first, struct player ** second)
{
	struct player * swap;
	swap = *second;
	*second = *first;
	*first = swap;
}
