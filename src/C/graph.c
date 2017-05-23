//
// Created by dehuit on 13/04/17.
//

#include "graph.h"

int DEBUG = 0;

/*
Graph is a list of vertices.
Vertice contains key value (case number) and list of vertice's neighbor referenced to other vertices.
So, every vertice of graph is referenced to list of his neighbor and every element of this list is referenced to vertice.
*/
typedef struct s_node {
  void * v; //Link to something
  int key;   //Key value
  struct s_node * next;  //Link to next element
  struct s_node * prev; //Link to previous element
} * Node;

struct s_list {
  Node zero; //Sentinel
  int size;  //Total elements
};

struct s_graph {
  List vert;
  int nb_vertice;
};

/*
Role: Crate new node with data passing in parametre
IN  : pointer on data, key value
OUT : node
*/
Node new_node(void * data,int key) {
  Node n = malloc(sizeof(struct s_node));
  n->v = data;
  n->key = key;
  return n;
}

/*
Role: Return new list.
IN  : nothing
OUT : empty list
*/
List new_list() {
  List l = malloc(sizeof(struct s_list));
  l->zero = malloc(sizeof(struct s_node));
  l->zero->next = l->zero;
  l->zero->prev = l->zero;
  l->zero->key = INT_MAX;
  l->size = 0;
  return l;
}

/*
Role: Return list size
IN  : List
OUT : list size
*/
int list_size(List l){
  return l->size;
}

/*
Role: Add new element to the list.
IN  : List, data, key value
OUT : List appended with value
 */
void * list_add(List l, void * data, int key) {
  Node n = new_node(data, key);
  Node cur = l->zero->next;
  while (cur->key < key)
    cur = cur->next;

  if (DEBUG && cur->key == key) {
    fprintf(stderr, "Error! Keys are equal! \n");
    return NULL;
  }
  if (DEBUG)
    printf("Key comparation: %d < %d < %d \n", cur->prev->key, key, cur->key);
  n->next = cur;
  n->prev = cur->prev;
  cur->prev->next = n;
  cur->prev = n;

  l->size++;
  return n;
}

/*
Role: Remove node from list
IN  : Liste, Node
OUT : -
 */
int list_remove_node(List l, Node n) {
  n->prev->next = n->next;
  n->next->prev = n->prev;
  l->size--;
  free(n);
  return 0;
}

/*
Role: Search element by it's key
IN  : List, key value
OUT : pointer to Node
 */
void * list_search_by_key(List l, int key) {
  if (l->size == 0 || l->zero->prev->key < key)
    return NULL;
  Node cur = l->zero->next;
  while (cur->key != key && cur != l->zero)
    cur = cur->next;

  return (cur->key == key)? cur : NULL;
}

/*
Role: return last element in the list
IN  : List
OUT : pointer to Node
 */
void * list_last_element(List l) {
  return (l->size == 0)? NULL: l->zero->prev->v;
}

/*
Role: Remove element by key value from list
IN  : List, key value
OUT : updated list
 */
int list_remove_elem(List l, int key) {
  Node n = list_search_by_key(l, key);
  if (!n) //Case when key is does not exist
    return -1;
  list_remove_node(l, n);
  return 0;
}

/*
Role: Delete list
IN  : List
OUT : void
 */
int list_delete(List l) {
  Node cur = l->zero->next;
  while (cur != l->zero){
    list_remove_node(l, cur);
    cur = l->zero->next;
  }
  free(l->zero);
  free(l);
  return 0;
}


int list_print(List l) {
  Node cur = l->zero->next;
  int * a;
  while (cur != l->zero){
    a = cur->v;
    printf("%d ", *a);
    cur = cur->next;
  }
  printf("\n");
  return 0;
}
/************************** GRAPH ***********************************/
List get_neighbor(Node n) {
  return (List) n->v;
}

Node first(List l) {
  return l->zero->next;
}

/*
Role: Return new graph.
IN  : nothing
OUT : empty graph
*/
Graph new_graph() {
  Graph g = malloc(sizeof(struct s_graph));
  g->nb_vertice = 0;
  g->vert = new_list();
  return g;
}

/*
Role: Add new edge for l
IN  : List, data, key value
OUT : List appended with value
 */
int graph_add_edge(Node a, Node b) {
  List la = a->v, lb = b->v;
  list_add(la, b, b->key);
  list_add(lb, a, a->key);
  return 0;
}

/*
Role: Determinate if who is neighbor to to_who
IN  : Potential neighbor, case, board size
OUT : Yes or not
 */
bool is_neighbor(int pn, int n, int size) {
  return (n != pn && (
  /* Checking if who is on of 2 upper-one of to_who */
  (pn == n - size) || (pn == n - size + 1 && pn % size != 0) ||
  /* Checking if who next left or right to to_who */
  (pn == n - 1 && n % size != 0) ||
  (pn == n + 1 && pn % size != 0) ||
  /*Checking 2 in the bottom*/
  (pn ==  n + size - 1 && n % size != 0) || (pn == n + size)));
}

