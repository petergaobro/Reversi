/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : Peng Gao
 * Student Number   : s3457558
 * Course Code      : COSC1076
 * Program Code     : BP162
 * Start up code provided by Paul Miller 
 **********************************************************************/

#include "scoreboard.h"

/**
 * initalise the scoreboard so that the scores for each element of the array
 * is set to 0.
 **/
void init_scoreboard(score scores[MAX_SCORES]) {
	int s;
	for (s = 0; s < MAX_SCORES; s++)
	{
		strcpy(scores[s].name, "");		/* upload the score, when the player finish current chess. */
		scores[s].token = BLANK;		/* score will be pointed to player name by score */
		scores[s].score = 0;
	}
}

/**
 * insert the top scorer from the last game played in sorted order according
 * to their score 
 * insert rank list
 * ----------------------------
 * Name                 | Score
 * ----------------------------
 * peter				   | 7
 * jacky				   | 5
 * Res				   	   | 4
 **/
BOOLEAN add_to_scoreboard(score scores[MAX_SCORES], struct player * winner)
{
	int m;
	int n;

	for (m = 0; m < MAX_SCORES; m++)
	{
		if (winner->score > scores[m].score)
		{
			for(n = MAX_SCORES - 2; n >= m; n--)
			{
				scores[n+1] = scores[n];
			}
			scores[m]= *winner;
			break;
		}
	}
	return TRUE;
}

/**
 * display the scores in the scoreboard according to their order. Your output
 * should match that provided in the assignment specification.
 *----------------------------
 *Name                 | Score
 *----------------------------
 *peter				   | 7
 **/
void display_scores(score scores[MAX_SCORES])
{
	int m;
	printf("Reversi - Top Scores\n");
	printf("====================\n");
	printf("----------------------------\n");
	printf("Name                 | Score\n");
	printf("----------------------------\n");

	for (m = 0; m < MAX_SCORES; m++)
	{
		if (scores[m].score>0)
		{
			 printf("%-21s", scores[m].name);
			 printf("|%4d\n", scores[m].score);
		}
	}
}
