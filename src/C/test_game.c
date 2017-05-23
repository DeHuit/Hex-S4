#include "graph.h"
#include "board.h"

int main(){
  Graph red = new_graph();
  Graph black = new_graph();
  board b = new_board(4, -1);
  int x, y;
  while (!(is_red_winner(red, 4)) & !(is_black_winner(black, 4))) {
    print_board(b);
    do {
      printf("x = "); scanf("%d", &x );
      printf("y = "); scanf("%d", &y );
    } while (!is_valid_turn(b, to_int(x, y, b)));
    add_case(b, x, y);
    if (get_player(b) == RED)
      graph_add_vertice(red, to_int(x, y, b), 4);
    else
      graph_add_vertice(black, to_int(x, y, b),4);
    next_player(b);
  }
  printf("%s\n", (is_red_winner(red, 4))?"Red is winner!":"Black is winner!");
  graph_delete(red);
  graph_delete(black);
  board_delete(b);
}
