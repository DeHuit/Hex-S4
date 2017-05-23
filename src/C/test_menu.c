#include "menu.h"
#include "graph.h"

int main() {

  //Insert (2, 2) (2,3) (3, 1) (0, 3)
	board b = new_board(4, -1); List h = new_list();
	add_case(b, 2, 2);
  history_add_turn(h, 1, to_int(2, 2, b));
	next_player(b);
  add_case(b, 2, 3);
  history_add_turn(h, 2, to_int(2, 3, b));
	next_player(b);
  add_case(b, 3, 1);
  history_add_turn(h, 3, to_int(3, 1, b));
	next_player(b);
  add_case(b, 0, 3);
  history_add_turn(h, 4, to_int(0, 3, b));
	print_board_legacy(b);
  printf("\nPerforming 2 step back\n\n");
  history_step_back(h, b);
	history_step_back(h, b);
  print_board_legacy(b);

  history_delete(h);
	board_delete(b);
}
