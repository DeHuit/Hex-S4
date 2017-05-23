//
//  Created by dehuit on 15/05/2017
//
#include <stdio.h>
#include <malloc.h>

#include "I_A.h"

struct s_minmax {
  board b ;
  int size ;
  int profondeur ;
  Graph j_humain ;
  Graph j_IA ;
} ;

MinMax new_minmax(board b , int profondeur , Graph j_h , Graph j_IA , int size) {
  MinMax m = (MinMax)malloc(sizeof(struct s_minmax)) ;
  m->size = size ;
  m->b = b ;
  m->profondeur = profondeur ;
  m->j_humain = j_h ;
  m->j_IA = j_IA ;
  return m ;
}

void minmax_delete(MinMax m) {
  free(m) ;
}

int IA_Jouer(MinMax m , int profondeur) {
  int valeurMaximale = -10000;
  int tmp;
  int maxX = 0; //correspond a l'abscisse de la case sur laquelle le pion sera reellement joue
  int maxY = 0; //correspond a l'ordonnée de la case sur laquelle le pion sera reellement joue
  //boucle qui permet de parcourir toute les cases du plateau
  for (int x = 0; x < m->size; x++) {
    for (int y = 0; y < m->size; y++) {
      /*Si la case est libre on considere que l'adversaire de l'ia peut jouer
        à cette case donc on l'ajoute dans la liste des coups joués*/
      if(possible_blow(m->b,to_int(x,y,m->b))) {
        add_case(m->b,x,y) ;
        graph_add_vertice(m->j_humain,to_int(x,y,m->b),m->size) ;
        tmp = min(m) ;
        m->profondeur = profondeur ;
        if (tmp > valeurMaximale || ((tmp == valeurMaximale) && (rand()%2 == 0))) {
          valeurMaximale = tmp ;
          maxX = x ;
          maxY = y ;
        }
        remove_case(m->b,x,y) ;
        graph_remove_vertice(m->j_humain,to_int(x,y,m->b)) ;
      }
    }
  }
  return(to_int(maxX,maxY,m->b)) ;
}

int min(MinMax m) {
  // On considère que le joueur humain réprésente les red et l'ia les black
  /* Si la profondeur est nulle ou que un des deux joueur a gagner
     on retourne le nombre de chaine gagnante de chaque joueur */
  if(((m->profondeur) == 0) || (is_red_winner(m->j_humain,m->size)) || (is_black_winner(m->j_IA,m->size))) {
    return eval(m) ;
  }
  int valeurMinimale = 10000 ;
  int tmp ;
  for (int x = 0; x < m->size; x++) {
    for (int y = 0; y < m->size; y++) {
      if (possible_blow(m->b,to_int(x,y,m->b)) && ((m->profondeur) > 0)) {
        add_case(m->b,x,y) ;
        graph_add_vertice(m->j_humain,to_int(x,y,m->b),m->size) ;
        (m->profondeur)-- ;
        tmp = max(m) ;
        if (tmp < valeurMinimale || ((tmp == valeurMinimale) && (rand()%2 == 0))) {
          valeurMinimale = tmp ;
        }
        remove_case(m->b,x,y) ;
        graph_remove_vertice(m->j_humain,to_int(x,y,m->b)) ;
      }
    }
  }
  return valeurMinimale ;
}

int max(MinMax m) {
  if(((m->profondeur) == 0) || (is_red_winner(m->j_humain,m->size)) || (is_black_winner(m->j_IA,m->size))) {
    return eval(m) ;
  }
  int valeurMaximale = -10000 ;
  int tmp ;
  for (int x = 0; x < m->size; x++) {
    for (int y = 0; y < m->size; y++) {
      if (possible_blow(m->b,to_int(x,y,m->b)) && ((m->profondeur) > 0)) {
        add_case(m->b,x,y) ;
        graph_add_vertice(m->j_IA,to_int(x,y,m->b),m->size) ;
        (m->profondeur)-- ;
        tmp = min(m) ;
        if (tmp > valeurMaximale || ((tmp == valeurMaximale) && (rand()%2 == 0))) {
          valeurMaximale = tmp ;
        }
        remove_case(m->b,x,y) ;
        graph_remove_vertice(m->j_IA,to_int(x,y,m->b)) ;
      }
    }
  }
  return valeurMaximale ;
}

int eval(MinMax m) {
  int nbPions ;
  //Nombre de pion présent sur le plateau
  nbPions = nombre_de_pion(m->b) ;
  if(is_red_winner(m->j_humain,m->size))
    return 1000 - nbPions ;
  else if(is_black_winner(m->j_IA,m->size))
    return -1000 + nbPions ;
  return nbPions ;
}
