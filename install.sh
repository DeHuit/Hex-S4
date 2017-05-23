#!/bin/sh

if [ ! -e "obj" ]; then 
	mkdir obj > /dev/null
fi
if [ ! -e "bin" ]; then 
	mkdir bin > /dev/null
fi
if [ ! -e "bin/tests" ]; then 
	mkdir bin > /dev/null
fi

echo "Creating library"

if [ ! -f "src/C/board.c" ]; then 
	echo "board.c n'existe pas" >&2
	exit 1
fi

if [ ! -f "src/C/graph.c" ]; then
	echo "graph.c n'existe pas" >&2
	exit 2
fi

if [ ! -f "src/C/I_A.c" ]; then
	echo "I_A.c n'existe pas" >&2
	exit 3
fi

if [ ! -f "src/C/menu.c" ]; then
	echo "menu.c n'existe pas" >&2
	exit 4 
fi

if [ ! -f "src/C/PartC.c" ]; then
	echo "PartC.c n'existe pas" >&2
	exit 5
fi
	
gcc -fPIC -I$JAVA_HOME/include -I$JAVA_HOME/include/linux -c src/C/board.c src/C/graph.c src/C/I_A.c src/C/menu.c src/C/PartC.c
gcc -shared -o libpartc.so board.o graph.o I_A.o menu.o PartC.o
mv *.o ./obj/

echo "Compiling java"
cp src/Java/*.java ./
javac BoardPanel.java  MainWindow.java  PartC.java  SettingsWindow.java
mv ./*.class ./bin
rm *.java
mv libpartc.so ./bin
#rm ./bin/*\$*.class
