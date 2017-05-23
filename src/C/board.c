/*
 * board.c
 *
 *  Created on: 17.04.2017
 *      Author: dehuit
 */


#include "board.h"
#define ERR_O -1
#define ERR_WR -2
#define ERR_RD -3
#define ABORT -4
#define SUCC 0

struct s_board {
	int * cases; //cases of board
	int size;		 //board size
	int player;	 //current player
	int bot_color;		 //Bot information
};

/*****************************/
/********* ACCESSORS **********/
/******************************/
/*
Role: Swith current player on the board
In: board to change
Out: -
*/
void next_player(board b) {
	b->player = !b->player;
}

/*
Role: Getter for board's player
In: board
Out: current player
*/
int get_player(board b) {
	return b->player;
}

/*
Role: Getter for board's size
In: board
Out: size
*/
int board_get_size(board b) {
	return b->size;
}

/*
Role: Getter for board's cases
In: board
Out: pointer to board's state array
*/
int * get_board(board b) {
	return b->cases;
}

/*
Role: Getter for bot color
In: board
Out: cbot color
*/
int get_bot_color(board b) {
	return b->bot_color;
}

/*
Role: Setter for player if board
In: board
Out: current player
*/
void set_player(board b, int player) {
	b->player = player;
}

/****************************************/
/*********** BOARD MATH *****************/
/*****************************************/
/*
Role: Convert coordinates to unique case id
In: x, y, board
Out: unique case id
*/
int to_int(int x, int y, board b) {
	return x*b->size+y;
}

/*
Role: Check if turn is possible
In: board, case id
Out: true or false
*/
bool is_valid_turn(board b, int cell) {
	if (0 > cell || cell >= b->size*b->size)
		return false;
	if (b->cases[cell] != VIDE)
		return false;
	return true;
}

/****************************************/
/********** BOARD MANIPULATORS ***********/
/*****************************************/

/*
Role: Create new board of size "size"
In: size of board
Out: empty board
*/
board new_board(int size, int mod) {
	board b = malloc(sizeof(struct s_board));
	b->size = size;
	b->cases = malloc(sizeof(int) * size * size);
	for (int x = 0; x < size; x++) {
		for(int y = 0; y < size; y++){
      b->cases[x*size + y] = VIDE;
		}
	}
	b->player = RED;
	b->bot_color = mod;
	return b;
}

/*
Role: Do the turn: mark case of board on x, y as controled by current player
In: x, y, board
Out: -
*/
void add_case(board b, int x, int y) {
	b->cases[to_int(x, y, b)] = b->player;
}

/*
Role: set case x,y in player value
In: x, y, board, player
Out: -
*/
void set_case(board b, int pos, int player) {
	b->cases[pos] = player;
}

/*
Role: return case x, y value
In: x, y, board, player
Out: -
*/
int get_case(board b, int pos) {
	return b->cases[pos];
}

/*
Role: Show board on stdin
In: board
Out: -
*/
void print_board(board b) {
	char offset[b->size*2 +2];
	strcpy(offset, "");
	char hex_top[b->size * 4 + 1];
	char hex_bottom[b->size * 4 + 3];
	strcpy(hex_top, "");
	strcpy(hex_bottom,"");
	printf("*** Current player: %s ***\n", (b->player == RED)?"RED":"BLACK");
	printf("  ");
	for(int i = 0; i < b->size; i++) {
		printf("  B ");
	}
	printf("\n   ");
	for(int i = 0; i < b->size; i++) {
		strcat(hex_top, " / \\");
		strcat(hex_bottom, " \\ /");
		printf("  %d ", i);
	}
	printf("\n   %s\n", hex_top);
	for (int x = 0; x < b->size; x++) {
		printf("R%2d%s", x, offset);
		for(int y = 0; y < b->size; y++){
      switch (b->cases[to_int(x, y, b)]){
				case VIDE: printf("|   "); break;
				case RED: printf("| r "); break;
				case BLACK: printf("| b "); break;
			}
		}
		printf ("|\n");
		if (x != b->size - 1)
			printf("   %s%s \\\n", offset, hex_bottom);
		else
			printf("   %s%s\n", offset, hex_bottom);
		strcat(offset, "  ");
	}
}

/*
Role: Show board on stdin in the "old" style
In: board
Out: -
*/
void print_board_legacy(board b) {
	char text[b->size] ;
	strcpy(text,"") ;
	printf("    ");
	for (int i = 0 ; i < b->size ; i++) {
		printf("%d ", i);
	}
	printf("\n  ");
	for (int i = 0 ; i < b->size ; i++) {
		printf("B ");
	}

	printf("B/R\n");
	for (int x = 0; x < b->size; x++) {
		strcat(text," ") ;
		printf("%2d%s",x,text);
		printf("R ");
		for (int y = 0; y < b->size; y++) {
			switch (b->cases[to_int(x,y,b)]) {
				case VIDE: printf(". ");break ;
				case RED: printf("o ");break ;
				case BLACK: printf("* ");break ;
			}
		}
		printf("R\n");
	}
	printf("   %sR/B ",text);
	for (int i = 0; i < b->size; i++) {
		printf("B ");
	}
	printf("\n");
}

