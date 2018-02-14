===================
**HEX**  is a strategy board game for two players played on a hexagonal grid, theoretically of any size and several possible shapes, but traditionally as an 11×11 rhombus. 
-------------------


Installation
-------------
Before we started you got to have Java 8 Installed if it is not, enter flowing commands :
   

	    sudo add-apt-repository ppa:openjdk-r/ppa
        sudo apt-get update
        sudo apt-get install openjdk-8-jdk
        export JAVA_HOME=/usr/lib/jvm/java-1.8.0-openjdk-amd64

   ***Note:** java-1.8.0-openjdk-amd64 may be different for you. Try to find folder with simmilar name.*

Our game include makefile wich makes game compilation pretty simple just by taping command:


> make

After that in your *./bin* dirrecrotory will apperars all binary and library nessesery for the game.

Launching
-------------
To simplify game launching process, we created a bash script that sets up all the environment variable for the game and launch it.
> ./launch.sh
>
***Note** : current version is a little unstable so several launch may be necessary.*
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
