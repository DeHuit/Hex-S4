#include "graph.h"

int main() {
  Graph g = new_graph();
  graph_add_vertice(g, 0, 4);
  graph_add_vertice(g, 1, 4);
  graph_add_vertice(g, 2, 4);
  graph_add_vertice(g, 3, 4);
  graph_print(g);
  printf("****************************\n");
  printf("Removed values: 5, 1\n");
  graph_remove_vertice(g,5);
  graph_remove_vertice(g,1);
  graph_print(g);
  graph_delete(g);
  return 0;
}
