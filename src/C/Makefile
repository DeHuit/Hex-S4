.PHONY: all test_board test_graph test_game clean maxclean

CC=gcc
CFLAGS= -Wall -std=c99
LDFLAGS=-lm
EXEC=hex
OBJ=board.o graph.o menu.o hex.o
TEST=t
BOARD_TEST=board.o graph.o test_board.o
GRAPH_TEST=graph.o test_graph.o
GAME_TEST=graph.o board.o test_game.o
MENU_TEST=graph.o board.o menu.o test_menu.o
AI_TEST=graph.o board.o menu.o I_A.o test_IA.o

all:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

test_board: $(BOARD_TEST)
	$(CC) $(CFLAGS) $(BOARD_TEST) -o $(TEST) $(LDFLAGS)

test_graph:	$(GRAPH_TEST)
	$(CC) $(CFLAGS) $(GRAPH_TEST) -o $(TEST) $(LDFLAGS)

test_game:	$(GAME_TEST)
	$(CC) $(CFLAGS) $(GAME_TEST) -o $(TEST) $(LDFLAGS)

test_menu:	$(MENU_TEST)
		$(CC) $(CFLAGS) $(MENU_TEST) -o $(TEST) $(LDFLAGS)

test_AI:	$(AI_TEST)
	$(CC) $(CFLAGS) $(AI_TEST) -o $(TEST) $(LDFLAGS)

board.o:	board.c board.h
graph.o:  graph.c graph.h
menu.o:  menu.c menu.h
I_A.o: I_A.c I_A.h
test_graph.o: test_graph.c
test_board.o:	test_board.c
test_game.o:	test_game.c
test_menu.o:	test_menu.c
test_IA.o: test_IA.c
hex.o:	hex.c

clean:
	rm -rf *.o

maxclean: clean
	  rm -rf $(EXEC) $(TEST)
