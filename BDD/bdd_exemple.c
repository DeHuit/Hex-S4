#include "graph.h"
#include "board.h"
#include "menu.h"

int main(){
  Graph red = new_graph();
  Graph black = new_graph();
  int size = size_board();
  board b = new_board(size, -1);
  List history = new_list();
  
  /* création de la base de données */
  MYSQL mysql;

  /* initialisation de MySQL */
  mysql_init(&mysql);
      
  /* connection à la base de données */
  mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");

  if (mysql_real_connect(&mysql,"localhost","hex","Toulouse31","bdd_hex",0,NULL,0)){	
      printf("Connexion à la base de donnée reussi\n");
	
      /* création des tables */
      mysql_query(&mysql, "CREATE TABLE Joueur(numJoueur NUMBER(10),pseudo VARCHAR(10),email VARCHAR(20),anneeNaiss NUMBER (4),CONSTRAINT pk_Joueur PRIMARY KEY (numJoueur),CONSTRAINT nn_numJoueur check (numJoueur is NOT NULL),CONSTRAINT nn_pseudo check (pseudo is NOT NULL),CONSTRAINT nn_email check (email is NOT NULL),CONSTRAINT nn_anneeNaiss check (anneeNaiss is NOT NULL));");
      mysql_query(&mysql, "CREATE TABLE Partie(numPartie NUMBER(10),CONSTRAINT pk_Partie PRIMARY KEY (numPartie),CONSTRAINT nn_numPartie check (numPartie is NOT NULL));");
      mysql_query(&mysql, "CREATE TABLE Rencontrer(numJoueur1 NUMBER(10),numJoueur2 NUMBER(10),CONSTRAINT pk_Rencontrer PRIMARY KEY (numJoueur1, numJoueur2));");
      mysql_query(&mysql, "CREATE TABLE Participer(pion VARCHAR(1),gagner VARCHAR(10),abandonner VARCHAR(10),datePartie VARCHAR(10),numPartie NUMBER(10),numJoueur NUMBER(10),CONSTRAINT nn_numeroJoueur check (numJoueur is NOT NULL),CONSTRAINT nn_numberPartie check (numPartie is NOT NULL),CONSTRAINT fk_Joueur FOREIGN KEY (numJoueur) REFERENCES Joueur(numJoueur),CONSTRAINT fk_Partie FOREIGN KEY (numPartie) REFERENCES Partie(numPartie));");
      mysql_query(&mysql, "CREATE TABLE Jouer(numCoups NUMBER(3),ligne NUMBER(3),colonne NUMBER(3),numJoueur NUMBER(10),numPartie NUMBER(10),CONSTRAINT pk_Jouer PRIMARY KEY (numCoups),CONSTRAINT nn_numberJoueur check (numJoueur is NOT NULL),CONSTRAINT nn_Partie check (numPartie is NOT NULL),CONSTRAINT fk_Jouer FOREIGN KEY (numJoueur) REFERENCES Joueur(numJoueur),CONSTRAINT fk_JouerPartie FOREIGN KEY (numPartie) REFERENCES Partie(numPartie));");
 	  
	  
      /* on declare un tableau de caractères pour y stocker la requete dans la table Joueur puis on la stocke */
      char requete[150] = " ";
      sprintf(requete, "Insert into Joueur (numJoueur, pseudo, email, anneeNaiss) values ('%d', '%s', '%s', '%d')" , p1, pseudo, email, ann);
      /* execution requete */
      mysql_query(&mysql,requete);
     
      player_choice(b);
      player p1, p2;
      int x, y, i = 1;
      int numCoups = 1;
      int numPartie = 1;
      
      if (get_player(b) == RED)
	  printf("Saisie des données joueur %d \n", get_player(b));
	  p1 = new_user();
      next_player(b);
      printf("Saisie des données joueur %d \n", get_player(b));
      p2 = new_user();
      next_player(b);
      
      /* insertion du numero de partie dans la table Partie */ 
      sprintf(requete, "Insert into Partie (numPartie) values ('%d')", numPartie);
      /* execution requete */
      mysql_query(&mysql,requete);
      
      /* insertion des joueurs dans la table Rencontrer */ 
      sprintf(requete, " Insert into Rencontrer (numJoueur1, numJoueur2) values ('%s', '%s')", p1, p2);
      /* execution requete */
      mysql_query(&mysql,requete);
	  
  
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
	
	/* insertion des coups jouer d'une partie dans la table Jouer */
	sprintf(requete, "Insert into Jouer (numCoups, ligne, colonne, numJoueur, numPartie) values ('%d', '%d', '%d', '%d', '%d');", numCoups, x, y, get_player(b), numPartie);
	/* execution requete */
	mysql_query(&mysql,requete);
	
	/* Add new turn to the history*/
	history_add_turn(history, i++, to_int(x, y, b));
	next_player(b);
	numCoups++;	
      }
      numPartie ++;
      printf("%s\n", (is_red_winner(red, size))?"Red is winner!":"Black is winner!");
      
      /* insertion de la fin d'une partie dans la table participer */
      sprintf(requete, "Insert into Participer (pion, gagner, abandonner, datePartie, numJoueur, numPartie) values ('%s', '%s', '%s', '%s', '%d', '%d');", pion, winner, ab, dateP, p1, numPartie);
      /* execution requete */
      mysql_query(&mysql,requete);
      
      graph_delete(red);
      graph_delete(black);
      board_delete(b);
  }
  else{
      printf("Probleme de connexion\n");
  }
  /* fermeture de MySQL */
  mysql_close(&mysql);
}
