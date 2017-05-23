/*
 * board.h
 *
 *  Created on: 17.04.2017
 *      Author: dehuit
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define RED 1
#define BLACK 0
#define VIDE -1
#define MAXNOM 100

/* Board type */
typedef struct s_board * board;


/*****************************/
/********* ACCESSORS **********/
/******************************/
/*
Role: Swith current player on the board
In: board to change
Out: -
*/
void next_player(board b);

/*
Role: Getter for board's player
In: board
Out: current player
*/
int get_player(board b);

/*
Role: Getter for board's cases
In: board
Out: pointer to board's state array
*/
int * get_board(board b);

/*
Role: Getter for board's size
In: board
Out: size
*/
int board_get_size(board b);

/*
Role: Getter for bot color
In: board
Out: cbot color
*/
int get_bot_color(board b);

/*
Role: Setter for player board
In: board
Out: current player
*/
void set_player(board b, int player);


/****************************************/
/*********** BOARD MATH *****************/
/*****************************************/

/*
Role: Convert coordinates to unique case id
In: x, y, board
Out: unique case id
*/
int to_int(int x, int y, board b);

/*
Role: Check if turn is possible
In: board, case id
Out: true or false
*/
bool is_valid_turn(board b, int cell);


/****************************************/
/********** BOARD MANIPULATORS ***********/
/*****************************************/

/*
Role: Create new board of size "size"
In: size of board
Out: empty board
*/
board new_board(int size, int mod);

/*
Role: Do the turn: mark case of board on x, y as controled by current player
In: x, y, board
Out: -
*/
void add_case(board b, int x, int y);

/*
Role: set case x,y in player value
In: position, board, player
Out: -
*/
void set_case(board b, int pos, int player);

/*
Role: return case x, y value
In: position, board
Out: case value
*/
int get_case(board b, int pos);

/*
Role: Show board on stdin
In: board
Out: -
*/
void print_board(board b);

/*
Role: Show board on stdin in the "old" style
In: board
Out: -
*/
void print_board_legacy(board b);

/*
Role: Delete board
In: board
Out: -
*/
void board_delete(board b);

/*
Role: Save current board to the file *.brd
In: board
Out: file or error code
*/
int board_to_file(board * b, char name[]);

/*
Role: Load board from the file in the pointer to board
In: pointer to board
Out: board or error code
*/
int board_from_file(board * b, char name[]);

/*
Role: Return pointer on board from the file (for Java)
In: file name
Out: board or NULL in case of error
*/
board board_from_file_JAVA(char name[]);

/*
Role: Transform current board into a graph of cases owned by player (useful after file load)
In: board to transform, graph, current player
Out: graph with cases owned by player
*/
int board_to_graph_by_player(board b, Graph g, int player);

int nombre_de_pion(board b) ;

void remove_case(board b , int x , int y) ;

bool possible_blow(board b , int cell) ;


#endif /* BOARD_H_ */
