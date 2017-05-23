Hex!
===================
**HEX**  is a strategy board game for two players played on a hexagonal grid, theoretically of any size and several possible shapes, but traditionally as an 11×11 rhombus. 
----------


Installation
-------------
Our game include makefile wich makes game compilation pretty simple just by launching a command:


> make

After that in your *./bin* dirrecrotory will apperars all binary and library nessesery for the game.

Launching
-------------
For the reason of simple game launching we created a bash script that sets up all the enviromment variable nessesery for the game and launch it.
> ./launch.sh

After all the tests will be available in *./bin/tests/* dirrectory
Here we have list of them


Tests
--------------------
If you want to test modules functonnality separetly, you can make run compilation of unit tests binary by launching:

> make tests

Test           | Desciption              | Launching command
-------------- | ------------------------|------------------
test_board     | Unit test of “board” module |./bin/tests/test_board
test_graph | Unit test of “graph” module | ./bin/tests/test_graph
test_AI | Unit test of  “AI” module | ./bin/tests/test_AI
test_menu | Unit test of  “menu” (history) | ./bin/tests/test_menu
test_game | Test of the game in C only | ./bin/tests/test_game
