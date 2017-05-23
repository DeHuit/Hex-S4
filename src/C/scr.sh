#! /bin/sh

cd "./src/C"

if [ ! -e "../../obj" ]; then 
	mkdir ../../obj > /dev/null
fi
if [ ! -e "../../bin" ]; then 
	mkdir ../../bin > /dev/null
fi
if [ ! -e "../../bin/tests" ]; then 
	mkdir ../../bin/tests > /dev/null
else
	rm ../../bin/tests/*
fi



make test_board
mv t ../../bin/tests/test_board
make test_graph
mv t ../../bin/tests/test_graph
make test_AI
mv t ../../bin/tests/test_AI
make test_menu
mv t ../../bin/tests/test_menu
make test_game
mv t ../../bin/tests/test_game
make maxclean
clear
echo "\n\nAll tests are in ./bin/C"
