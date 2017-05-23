/*
 * menu.h
 *
 *  Created on: 07.05.2017
 *      Author: dehuit
 */

#define MENU_H_

#include "board.h"
#include "graph.h"

/*
Role: chosing player dialog
In: board
Out: board with new player
*/
void player_choice(board b);

/*
Role: get size for board
In: -
Out: int for board size
*/
int size_board();

/*
Role: get position x and y
In: pointer to x & y, board
Out: x, y
*/
void get_xy(board b, int *x, int * y);

/************************/
/* HISTORY MANIPULATION */
/************************/

/*
Role: add new turn to the history
In: list of turn, turn id, turn informations
Out: -
*/
void history_add_turn(List h, int num_turn, int turn);

/*
Role:  board step back on board
In: history, board
Out: -
*/
int history_step_back(List h, board b);

/*
Role: remove all turn from history
In: history
Out: -
*/
void history_clear(List h);

/*
Role: remove history
In: history
Out: -
*/
void history_delete(List h);
