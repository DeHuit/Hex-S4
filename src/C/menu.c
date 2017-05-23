

#include "menu.h"


/*
Role: chosing player dialog
In: board
Out: board with new player
*/
void player_choice(board b){
    int player;
    printf("Quel joueur commence la partie ? [Red 1/Black 0]");
    scanf("%d", &player);
    printf("\n");
    set_player(b,player);
}

/*
Role: get size for board
In: -
Out: int for board size
*/
int size_board(){
  int size_board;
  do {
    printf("Size board : ");
    scanf("%d", &size_board);
    if (size_board < 2)
      printf("Too small!\n");
  } while (size_board < 2);
  return size_board;
}

/*
Role: get position x and y
In: pointer to x & y, board
Out: x, y
*/
void get_xy(board b, int *x, int * y) {
  do {
    printf("x = "); scanf("%d", x );
    printf("y = "); scanf("%d", y );
  } while (!is_valid_turn(b, to_int(*x, *y, b)));
}

/************************/
/* HISTORY MANIPULATION */
/************************/

/*
Role: add new turn to the history
In: list of turn, turn id, turn informations
Out: -
*/
void history_add_turn(List h, int num_turn, int turn) {
  int * x = malloc(sizeof(int));
  *x = turn;
  list_add(h, x, num_turn);
}

/*
Role: return board step by one step back
In: history, board
Out: -
*/
int history_step_back(List h, board b){
  if (list_size(h) != 0) {
    int * pos = (int*) list_last_element(h);
    set_case(b, *pos, VIDE);
    int a = *pos;
    free(pos);
    list_remove_elem(h, list_size(h));
    next_player(b);
    return a;
  }
  else
    return -1;
}

/*
Role: remove all turn from history
In: history
Out: -
*/
void history_clear(List h) {
  if (list_size(h) != 0) {
    int * pos;
    while(list_size(h) > 0) {
      pos = list_last_element(h);
      free(pos);
      list_remove_elem(h, list_size(h));
    }
  }
}

/*
Role: remove history
In: history
Out: -
*/
void history_delete(List h) {
  history_clear(h);
  list_delete(h);
}
