#include "graph.h"
#include "board.h"
#include "I_A.h"
#include "menu.h"

int main(){
  Graph red = new_graph();
  Graph black = new_graph();
  int size = size_board();
  board b = new_board(size, BLACK);
  List history = new_list();
  MinMax I_A = new_minmax(b,size*size,red,black,size) ;

  int x, y, i = 1 , depth = (size*size)-1;
  player_choice(b);
  while (!(is_red_winner(red, size)) & !(is_black_winner(black, size))) {
    print_board(b);
    printf("\nCurrent player: %s\n", (get_player(b) == RED)?"RED":"BLACK" );
    if (get_player(b) == RED) {
      get_xy(b, &x, &y);
      add_case(b, x, y);
      graph_add_vertice(red, to_int(x, y, b), size);
    }else{
      int indice = IA_Jouer(I_A,depth-1) ;
      x = indice / size ;
      y = indice % size ;
      add_case(b,x,y) ;
      graph_add_vertice(black, to_int(x, y, b),size);
    }
    /* Add new turn to the history*/
    history_add_turn(history, i++, to_int(x, y, b));
    next_player(b);
  }

  print_board(b);
  printf("%s\n", (is_red_winner(red, size))?"Red is winner!":"Black is winner!");
  graph_delete(red);
  graph_delete(black);
  minmax_delete(I_A);
  history_delete(history);
  board_delete(b);
}
