/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : Peng Gao
 * Student Number   : s3457558
 * Course Code      : COSC1076
 * Program Code     : BP162
 * Start up code provided by Paul Miller 
 **********************************************************************/
#include <time.h>
#include "shared.h"
#include "player.h"
#include "gameboard.h"

#ifndef GAME_H
#define GAME_H

struct player * play_game(game_board board, struct player * human,
		struct player * computer);
BOOLEAN apply_move(game_board board, unsigned x, unsigned y,
		enum cell player_token);
BOOLEAN sampleMove(enum cell token, game_board board, int direct[2], unsigned x,
		unsigned y, unsigned short *ex, unsigned short *ey);
unsigned game_score(game_board board, enum cell player_token);
void swap_players(struct player ** first, struct player ** second);

#endif /* ifndef GAME_H */
