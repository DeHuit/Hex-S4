//
//  Created by dehuit on 15/05/2017
//
#ifndef IA_H
#define IA_H

#include "board.h"
#include "graph.h"

typedef struct s_minmax *MinMax ;

/*
Role : Return new minmax
In : board , depth , Graph , Graph
Out : new minmax
*/
MinMax new_minmax(board b , int profondeur , Graph j_h , Graph j_IA , int size) ;

/*
Role : Delete MinMax from memory
IN : MinMax
OUT : -
*/
void minmax_delete(MinMax m) ;

/*
Role : Return the most adventageaous position for the ia
In : MinMax
OUT : The index of the box where the ia must play
*/
int IA_Jouer(MinMax m , int profondeur) ;

/*
Role : Determine the most unfavorable blow to the ia
In : MinMax
OUT : the most unfavorable blow to the ia
*/
int min(MinMax m) ;

/*
Role : Determine the most advantageous blow for the ia
IN : MinMax
OUT : the most advantageous blow for the ia
*/
int max(MinMax m) ;

/*
Role : Return the number of winning chains of each player if there is no winner
IN : MinMax
OUT : the number of winning chains of each player
*/
int eval(MinMax m) ;

/*
Role : Calculate the number of winning chains of each player
IN : MinMax
OUT : the number of winning chains of each player
*/
int nb_series(MinMax m) ;

#endif
