#include "board.h"
#include "graph.h"

int main() {

  //Insert (2, 2) (2,3) (3, 1) (0, 3)


  printf("*** Creation of board of size 4 ***\n");
	board b = new_board(4, 0);
	print_board(b);
	printf("\n");
  printf("*** Insertion testing ***\n");
	add_case(b, 2, 2);
	next_player(b);
  add_case(b, 2, 3);
	next_player(b);
  add_case(b, 3, 1);
	next_player(b);
  add_case(b, 0, 3);
	print_board(b);

	printf("*** SAVE TEST ***\n");
  board_to_file(&b, "fic");
  board b2;
	printf("*** LOAD TEST ***\n");
  board_from_file(&b2, "fic");
  print_board(b2);
	printf("*** EXPORTING TO GRAPH TEST ***\n");
  Graph g1 = new_graph(), g2 = new_graph();
  board_to_graph_by_player(b2, g1, RED);
  printf("For RED\n");
  graph_print(g1);
  board_to_graph_by_player(b2, g2, BLACK);
  printf("For BLACK\n");
  graph_print(g2);
  graph_delete(g1);
  graph_delete(g2);
	board_delete(b);
	board_delete(b2);
}
