#include <stdlib.h>
#include <stdio.h>
#include "Circle.h"
#include "Rect.h"
#include "Quadra.h"
#include "Point.h"
#include "Object.h"
#include "ProcString.h"
#include "LinkedList.h"
#include "CommandsT2.h"
#include "CommandsT3.h"
#include "CreateSvg.h"
#include "RunCommands.h"
#include "Cidade.h"
#include "ObjList.h"
#include "Args.h"
#include "File.h"
#include "Resumo.h"

int runCommands( Args *args ){
	FILE *inFileGeo, *inFileQry, *outFileTxt, *outResumoTxt;
	char line[1000];
	char *fileQry, *fileGeo, *inDir, *outDir;
	char *fullPathGeo, *fullPathQry, *fullPathTxt, *fullPathResumo;
	char *nameFiles, *nameFileGeo, *nameFileQry;
	List *objs;
	Cidade *cidade;
	Resumo *res;
	int error;

	inDir = NULL;
	nameFileQry = NULL;
	fullPathQry = NULL;
	fullPathTxt = NULL;
	fullPathResumo = NULL;

	inFileQry = NULL;
	outFileTxt = NULL;
	outResumoTxt = NULL;

	error = 0;

	fileGeo = getArgsF(args);
	fileQry = getArgsQ(args);
	if( getArgsE(args) != NULL ){
		inDir = fixDir( getArgsE(args) );
	}
	outDir = fixDir( getArgsO(args) );
	nameFileGeo = fileRemovePathExt(fileGeo);
	if( getArgsQ(args) != NULL ){
		nameFileQry = fileRemovePathExt(fileQry);
	}
	if( getArgsQ(args) != NULL ){
		nameFiles = createStringCat( nameFileGeo, "-", nameFileQry, NULL, NULL );
	}
	else{
		nameFiles = createString( nameFileGeo );
	}

	fullPathGeo = createStringCat( inDir, fileGeo, NULL, NULL, NULL );
	inFileGeo = openFileRead( fullPathGeo );
	if( inFileGeo == NULL ){
		error++;
	}

	if( getArgsQ(args) != NULL ){
		if( error == 0 ){
			fullPathQry = createStringCat( inDir, fileQry, NULL, NULL, NULL );
			inFileQry = openFileRead( fullPathQry );
			if( inFileQry == NULL ){
				error++;
			}
		}
	}

	if( error == 0 ){
		fullPathTxt = createStringCat( outDir, nameFiles, ".txt", NULL, NULL );
		outFileTxt = openFileWrite( fullPathTxt );
		if( outFileTxt == NULL ){
			error++;
		}
	}

	if( getArgsAcc(args) == 1 || getArgsAcc0(args) == 1 ){
		if( error == 0 ){
			fullPathResumo = createStringCat( outDir, "resumo.txt", NULL, NULL, NULL );
			if( getArgsAcc(args) == 1 ){
				outResumoTxt = openFileAppend(fullPathResumo);
				if( outResumoTxt == NULL ){
					error++;
				}
			}
			else if( getArgsAcc0(args) == 1 ){
				outResumoTxt = openFileWrite(fullPathResumo);
				if( outResumoTxt == NULL ){
					error++;
				}
			}
		}
	}

	if( error == 0 ){
		objs = createList();
		cidade = createCidade();
		if( getArgsAcc(args) == 1 || getArgsAcc0(args) == 1 ){
			res = createResumo();
		}
		else{
			res = NULL;
		}
		while( fgets(line,1000,inFileGeo) != NULL ){
			switch( line[0] ){
				case 'c':
					switch( line[1] ){
						case 'q':
							commandCidadeColors(line, cidade);
							break;
						case 'h':
							commandCidadeColors(line, cidade);
							break;
						case 's':
							commandCidadeColors(line, cidade);
							break;
						case 't':
							commandCidadeColors(line, cidade);
							break;
						default:
							procC(line, objs);
					}
					break;
				case 'r':
	                procR(line, objs);
					break;
				case 'o':
					procO( line, objs, outFileTxt );
					break;
				case 'i':
					procI( line, objs, outFileTxt );
					break;
				case 'd':
					procD( line, objs, outFileTxt );
					break;
				case 'a':
					procA( line, objs, nameFileGeo, outDir );
					break;
				case 'q':
					commandCidadeInsert( line, cidade, res );
					break;
				case 'h':
					commandCidadeInsert( line, cidade, res );
					break;
				case 's':
					commandCidadeInsert( line, cidade, res );
					break;
				case 't':
					commandCidadeInsert( line, cidade, res );
					break;
	            case 'p':
					procP(objs,cidade);
					break;
	            case 'z':
					procZ(cidade);
					break;
			}
		}
		if( getArgsQ(args) != NULL ){
			while( fgets(line,1000,inFileQry) != NULL ){
				switch( line[0] ){
					case 'd':
						switch( line[1] ){
							case 'q':
								commandCidadeDeleteRect( line, cidade, outFileTxt, res );
								break;
							case 'h':
								commandCidadeDeleteRect( line, cidade, outFileTxt, res );
								break;
							case 's':
								commandCidadeDeleteRect( line, cidade, outFileTxt, res );
								break;
							case 't':
								commandCidadeDeleteRect( line, cidade, outFileTxt, res );
								break;
						}
						break;
					case 'D':
						switch( line[1] ){
							case 'q':
								commandCidadeDeleteCircle( line, cidade, outFileTxt, res );
								break;
							case 'h':
								commandCidadeDeleteCircle( line, cidade, outFileTxt, res );
								break;
							case 's':
								commandCidadeDeleteCircle( line, cidade, outFileTxt, res );
								break;
							case 't':
								commandCidadeDeleteCircle( line, cidade, outFileTxt, res );
								break;
						}
						break;
					case 'c':
						if( line[1] == 'r' && line[2] == 'd' ){
							commandSearchIdCep( line, cidade, outFileTxt );
						}
						break;
				}
			}
		}
		createSvg(objs, cidade, nameFiles, outDir);
		destroyObjList(objs);
		destroyCidade(cidade);
		if( getArgsAcc(args) == 1 || getArgsAcc0(args) == 1 ){
			printResumo( res, nameFiles, outResumoTxt );
			destroyResumo(res);
		}
	}

	closeFile(inFileGeo);
	closeFile(inFileQry);
	closeFile(outFileTxt);
	closeFile(outResumoTxt);

	destroyString(inDir);
	destroyString(outDir);
	destroyString(nameFileGeo);
	destroyString(nameFileQry);
	destroyString(nameFiles);
	destroyString(fullPathGeo);
	destroyString(fullPathQry);
	destroyString(fullPathTxt);
	destroyString(fullPathResumo);

	if( error != 0 ){
		return 1;
	}
	return 0;
}

