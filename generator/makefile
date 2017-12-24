ObjCodeList = Main.o
gccCommand = gcc -Wall -Wextra -pedantic -ansi -g

gen : $(ObjCodeList)
	$(gccCommand) -o gen $(ObjCodeList) -lm

Main.o : Main.c
	$(gccCommand) -o Main.o -c Main.c
