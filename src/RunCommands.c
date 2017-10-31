#include "RunCommands.h"
#include <stdlib.h>
#include <string.h>
#include "Cidade.h"
#include "Object.h"
#include "Circle.h"
#include "Rect.h"
#include "Quadra.h"
#include "Point.h"
#include "ProcString.h"
#include "LinkedList.h"
#include "CommandsT2.h"
#include "CommandsT3.h"
#include "CommandsT4.h"
#include "CommandsDebug.h"
#include "CreateSvg.h"
#include "ObjList.h"
#include "File.h"
#include "Resumo.h"
#include "Polygon.h"

/*
Argumentos fornecidos na linha de comando:
|    -acc0              Cria resumo.txt
|    -acc               Abre resumo.txt para append
|    -e <path>          Diretório com arquivos de entrada
|    -o <path>          Diretório de saida de arquivos
|    -f <arq.geo>       Arquivo de entrada com elementos a serem inseridos
|    -q <arq.qry>       Arquivo de entrada com testes a serem feitos
|    -id                Imprime nome e matrícula na saída padrão
|    -m <n>			    Chama cidadeListToQuadTree() com method = <n>.
|	 -d <obj>    	    Dumpa QuadTree.
|	 -t 				Gera svg com raio de cobertura das torres.
|	 -noT2				Não coloca objetos do T2 na saiva svg.
|	 -r <raio>			Raio de cobertura padrão para as torres.
|	 -g <obj>			Gera <nameGeo>-<nameQry>-convexhull.{svg,txt} com os envoltórios convexos dos objetos
|	 -h <obj>			Gera <nameGeo>-<nameQry>-convexhull.{svg,txt} com os envoltórios convexos com colineares dos objetos
|	 -I					Dumpa as informações específicas de toadas as intancias de Point no arquivo nameGeo-nameQry-info.txt

Comandos T2:
|	c <i> <r> <x> <y> <fill>       Cria um círculo
|	r <i> <w> <h> <x> <y> <fill>   Cria um retangulo
|	o <j> <k>                      Verifica se as formas com ids j e k se sobrepoem (saidas colocadas em arg.txt)
|	i <j> <x> <y>                  Verifica se o ponto (x,y) está dentro da forma com id j (saidas colocadas em arg.txt)
|	d <j> <k>                      Verifica a distancia entre os centros das formas com ids j e k (saidas colocadas em arg.txt)
|	a <sufix> <fill>			   Cria um arquivo svg, mostrando apenas os
|	                               centros dos círculos e os cantos dos
|	                               retângulos criados pelos comandos c e r.

Comandos T3:
|  .geo
|    q <x> <y> <larg> <alt> <cep>      Insere uma quadra (retângulo e cep)
|    h <x> <y> <id>                    Insere um hidrante
|    s <x> <y> <id>                    Insere um semáforo
|    t <x> <y> <id>                    Insere uma rádio-base (torre de celular)
|    cq <cfill> <cstrk>                Cores do preenchimento e da borda das quadras (a partir deste comando)
|    ch <cfill> <cstrk>                Cores do preenchimento e da borda dos hidrantes (a partir deste comando)
|    ct <cfill> <cstrk>                Cores do preenchimento e da borda das torres de celular (a partir deste comando)
|    cs <cfill> <cstrk>                Cores do preenchimento e da borda dos semáforos (a partir deste comando)
|  .qry (saidas colocadas em nameGeo-nameQry.txt)
|    dq <x> <y> <larg> <alt>           Remove todas quadras que estiverem inteiramente dentro do retângulo.
|    dh <x> <y> <larg> <alt>           Semelhante ao dq. Remove os hidrantes dentro da região.
|    ds <x> <y> <larg> <alt>           Semelhante dq. Remove os semáforos da região.
|    dt <x> <y> <larg> <alt>           Semelhante dq. Remove as torres de celular dentro da região.
|    Dq <x> <y> <raio>                 Remove todas as quadras que estiverem inteiramente contidas dentro do círculo.
|    Dh <x> <y> <raio>                 Semelhante a Dq. Remove os hidrantes dentro da região.
|    Ds <x> <y> <raio>                 Semelhante a Dq. Remove os semáforos dentro da região.
|    Dt <x> <y> <raio>                 Semelhante a Dq. Remove as torres de celular dentro da região.
|    crd? <cep|id>                     Imprime no arquivo .txt as coordenadas e a espécie do equipamento urbano de um determinado cep ou com uma determinada identificação.

Comandos T4:
|  .geo
|    hI <id> <vazao>                          Informa a vazão (l/s) do hidrante id.
|    sI <id> <t>                              Informa o tempo (s) do ciclo do semaforo id.
|    tI <id> <r>                              Informa o raio (m) de alcance da radio-base id.
|  .qry TODO TODO TODO TODO TODO TODO TODO TODO
|    pc? <sufix> [ <x> <y> <larg> <alt> ]     Calcula o polígono de cobertura das rádio-bases da cidade (ou daquelas contidas na
|                                             região retangular). Cria o arquivo nameGeo-nameQry-sufix.svg mostrando a cidade e o polígono de cobertura.
|    ac? [ <x> <y> <larg> <alt> ]             Calcula e imprime no arquivo nameGeo-nameQry.txt a área (m2) do polígono de cobertura das rádio-bases
|

Vars:
|    <n> = 0 - não inserir na QuadTree e deixar na lista.
|          1 - inserir usando envoltório convexo e ordenação.
|          2 - inserir usando envoltório convexo.
|          3 - inserir na ordem que foi inserido na lista.
|    <tipo> = d - diretamente (tira da lista e coloca na qt)
|             c - cria envoltórios convexos e insere na qt
|             o - cria envoltórios convexos, faz ordenações e insere na qt
|    <obj> = q - quadras
|            h - hidrantes
|            s - semaforos
|            t - torres
|            c - circulos e retangulos
|            r - circulos e retangulos

*/

