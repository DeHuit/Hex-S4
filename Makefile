.PHONY: all tests clean maxclean

all:	
	./install.sh

tests:  
	./src/C/scr.sh

clean:
	rm -rf obj/*.o 
	rm -rf bin/*.class bin/*.so

maxclean: clean
	  rm -rf bin/tests/*
