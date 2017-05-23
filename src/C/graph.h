//
// Created by dehuit on 13/04/17.
//

#ifndef CODE_GRAPH_H
#define CODE_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/*
Double linked list on Sentinel
*/
typedef struct s_list  * List;

/*
Graph is a list of vertices.
Vertice contains key value (case number) and list of vertice's neighbor referenced to others vertices.
So, every vertice of graph is referenced to list of his neighbor and every element of this list is referenced to vertice.
*/
typedef struct s_graph * Graph;

int list_print(List l);

/*
Role: Return new graph.
IN  : nothing
OUT : empty graph
*/
Graph new_graph();

/*
Role: Add new vertice.
IN  : Graph, new vertice number and board_size
OUT : Appended graph
 */
int graph_add_vertice(Graph g, int num, int board_size);

/*
Role: Remove vertice from graph.
IN  : Graph, vertice number
OUT : Updated graph
 */
int graph_remove_vertice(Graph g, int num);

/*
Role: Delete graph from memory
IN  : graph
OUT : -
*/
void graph_delete(Graph g);

/*
Role: Print graph
IN  : graph
OUT : -
*/
void graph_print(Graph g);



/******************************/
/******** LINKED LIST *********/
/******************************/
/******* CONSTRUCTORS *********/
/*
Role: Return new list.
IN  : nothing
OUT : empty list
*/
List new_list();

/*
Role: Return list size
IN  : List
OUT : list size
*/
int list_size(List l);

/*
Role: Add new element to the list.
IN  : List, data, key value
OUT : List appended with value
 */
void * list_add(List l, void * data, int key);

/*
Role: Search element by it's key
IN  : List, key value
OUT : pointer to Node
 */
void * list_search_by_key(List l, int key);

/*
Role: return last element in the list
IN  : List
OUT : pointer to Node
 */
 void * list_last_element(List l);

/*
Role: Remove element by key value from list
IN  : List, key value
OUT : updated list
 */
int list_remove_elem(List l, int key);

/*
Role: Delete list
IN  : List
OUT : void
 */
int list_delete(List l);

bool is_red_winner(Graph g, int size);
bool is_black_winner(Graph g, int size);
#endif //CODE_GRAPH_H
