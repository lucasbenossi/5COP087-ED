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
	CommandsT4.o \
	CommandsDebug.o \
	Geometry.o \
	WriteTags.o \
	Cidade.o \
	ObjList.o \
	ObjQuadTree.o \
	Quadra.o \
	Point.o \
	File.o \
	Resumo.o \
	ConvexHull.o \
	Stack.o \
	QuadTree.o \
	QuadTreeDeletion.o \
	QuickSort.o \
	Array.o \
	DumpQuadTree.o \
	Polygon.o

gccCommand = gcc -Wall -pedantic -ansi -g

siguel : $(ObjCodeList)
	$(gccCommand) $(ObjCodeList) -lm -o siguel

Main.o : Main.c
	$(gccCommand) -c Main.c -o Main.o

Args.o : Args.c Args.h
	$(gccCommand) -c Args.c -o Args.o

Object.o : Object.c Object.h
	$(gccCommand) -c Object.c -o Object.o

Rect.o : Rect.c Rect.h
	$(gccCommand) -c Rect.c -o Rect.o

Circle.o : Circle.c Circle.h
	$(gccCommand) -c Circle.c -o Circle.o

Quadra.o : Quadra.h Quadra.c
	$(gccCommand) -c Quadra.c -o Quadra.o

Point.o : Point.h Point.c
	$(gccCommand) -c Point.c -o Point.o

Polygon.o : Polygon.h Polygon.c
	$(gccCommand) -c Polygon.c -o Polygon.o

RunCommands.o : RunCommands.c RunCommands.h
	$(gccCommand) -c RunCommands.c -o RunCommands.o

ProcString.o : ProcString.c ProcString.h
	$(gccCommand) -c ProcString.c -o ProcString.o

LinkedList.o : LinkedList.c LinkedList.h
	$(gccCommand) -c LinkedList.c -o LinkedList.o

CreateSvg.o : CreateSvg.c CreateSvg.h
	$(gccCommand) -c CreateSvg.c -o CreateSvg.o

CommandsT2.o : CommandsT2.h CommandsT2.c
	$(gccCommand) -c CommandsT2.c -o CommandsT2.o

CommandsT3.o : CommandsT3.h CommandsT3.c
	$(gccCommand) -c CommandsT3.c -o CommandsT3.o

CommandsT4.o : CommandsT4.h CommandsT4.c
	$(gccCommand) -c CommandsT4.c -o CommandsT4.o

CommandsDebug.o : CommandsDebug.h CommandsDebug.c
	$(gccCommand) -c CommandsDebug.c -o CommandsDebug.o

Geometry.o : Geometry.h Geometry.c
	$(gccCommand) -c Geometry.c -o Geometry.o

WriteTags.o : WriteTags.h WriteTags.c
	$(gccCommand) -c WriteTags.c -o WriteTags.o

Cidade.o : Cidade.h Cidade.c
	$(gccCommand) -c Cidade.c -o Cidade.o

ObjList.o : ObjList.h ObjList.c
	$(gccCommand) -c ObjList.c -o ObjList.o

ObjQuadTree.o : ObjQuadTree.h ObjQuadTree.c
	$(gccCommand) -c ObjQuadTree.c -o ObjQuadTree.o

File.o : File.c File.h
	$(gccCommand) -c File.c -o File.o

Resumo.o : Resumo.h Resumo.c
	$(gccCommand) -c Resumo.c -o Resumo.o

ConvexHull.o : ConvexHull.h ConvexHull.c
	$(gccCommand) -c ConvexHull.c -o ConvexHull.o

Stack.o : Stack.h Stack.c
	$(gccCommand) -c Stack.c -o Stack.o

QuadTree.o : QuadTree.h QuadTree.c
	$(gccCommand) -c QuadTree.c -o QuadTree.o

QuadTreeDeletion.o : QuadTreeDeletion.h QuadTreeDeletion.c
	$(gccCommand) -c QuadTreeDeletion.c -o QuadTreeDeletion.o

QuickSort.o : QuickSort.h QuickSort.c
	$(gccCommand) -c QuickSort.c -o QuickSort.o

Array.o : Array.h Array.c
	$(gccCommand) -c Array.c -o Array.o

DumpQuadTree.o : DumpQuadTree.h DumpQuadTree.c
	$(gccCommand) -c DumpQuadTree.c -o DumpQuadTree.o

clean :
	rm *.o

check :
	$(gccCommand) -fsyntax-only *.c *.h
