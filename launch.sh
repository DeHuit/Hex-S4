#! /bin/sh

cd ./bin

if [ ! -f "libpartc.so" ]; then 
	echo "libpartc.so does not exist! Recompile your program." >&2
	exit 1
fi

if [ ! -f "BoardPanel.class" ]; then
	echo "BoardPanel.class does not exist! Recompile your program." >&2
	exit 2
fi

if [ ! -f "SettingsWindow.class" ]; then
	echo "SettingsWindow.class does not exist! Recompile your program." >&2
	exit 3
fi

if [ ! -f "PartC.class" ]; then
	echo "PartC.class does not exist! Recompile your program." >&2
	exit 4 
fi

if [ ! -f "MainWindow.class" ]; then
	echo "MainWindow.class does not exist! Recompile your program." >&2
	exit 5
fi

LD_LIBRARY_PATH="$(pwd)"
export LD_LIBRARY_PATH

java MainWindow
