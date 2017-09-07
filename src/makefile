ObjCodeList = Main.o \
	Args.o \
	Rect.o \
	Circle.o \
	Object.o \
	RunCommands.o \
	ProcString.o \
	LinkedList.o \
	CreateSvg.o \
	CommandsT2.o \
	CommandsT3.o \
	Geometry.o \
	WriteTags.o \
	Cidade.o \
	ObjList.o \
	Quadra.o \
	Point.o \
	File.o \
	Resumo.o
gccCommand = gcc -Wall -pedantic -ansi -g

siguel : $(ObjCodeList)
	$(gccCommand) -o siguel $(ObjCodeList) -lm

Main.o : Main.c
	$(gccCommand) -o Main.o -c Main.c

Args.o : Args.c Args.h
	$(gccCommand) -o Args.o -c Args.c

Rect.o : Rect.c Rect.h
	$(gccCommand) -o Rect.o -c Rect.c

Circle.o : Circle.c Circle.h
	$(gccCommand) -o Circle.o -c Circle.c

Object.o : Object.c Object.h
	$(gccCommand) -o Object.o -c Object.c

RunCommands.o : RunCommands.c RunCommands.h
	$(gccCommand) -o RunCommands.o -c RunCommands.c

ProcString.o : ProcString.c ProcString.h
	$(gccCommand) -o ProcString.o -c ProcString.c

LinkedList.o : LinkedList.c LinkedList.h
	$(gccCommand) -o LinkedList.o -c LinkedList.c

CreateSvg.o : CreateSvg.c CreateSvg.h
	$(gccCommand) -o CreateSvg.o -c CreateSvg.c

CommandsT2.o : CommandsT2.h CommandsT2.c
	$(gccCommand) -o CommandsT2.o -c CommandsT2.c

CommandsT3.o : CommandsT3.h CommandsT3.c
	$(gccCommand) -o CommandsT3.o -c CommandsT3.c

Geometry.o : Geometry.h Geometry.c
	$(gccCommand) -o Geometry.o -c Geometry.c

WriteTags.o : WriteTags.h WriteTags.c
	$(gccCommand) -o WriteTags.o -c WriteTags.c

Cidade.o : Cidade.h Cidade.c
	$(gccCommand) -o Cidade.o -c Cidade.c

ObjList.o : ObjList.h ObjList.c
	$(gccCommand) -o ObjList.o -c ObjList.c

Quadra.o : Quadra.h Quadra.c
	$(gccCommand) -o Quadra.o -c Quadra.c

Point.o : Point.h Point.c
	$(gccCommand) -o Point.o -c Point.c

File.o : File.c File.h
	$(gccCommand) -o File.o -c File.c

Resumo.o : Resumo.h Resumo.c
	$(gccCommand) -o Resumo.o -c Resumo.c

clean :
	rm *.o
