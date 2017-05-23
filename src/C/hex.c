#include "graph.h"
#include "board.h"
#include "menu.h"

int main(){
  Graph red = new_graph();
  Graph black = new_graph();
  int size = size_board();
  board b = new_board(size, -1);
  List history = new_list();


  int x, y, i = 1;
  player_choice(b);
  while (!(is_red_winner(red, size)) & !(is_black_winner(black, size))) {
    print_board(b);
    printf("\nCurrent player: %s\n", (get_player(b) == RED)?"RED":"BLACK" );
    get_xy(b, &x, &y);
    add_case(b, x, y);
    if (get_player(b) == RED)
      graph_add_vertice(red, to_int(x, y, b), size);
    else
      graph_add_vertice(black, to_int(x, y, b),size);
    /* Add new turn to the history*/
    history_add_turn(history, i++, to_int(x, y, b));
    next_player(b);
  }
  printf("%s\n", (is_red_winner(red, size))?"Red is winner!":"Black is winner!");
  graph_delete(red);
  graph_delete(black);
  board_delete(b);
}