/*
Role: Add new vertice.
IN  : Graph, new vertice number and board_size
OUT : Appended graph
 */
int graph_add_vertice(Graph g, int num, int board_size) {
  List l = new_list(); //List of neighbor of our new vertice

  /*First of all: link vertice to graph */
  Node our_vertice = list_add(g->vert, l, num);

  /* Now we have to find all possible neighbors */
  Node cur = g->vert->zero->next;
  while (cur != g->vert->zero) {
    if (is_neighbor(cur->key, num, board_size)) {
        /* cur is neighbor, l is list of new vertice's neighborhood */
        graph_add_edge(cur, our_vertice);
    }
    cur = cur->next;
  }

  g->nb_vertice++;
  return 0;
}

/*
Role: Remove vertice from graph.
IN  : Graph, vertice number
OUT : Updated graph
 */
int graph_remove_vertice(Graph g, int num) {
  Node temp, current, to_remove = list_search_by_key(g->vert, num);
  if (!to_remove)
    return -1;
  /* Step 1: Eliminate all related edges from other vertices */
  List l =  to_remove->v;
  while (l->size != 0) {
    current = l->zero->next;
    temp = current->v;
    list_remove_elem(temp->v, num);
    list_remove_elem(l, temp->key);
  }
  list_delete(l);
  list_remove_node(g->vert, to_remove);
  g->nb_vertice--;
  return 0;
}

/*
Role: Delete graph from memory
IN  : graph
OUT : -
*/
void graph_delete(Graph g) {
  Node cur = first(g->vert);
  while (cur != g->vert->zero){
    list_delete((List) cur->v);
    cur = cur->next;
  }
  list_delete(g->vert);
  free(g);
}

/*
Role: Print graph
IN  : graph
OUT : -
*/
void graph_print(Graph g) {
  Node p,cur,v = g->vert->zero->next;
  List l;
  while (v != g->vert->zero) {
    printf("%d -> ", v->key);
    l = v->v;
    cur = l->zero->next;
    while (cur != l->zero) {
      p = cur->v;
      printf("%d ", p->key);
      cur = cur->next;
    }
    printf("\n");
    v = v->next;
  }
}

/*********************************/
/****** GRAPH TRAVERSIAL   *******/
/*********************************/
/*
 1) Red is winner when we can trace a root from case whose index
has to be a multiple of board size (left corner: index % size == 0)
to the case whose index has to give us size-1 by Euclidean division (right corner: index % size == size-1)
2) Black is winner when we can trace a root from case whose index has to be lighter than board size (top: index / size == 0)
to the case whose index has to give us size-1 by division (bottom: index / size == size-1)

General algorithm:
 For every not-visited neighbor
    -if the other edge is achived -> return true
    -if not -> mark current node as visited, go through its neighbors
      *if the end is reached - unvisit current neighbor, go to the next one
    -if can't find the way -> return false
*/

bool trace_red_root(Graph g, Node n, List visited, int size) {
  List neighb = get_neighbor(n);
  Node curN = first(neighb);

  while (curN != neighb->zero) {
    if (list_search_by_key(visited, curN->key) == NULL){
      //If case is not visited yet, we check it & it's neighbors
      if (curN->key % size == size -1) return true;
      list_add(visited, NULL, curN->key); //mark as visited
      if(trace_red_root(g, curN->v, visited, size)) return true;
      list_remove_elem(visited, curN->key); //unmark as visited
    }
    curN = curN->next;
  }
  return false;
}

bool is_red_winner(Graph g, int size) {
  List visited = new_list();
  Node n = g->vert->zero->next;

  while (n != g->vert->zero) {
    if (n->key % size == 0) {
      if (trace_red_root(g, n, visited, size)){
        list_delete(visited);
        return true;
      }
    }
    n = n->next;
  }
  list_delete(visited);
  return false;
}



bool trace_black_root(Graph g, Node n, List visited, int size) {
  List neighb = (List) n->v;
  Node curN = first(neighb);

  while (curN != neighb->zero) {
    if (list_search_by_key(visited, curN->key) == NULL){
      //If case is not visited yet, we check it & it's neighbors
      list_add(visited, NULL, curN->key); //mark as visited
      if (curN->key / size == size -1) return true;
      if(trace_black_root(g, curN->v, visited, size)) return true;
      list_remove_elem(visited, curN->key);
    }
    curN = curN->next;
  }
  return false;
}

bool is_black_winner(Graph g, int size) {
  List visited = new_list();
  Node n = g->vert->zero->next;

  while (n != g->vert->zero) {
    if (n->key / size == 0) {
      if (trace_black_root(g, n, visited, size)){
        list_delete(visited);
        return true;
      }
    }
    n = n->next;
  }
  list_delete(visited);
  return false;
}
