ObjCodeList = Main.o
gccCommand = gcc -pedantic -ansi -g

gen : $(ObjCodeList)
	$(gccCommand) -o gen $(ObjCodeList) -lm

Main.o : Main.c
	$(gccCommand) -o Main.o -c Main.c