/*
Role: Delete board
In: board
Out: -
*/
void board_delete(board b) {
	free(b->cases);
	free(b);
}

/*
Role: Save current board to the file *.brd
In: board
Out: file or error code
*/
int board_to_file(board * b, char name[]) {
	char nom_fic[MAXNOM];
	strcpy(nom_fic, name);
	FILE * fic;

	/* File creation */
	strcat(nom_fic, ".txt"); //Add extention

	/* File re/creation */
	fic = fopen(nom_fic, "wt+");
	if (!fic) {
		fprintf(stderr, "Creation error!\n");
		return ERR_O;
	}

	/* Write in file */
	fprintf(fic, "\\hex\n");
	fprintf(fic, "\\dim %d\n", (*b)->size);
	fprintf(fic, "\\pl %d\n", (*b)->player);
	fprintf(fic, "\\bcl %d\n", (*b)->bot_color);
	fprintf(fic,"\\board\n");
	for (int x = 0; x < (*b)->size; x++) {
		for(int y = 0; y < (*b)->size; y++){
      switch ((*b)->cases[to_int(x, y, *b)]){
				case VIDE: fprintf(fic, ". "); break;
				case RED: fprintf(fic, "* "); break;
				case BLACK: fprintf(fic, "o "); break;
			}
		}
		fprintf(fic,"\n");
	}
	fprintf(fic,"\\endboard\n");
	fprintf(fic,"\\endhex\n");
	/* Fermeture */
	printf("Saved successfuly!\n");
	fclose(fic);
	return SUCC;
}

/*
Role: Load board from the file in the pointer to board
In: pointer to board
Out: board or error code
*/
int board_from_file(board * b, char name[]) {
	char nom_fic[MAXNOM];
	strcpy(nom_fic, name);
	FILE * fic;

	/* File reading */
	strcat(nom_fic, ".txt"); //Add extention
	fic = fopen(nom_fic, "r+");
	char temp;
	int s;
	/* Reading */
	fscanf(fic, "\\hex\n");
	fscanf(fic, "\\dim %d\n", &s);
	*b = new_board(s, -1);
	fscanf(fic, "\\pl %d\n", &((*b)->player));
	fscanf(fic, "\\bcl %d\n", &((*b)->bot_color));
	fscanf(fic,"\\board\n");
	for (int x = 0; x < (*b)->size; x++) {
		for(int y = 0; y < (*b)->size; y++){
			fscanf(fic,"%s ", &temp);
      switch (temp){
				case '*': (*b)->cases[to_int(x, y, *b)] = RED; break;
				case 'o': (*b)->cases[to_int(x, y, *b)] = BLACK; break;
				case '.': (*b)->cases[to_int(x, y, *b)] = VIDE; break;
			}
		}
		fscanf(fic,"\n");
	}
	fscanf(fic,"\\endboard\n");
	fscanf(fic,"\\endhex\n");
	/* Fermeture */
	fclose(fic);
	return SUCC;
}

/*
Role: Return pointer on board from the file
In: file name
Out: board or NULL in case of error
*/
board board_from_file_JAVA(char name[]) {
	char nom_fic[MAXNOM];
	strcpy(nom_fic, name);
	FILE * fic;

	/* File reading */
	strcat(nom_fic, ".txt"); //Add extention
	/* Here is testing of file existence */
	fic = fopen(nom_fic, "r+");
	char temp;
	int s;
	/* Reading */
	fscanf(fic, "\\hex\n");
	fscanf(fic, "\\dim %d\n", &s);
	board p = new_board(s, -1);
	fscanf(fic, "\\pl %d\n", &(p->player));
	fscanf(fic, "\\bcl %d\n", &(p->bot_color));
	fscanf(fic,"\\board\n");
	for (int x = 0; x < p->size; x++) {
		for(int y = 0; y < p->size; y++){
			fscanf(fic,"%s ", &temp);
      switch (temp){
				case '*': p->cases[to_int(x, y, p)] = RED; break;
				case 'o': p->cases[to_int(x, y, p)] = BLACK; break;
				case '.': p->cases[to_int(x, y, p)] = VIDE; break;
			}
		}
		fscanf(fic,"\n");
	}
	fscanf(fic,"\\endboard\n");
	fscanf(fic,"\\endhex\n");
	/* Fermeture */
	fclose(fic);
	return p;
}

/*
Role: Transform current board into a graph of cases owned by player (useful after file load)
In: board to transform, graph, current player
Out: graph with cases owned by player
*/
int board_to_graph_by_player(board b, Graph g, int player) {
	for (int i = 0; i < b->size * b->size; i++){
		if (b->cases[i] == player)
			graph_add_vertice(g, i, b->size);
	}
	return 0;
}



// Fonction auxiliaire qui détermine le nombre de pion présent dans le plateau
int nombre_de_pion(board b) {
  int nbPions = 0 ;
  for (int x = 0; x < b->size; x++) {
    for (int y = 0; y < b->size; y++) {
      if(b->cases[to_int(x,y,b)] != VIDE)
        nbPions++ ;
    }
  }
  return nbPions ;
}


void remove_case(board b , int x , int y) {
  b->cases[to_int(x,y,b)] = VIDE ;
}

bool possible_blow(board b , int cell) {
	return(b->cases[cell] == VIDE) ;
}