void procP( List *objs, Cidade *cidade ){
	int k;
	Node *node;
	List *list;
	char objType;
	void *objData;

	k = 0;
	node = getFirst(objs);
	list = objs;
	while( node != NULL ){
		objType = getObjType( get(list,node) );
		objData = getObjData( get(list,node) );
		printf("Objetos - [%d]\n",k);
		if( objType == 'c' ){
			printf("\ttype = %c\n", objType );
			printf("\ti = %d\n",    getCircleId( objData ) );
			printf("\tr = %f\n",    getCircleRadius( objData ) );
			printf("\tx = %f\n",    getCircleX( objData ) );
			printf("\ty = %f\n",    getCircleY( objData ) );
			printf("\tfill = %s\n", getCircleFill( objData ) );
		}
		else if( objType == 'r' || objType == 'o' ){
			printf("\ttype = %c\n", objType );
			printf("\ti = %d\n",    getRectId( objData ) );
			printf("\tw = %f\n",    getRectWidth( objData ) );
			printf("\tx = %f\n",    getRectX( objData ) );
			printf("\th = %f\n",    getRectHeight( objData ) );
			printf("\tx = %f\n",    getRectX( objData ) );
			printf("\ty = %f\n",    getRectY( objData ) );
			printf("\tfill = %s\n", getRectFill( objData ) );
		}
		k++;
		node = getNext(list,node);
	}

	list = getCidadeQuadras(cidade);
	node = getFirst(list);
	k = 0;
	while( node != NULL ){
		objData = getObjData( get(list,node) );
		printf("Cidade - Quadras - [%d]\n",k);
		printf("\ttype = %c\n",   getObjType( get(list,node) ) );
		printf("\tx = %f\n",      getQuadraX( objData ) );
		printf("\ty = %f\n",      getQuadraY( objData ) );
		printf("\twidth = %f\n",  getQuadraWidth( objData ) );
		printf("\theight = %f\n", getQuadraHeight( objData ) );
		printf("\tcep = %s\n",    getQuadraCep( objData ) );
		printf("\tfill = %s\n",   getQuadraFill( objData ) );
		printf("\tstroke = %s\n", getQuadraStroke( objData ) );
		k++;
		node = getNext(list,node);
	}

	list = getCidadeHidrantes(cidade);
	node = getFirst(list);
	k = 0;
	while( node != NULL ){
		objData = getObjData( get(list,node) );
		printf("Cidade - Hidrantes - [%d]\n",k);
		printf("\ttype = %c\n",   getObjType( get(list,node) ) );
		printf("\tx = %f\n",      getPointX( objData ) );
		printf("\ty = %f\n",      getPointY( objData ) );
		printf("\tid = %s\n",     getPointId( objData ) );
		printf("\tfill = %s\n",   getPointFill( objData ) );
		printf("\tstroke = %s\n", getPointStroke( objData ) );
		k++;
		node = getNext(list,node);
	}

	list = getCidadeSemaforos(cidade);
	node = getFirst(list);
	k = 0;
	while( node != NULL ){
		objData = getObjData( get(list,node) );
		printf("Cidade - Semaforos - [%d]\n",k);
		printf("\ttype = %c\n",   getObjType( get(list,node) ) );
		printf("\tx = %f\n",      getPointX( objData ) );
		printf("\ty = %f\n",      getPointY( objData ) );
		printf("\tid = %s\n",     getPointId( objData ) );
		printf("\tfill = %s\n",   getPointFill( objData ) );
		printf("\tstroke = %s\n", getPointStroke( objData ) );
		k++;
		node = getNext(list,node);
	}

	list = getCidadeSemaforos(cidade);
	node = getFirst(list);
	k = 0;
	while( node != NULL ){
		objData = getObjData( get(list,node) );
		printf("Cidade - Radios-Base - [%d]\n",k);
		printf("\ttype = %c\n",   getObjType( get(list,node) ) );
		printf("\tx = %f\n",      getPointX( objData ) );
		printf("\ty = %f\n",      getPointY( objData ) );
		printf("\tid = %s\n",     getPointId( objData ) );
		printf("\tfill = %s\n",   getPointFill( objData ) );
		printf("\tstroke = %s\n", getPointStroke( objData ) );
		k++;
		node = getNext(list,node);
	}
}

void procZ( Cidade *cidade ){
	printf("Quadras:\n");
	printf("\tfill = %s\n",getCidadeQuadrasFill(cidade));
	printf("\tstroke = %s\n",getCidadeQuadrasStroke(cidade));
	printf("Hidrantes:\n");
	printf("\tfill = %s\n",getCidadeHidrantesFill(cidade));
	printf("\tstroke = %s\n",getCidadeHidrantesStroke(cidade));
	printf("Semaforos:\n");
	printf("\tfill = %s\n",getCidadeSemaforosFill(cidade));
	printf("\tstroke = %s\n",getCidadeSemaforosStroke(cidade));
	printf("Torres:\n");
	printf("\tfill = %s\n",getCidadeTorresFill(cidade));
	printf("\tstroke = %s\n",getCidadeTorresStroke(cidade));
}