int prepareEnvironment( Args *args ){
	FILE *inFileGeo, *inFileQry, *outFileTxt, *outResumoTxt;
	char *fileQry, *fileGeo, *inDir, *outDir;
	char *fullPathGeo, *fullPathQry, *fullPathTxt, *fullPathResumo;
	char *nameFiles, *nameFileGeo, *nameFileQry;
	int error;

	error = 0;

	inFileQry = NULL;
	outFileTxt = NULL;
	outResumoTxt = NULL;

	fileGeo = getArgsF(args);
	fileQry = getArgsQ(args);
	inDir = fixDir( getArgsE(args) );
	outDir = fixDir( getArgsO(args) );
	nameFileGeo = fileRemovePathExt(fileGeo);
	nameFileQry = fileRemovePathExt(fileQry);
	if( nameFileQry != NULL ){
		nameFiles = createStringCat( 3, nameFileGeo, "-", nameFileQry );
	}
	else{
		nameFiles = createString( nameFileGeo );
	}
	fullPathGeo = createStringCat( 2, inDir, fileGeo );
	fullPathQry = createStringCat( 2, inDir, fileQry );
	fullPathTxt = createStringCat( 3, outDir, nameFiles, ".txt" );
	fullPathResumo = createStringCat( 2, outDir, "resumo.txt" );

	inFileGeo = openFileRead( fullPathGeo );
	if( inFileGeo == NULL ){
		error++;
		goto Return;
	}

	if( getArgsQ(args) != NULL ){
		inFileQry = openFileRead( fullPathQry );
		if( inFileQry == NULL ){
			error++;
			goto Return;
		}
	}

	outFileTxt = openFileWrite( fullPathTxt );
	if( outFileTxt == NULL ){
		error++;
		goto Return;
	}

	if( getArgsAcc(args) == 1 || getArgsAcc0(args) == 1 ){
		if( getArgsAcc(args) == 1 ){
			outResumoTxt = openFileAppend(fullPathResumo);
		}
		else if( getArgsAcc0(args) == 1 ){
			outResumoTxt = openFileWrite(fullPathResumo);
		}
		if( outResumoTxt == NULL ){
			error++;
			goto Return;
		}
	}

	runCommands( args, outDir, nameFileGeo, nameFiles, inFileGeo, inFileQry, outFileTxt, outResumoTxt );

	Return:

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

void runCommands( Args *args, char *outDir, char *nameFileGeo, char *nameFiles, FILE *inFileGeo, FILE *inFileQry, FILE *outFileTxt, FILE *outResumoTxt ){
	char line[1000];
	int method;
	List *objs;
	Cidade *cidade;
	Resumo *res;

	objs = createList();
	cidade = createCidade();
	if( getArgsAcc(args) == 1 || getArgsAcc0(args) == 1 ){
		res = createResumo();
	}
	else{
		res = NULL;
	}
	if( getArgsM(args) == NULL ){
		method = 1;
	}
	else{
		method = atoi(getArgsM(args));
	}

	while( fgets(line,1000,inFileGeo) != NULL ){
		switch( line[0] ){
			case 'c':
				switch( line[1] ){
					case 'q':
					case 'h':
					case 's':
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
				commandCidadeInsert( line, cidade, res, getArgsR(args) );
				break;
			case 'h':
			case 's':
			case 't':
				if( line[1] == ' ' ){
					commandCidadeInsert( line, cidade, res, getArgsR(args) );
				}
				else if( line[1] == 'I' ){
					commandInsertInfo( line, cidade );
				}
				break;
			case 'I':
				dumpPointInfo( cidade, nameFiles, outDir );
				break;
		}
	}

	if( getArgsG(args) != NULL ){
		convexHull( getArgsG(args), 0, objs, cidade, nameFiles, outDir );
	}

	if( getArgsH(args) != NULL ){
		convexHull( getArgsH(args), 1, objs, cidade, nameFiles, outDir );
	}

	if( getArgsI(args) == 1 ){
		dumpPointInfo( cidade, nameFiles, outDir );
	}

	cidadeListToQuadTree( cidade, method );

	if( getArgsQ(args) != NULL ){
		while( fgets(line,1000,inFileQry) != NULL ){
			switch( line[0] ){
				case 'd':
				case 'D':
					commandCidadeDelete( line, cidade, outFileTxt, res, method );
				case 'c':
					if( strncmp( line, "crd?", 4 ) == 0 ){
						commandSearchIdCep( line, cidade, outFileTxt, method );
					}
					break;
				case 'p':
					if( strncmp( line, "pc?", 3 ) == 0 ){
						commandPoligonoCobertura( line, cidade, nameFiles, outDir, method );
					}
				case 'a':
					if( strncmp( line, "ac?", 3 ) == 0 ){
						commandPoligonoCoberturaArea( line, cidade, outFileTxt, method );
					}
			}
		}
	}

	if( getArgsD(args) != NULL ){
		objListToTreeDump( getArgsD(args), method, objs, cidade, nameFiles, outDir );
	}

	createSvg(objs, cidade, nameFiles, outDir, method, getArgsT(args), getArgsNoT2(args));

	destroyObjList(objs);
	destroyCidade(cidade);
	if( getArgsAcc(args) == 1 || getArgsAcc0(args) == 1 ){
		printResumo( res, nameFiles, outResumoTxt );
		destroyResumo(res);
	}
}
