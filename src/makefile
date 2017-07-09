ObjCodeList = Main.o Args.o Rect.o Circle.o RunCommands.o ProcString.o LinkedList.o CreateSvg.o ProcOIDA.o FreeObjList.o Geometry.o WriteTags.o
gccCommand = gcc -pedantic -ansi -g

t2 : $(ObjCodeList)
	$(gccCommand) -o t2 $(ObjCodeList) -lm

Main.o : Main.c
	$(gccCommand) -o Main.o -c Main.c

Args.o : Args.c Args.h
	$(gccCommand) -o Args.o -c Args.c

Rect.o : Rect.c Rect.h
	$(gccCommand) -o Rect.o -c Rect.c

Circle.o : Circle.c Circle.h
	$(gccCommand) -o Circle.o -c Circle.c

RunCommands.o : RunCommands.c RunCommands.h
	$(gccCommand) -o RunCommands.o -c RunCommands.c

ProcString.o : ProcString.c ProcString.h
	$(gccCommand) -o ProcString.o -c ProcString.c

LinkedList.o : LinkedList.c LinkedList.h
	$(gccCommand) -o LinkedList.o -c LinkedList.c

CreateSvg.o : CreateSvg.c CreateSvg.h
	$(gccCommand) -o CreateSvg.o -c CreateSvg.c

FreeObjList.o : FreeObjList.h FreeObjList.c
	$(gccCommand) -o FreeObjList.o -c FreeObjList.c

ProcOIDA.o : ProcOIDA.h ProcOIDA.c
	$(gccCommand) -o ProcOIDA.o -c ProcOIDA.c

Geometry.o : Geometry.h Geometry.c
	$(gccCommand) -o Geometry.o -c Geometry.c

WriteTags.o : WriteTags.h WriteTags.c
	$(gccCommand) -o WriteTags.o -c WriteTags.c

clean :
	rm *.o
