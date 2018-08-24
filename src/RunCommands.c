#include "RunCommands.h"
#include <stdlib.h>
#include <string.h>
#include "Cidade.h"
#include "Object.h"
#include "Circle.h"
#include "Rect.h"
#include "Quadra.h"
#include "Point.h"
#include "String.h"
#include "Tokens.h"
#include "LinkedList.h"
#include "CommandsObjs.h"
#include "CommandsGeo.h"
#include "CommandsEc.h"
#include "CommandsPm.h"
#include "CommandsTm.h"
#include "CommandsVia.h"
#include "CommandsQry.h"
#include "CommandsDebug.h"
#include "CreateSvg.h"
#include "ObjData.h"
#include "File.h"
#include "Resumo.h"
#include "Polygon.h"
#include "Parser.h"

/*
Argumentos fornecidos na linha de comando:
|    -acc0              Cria resumo.txt
|    -acc               Abre resumo.txt para append
|    -e <path>          Diretório com arquivos de entrada
|    -o <path>          Diretório de saida de arquivos
|    -f <arq.geo>       Arquivo de entrada com elementos a serem inseridos
|    -q <arq.qry>       Arquivo de entrada com testes a serem feitos
|	 -ec <arq.ec>		Arquivo dos estabelecimentos comerciais
|	 -pm <arq.pm>		Arquivo das pessoas e moradores
|	 -tm <arq.tm>		Arquivo dos clientes de telefonia móvel
|	 -v <arq.via>		Arquivos das vias
|    -id                Imprime nome e matrícula na saída padrão
|    -m <method>	    Chama listToQt() com method definido.
|	 -t 				Gera svg com raio de cobertura das torres.
|	 -noT2				Não coloca objetos do T2 na saiva svg.
|	 -r <raio>			Raio de cobertura padrão para as torres.
|	 -g <obj>			Gera <nameGeo>-<nameQry>-convexhull.{svg,txt} com os envoltórios convexos dos objetos
|	 -h <obj>			Gera <nameGeo>-<nameQry>-convexhullcollinear.{svg,txt} com os envoltórios convexos com colineares dos objetos
|	 -od <path>			Dumpa dados em path
|	 -n <obj>,<x>,<y>	Cria nearest.svg mostrando o ponto mais próximo a (x,y).

Comandos Objs:
|	c <i> <r> <x> <y> <fill>       Cria um círculo
|	r <i> <w> <h> <x> <y> <fill>   Cria um retangulo
|	o <j> <k>                      Verifica se as formas com ids j e k se sobrepoem (saidas colocadas em arg.txt)
|	i <j> <x> <y>                  Verifica se o ponto (x,y) está dentro da forma com id j (saidas colocadas em arg.txt)
|	d <j> <k>                      Verifica a distancia entre os centros das formas com ids j e k (saidas colocadas em arg.txt)
|	a <sufix> <fill>			   Cria um arquivo svg, mostrando apenas os
|	                               centros dos círculos e os cantos dos
|	                               retângulos criados pelos comandos c e r.

Comandos Geo:
|	q <x> <y> <larg> <alt> <cep>    Insere uma quadra (retângulo e cep)
|	h <x> <y> <id>                  Insere um hidrante
|	s <x> <y> <id>                  Insere um semáforo
|	t <x> <y> <id>                  Insere uma rádio-base (torre de celular)
|	cq <cfill> <cstrk>              Cores do preenchimento e da borda das quadras (a partir deste comando)
|	ch <cfill> <cstrk>              Cores do preenchimento e da borda dos hidrantes (a partir deste comando)
|	ct <cfill> <cstrk>              Cores do preenchimento e da borda das torres de celular (a partir deste comando)
|	cs <cfill> <cstrk>              Cores do preenchimento e da borda dos semáforos (a partir deste comando)
|	hI <id> <vazao>                 Informa a vazão (l/s) do hidrante id.
|	sI <id> <t>                     Informa o tempo (s) do ciclo do semaforo id.
|	tI <id> <r>                     Informa o raio (m) de alcance da radio-base id.
|	su <id>							Informa que torre de celular de identificação id pertence à operadora SercomtUEL
|	um <id>							Informa que torre de celular de identificação id pertence à operadora UELMobile

Comandos Ec:
|	t <codt> <descricao>						Define tipo de estabelecimento comercial.
|	e <codt> <cep> <face> <num> <cnpj> <nome>	Insere um novo estabelecimento comercial.
|	d <cnpj>									*Remove estabelecimento da cidade.

Comandos Pm:
|	p <cpf> <nome> <sobrenome> <sexo> <nasc>	Insere pessoa na cidade.
|	m <cpf> <cep> <face> <num> <compl>			Define onde a pessoa mora.

Comandos Tm:
|	su <cpf> <numcel>		Cpf é cliente de SercomtUEL.
|	um <cpf> <numcel>		Cpf é cliente de UELMobile.

Comandos Via:
|	v <id> <x> <y>									Insere vertice.
|	e <i> <j> <ldir> <lesq> <cmp> <vm> <nome>		Insere rua/aresta.

Comandos Qry (saidas colocadas em nameGeo-nameQry.txt):
|	dq <region>				           			Remove todas quadras que estiverem inteiramente dentro do retângulo.
|	dh <region>				           			Semelhante ao dq. Remove os hidrantes dentro da região.
|	ds <region>				           			Semelhante dq. Remove os semáforos da região.
|	dt <region>				           			Semelhante dq. Remove as torres de celular dentro da região.
|	Dq <x> <y> <raio>                 			Remove todas as quadras que estiverem inteiramente contidas dentro do círculo.
|	Dh <x> <y> <raio>                 			Semelhante a Dq. Remove os hidrantes dentro da região.
|	Ds <x> <y> <raio>                 			Semelhante a Dq. Remove os semáforos dentro da região.
|	Dt <x> <y> <raio>                 			Semelhante a Dq. Remove as torres de celular dentro da região.
|	crd? <cep|id>                     			Imprime no arquivo .txt as coordenadas e a espécie do equipamento urbano de um determinado cep ou com uma determinada identificação.
|	pc? <sufix> [<region>] 				    	Calcula o polígono de cobertura das rádio-bases da cidade (ou daquelas contidas na
|                                        		região retangular). Cria o arquivo nameGeo-nameQry-sufix.svg mostrando a cidade e o polígono de cobertura.
|	ac? [<region>] 				            	Calcula e imprime no arquivo nameGeo-nameQry.txt a área (m2) do polígono de cobertura das rádio-bases
|	mv <opdest> <num>							Move celular de uma operadora pra outra (ver pdf p/ mais detalhes)
|	m? <cep>									Mostra moradores da quadras
|	mr? <region>								Mostra moradores das quadras de dentro da regiao
|	dm? <cpf>									Imprime dados do moradores
|	de? <cnpj>									Dados do estabelecimento
|	con <numcel> <cep> <face> <num>				Conecta celular que está no dado endereco
|	mse? <sx> <tp> <region>						Complexo, ver pdf
|	rip <cpf>									Matar pessoa
|	lk? <id>									Celular conectados a torre
|	rb? <numcel>								Torre que o celular está conectado
|	co? (su|um) [<n>]							Mostra em ordem, o numero e nome dos clientes da operadora, mostra até n clientes
|	lnr? <region> [(su|um)]						Lista celular conectados as torres da regiao, mostra apenas da operadora data se especificado
|	ecp? <cep>									Lista estabelecimentos de uma quadra
|	ecr? <tp> [<region>]						Lista os estabelecimentos de um tipo, e de um regiao se presente
|	tecq? <cep>									Lista os tipos de estabelecimentos de uma quadra
|	tecr? <region>								Tipos de estabelecimentos de uma região
|	dc? <num>									Usuário do celular
|	lec? <num>									Endereco onde o celular esta
|	lcc? <num>									Coordenadas onde o celular esta
|	dpr <region>								Apaga tudo da região
|	@f? <r> <fone>								Armazena endereco de fone
|	@m? <r> <cpf>								Armazena endereco de cpf
|	@e? <r> <cep> <face> <num>					Armazena endereco fornecido
|	@g? <r> <id>								Armazena posicao do equipamento urbano
|	@xy[?] <r> <x> <y>							Armazena a coordenada
|	@tp? <r1> <tp> <r2>							Armazena em r1 o estabelecimento comercial de tipo tp mais próximo da posição armazenada em r2
|	p? (t|p <sufixo>) (D|T) <r1> <r2> [<cor>]	Calcula melhor trajeto
|		t = descrição textual
|		p = descrição pictórica
|		D = menor distância
|		T = menor tempo estimado

Vars:
|    <method> = 1 - inserir usando envoltório convexo e ordenação.
|               2 - inserir usando envoltório convexo.
|               3 - inserir na ordem que foi inserido na lista.
|    <obj> = q - quadras
|            h - hidrantes
|            s - semaforos
|            t - torres
|            c - circulos e retangulos
|            r - circulos e retangulos
|			 v - vertices
|	<region> = <x> <y> <larg> <alt> - Define uma regiao retangular

*/

struct _fileStuff{
	FILE *inFileGeo, *inFileEc, *inFilePm, *inFileTm, *inFileVia, *inFileQry, *outFileTxt, *outResumoTxt;
	char *fileGeo, *fileEc, *filePm, *fileTm, *fileVia, *fileQry;
	char *inDir, *outDir;
	char *nameFiles, *nameFileGeo, *nameFileQry;
	char *fullPathGeo, *fullPathEc, *fullPathPm, *fullPathTm, *fullPathVia, *fullPathQry, *fullPathTxt, *fullPathResumo;
};

int prepareEnvironment( Args *args ){
	int error;
	FileStuff stuff;

	error = 0;

	stuff.inFileGeo = NULL;
	stuff.inFileEc = NULL;
	stuff.inFilePm = NULL;
	stuff.inFileTm = NULL;
	stuff.inFileVia = NULL;
	stuff.inFileQry = NULL;
	stuff.outFileTxt = NULL;
	stuff.outResumoTxt = NULL;

	stuff.fileGeo = args->f;
	stuff.fileEc = args->ec;
	stuff.filePm = args->pm;
	stuff.fileTm = args->tm;
	stuff.fileVia = args->v;
	stuff.fileQry = args->q;

	stuff.inDir = fixDir( args->e );
	stuff.outDir = fixDir( args->o );

	stuff.nameFileGeo = fileRemovePathExt(stuff.fileGeo);
	stuff.nameFileQry = fileRemovePathExt(stuff.fileQry);
	if( stuff.nameFileQry != NULL ){
		stuff.nameFiles = createStringCat( 3, stuff.nameFileGeo, "-", stuff.nameFileQry );
	}
	else{
		stuff.nameFiles = createString( stuff.nameFileGeo );
	}

	stuff.fullPathGeo = createStringCat( 2, stuff.inDir, stuff.fileGeo );
	stuff.fullPathEc = createStringCat( 2, stuff.inDir, stuff.fileEc );
	stuff.fullPathPm = createStringCat( 2, stuff.inDir, stuff.filePm );
	stuff.fullPathTm = createStringCat( 2, stuff.inDir, stuff.fileTm );
	stuff.fullPathVia = createStringCat( 2, stuff.inDir, stuff.fileVia );
	stuff.fullPathQry = createStringCat( 2, stuff.inDir, stuff.fileQry );
	stuff.fullPathTxt = createStringCat( 3, stuff.outDir, stuff.nameFiles, ".txt" );
	stuff.fullPathResumo = createStringCat( 2, stuff.outDir, "resumo.txt" );

	stuff.inFileGeo = openFileRead( stuff.fullPathGeo );
	if( stuff.inFileGeo == NULL ){
		error++;
	}

	if( error == 0 ){
		if( args->ec != NULL ){
			stuff.inFileEc = openFileRead( stuff.fullPathEc );
			if( stuff.inFileEc == NULL ){
				error++;
			}
		}
	}

	if( error == 0 ){
		if( args->pm != NULL ){
			stuff.inFilePm = openFileRead( stuff.fullPathPm );
			if( stuff.inFilePm == NULL ){
				error++;
			}
		}
	}

	if( error == 0 ){
		if( args->tm != NULL ){
			stuff.inFileTm = openFileRead( stuff.fullPathTm );
			if( stuff.inFileTm == NULL ){
				error++;
			}
		}
	}

	if( error == 0 ){
		if( args->v != NULL ){
			stuff.inFileVia = openFileRead( stuff.fullPathVia );
			if(!stuff.inFileVia){
				error++;
			}
		}
	}

	if( error == 0 ){
		if( args->q != NULL ){
			stuff.inFileQry = openFileRead( stuff.fullPathQry );
			if( stuff.inFileQry == NULL ){
				error++;
			}
		}
	}

	if( error == 0 ){
		stuff.outFileTxt = openFileWrite( stuff.fullPathTxt );
		if( stuff.outFileTxt == NULL ){
			error++;
		}
	}

	if( error == 0 ){
		if( args->acc == 1 || args->acc0 == 1 ){
			if( args->acc == 1 ){
				stuff.outResumoTxt = openFileAppend(stuff.fullPathResumo);
			}
			else if( args->acc0 == 1 ){
				stuff.outResumoTxt = openFileWrite(stuff.fullPathResumo);
			}
			if( stuff.outResumoTxt == NULL ){
				error++;
			}
		}
	}

	if( error == 0 ){
		runCommands( args, stuff );
	}

	closeFile(stuff.inFileGeo);
	closeFile(stuff.inFileQry);
	closeFile(stuff.inFileEc);
	closeFile(stuff.inFilePm);
	closeFile(stuff.inFileTm);
	closeFile(stuff.inFileVia);
	closeFile(stuff.outFileTxt);
	closeFile(stuff.outResumoTxt);

	destroyString(stuff.inDir);
	destroyString(stuff.outDir);
	destroyString(stuff.nameFileGeo);
	destroyString(stuff.nameFileQry);
	destroyString(stuff.nameFiles);
	destroyString(stuff.fullPathGeo);
	destroyString(stuff.fullPathEc);
	destroyString(stuff.fullPathPm);
	destroyString(stuff.fullPathTm);
	destroyString(stuff.fullPathVia);
	destroyString(stuff.fullPathQry);
	destroyString(stuff.fullPathTxt);
	destroyString(stuff.fullPathResumo);

	if( error != 0 ){
		return 1;
	}
	return 0;
}

void runCommands( Args *args, FileStuff stuff ){
	int method;
	List *objs;
	Cidade *cidade;
	Resumo *res;

	if( args->acc == 1 || args->acc0 == 1 ){
		res = createResumo();
	}
	else{
		res = NULL;
	}
	if( args->m == NULL ){
		method = 1;
	}
	else{
		method = atoi(args->m);
	}

	objs = createList();
	cidade = createCidade("Bitnópolis", method);

	runCommandsGeo( objs, cidade, args, stuff, res );

	if( args->ec != NULL ){
		runCommandsEc( cidade, stuff );
	}

	if( args->pm != NULL ){
		runCommandsPm( cidade, stuff );
	}

	if( args->tm != NULL ){
		runCommandsTm( cidade, stuff );
	}

	if( args->v != NULL ){
		runCommandsVia(cidade, stuff);
	}

	if( args->g != NULL ){
		convexHull( args->g, 0, objs, cidade, stuff.nameFiles, stuff.outDir );
	}
	if( args->h != NULL ){
		convexHull( args->h, 1, objs, cidade, stuff.nameFiles, stuff.outDir );
	}

	cidadeFillDataStructures( cidade );

	if( args->q != NULL ){
		runCommandsQry( cidade, stuff, res );
	}

	createSvg(objs, cidade, stuff.nameFiles, stuff.outDir, args->t, args->noT2);

	if( args->n != NULL ){
		nearestPoint( args->n, cidade, stuff.outDir );
	}

	if( args->od != NULL ){
		dumpData( objs, cidade, args->od );
	}

	setListFuncDestroyData(objs, destroyObjDataVoid);
	destroyList(objs);
	destroyCidade(cidade);
	if( args->acc == 1 || args->acc0 == 1 ){
		printResumo( res, stuff.nameFiles, stuff.outResumoTxt );
		destroyResumo(res);
	}
}

void runCommandsGeo( List *objs, Cidade *cidade, Args *args, FileStuff stuff, Resumo *res ){
	char line[STRING_SIZE_LARGE];
	int commandId;
	Tokens *tokens;

	tokens = createTokens(DELIMITERS);

	while( fgets(line,STRING_SIZE_LARGE,stuff.inFileGeo) != NULL ){
		defineTokens( tokens, line );
		commandId = parserGeo( getToken(tokens, 0) );
		switch( commandId ){
			case 1: /* c */
			case 2: /* r */
				commandInsertObjs(line, objs);
				break;
			case 3: /* o */
				procO( line, objs, stuff.outFileTxt );
				break;
			case 4: /* i */
				procI( line, objs, stuff.outFileTxt );
				break;
			case 5: /* d */
				procD( line, objs, stuff.outFileTxt );
				break;
			case 6: /* a */
				procA( line, objs, stuff.nameFileGeo, stuff.outDir );
				break;
			case 7: /* q */
			case 8: /* h */
			case 9: /* s */
			case 10: /* t */
				commandCidadeInsert( line, cidade, res, args->r );
				break;
			case 11: /* cq */
			case 12: /* ch */
			case 13: /* cs */
			case 14: /* ct */
				commandCidadeColors(line, cidade);
				break;
			case 15: /* hI */
			case 16: /* sI */
			case 17: /* tI */
				commandInsertInfo( line, cidade );
				break;
			case 18: /* su */
			case 19: /* um */
				commandSetTorreOwner( line, cidade );
				break;
			default:
				break;
		}
	}

	destroyTokens(tokens);
}

void runCommandsEc( Cidade *cidade, FileStuff stuff ){
	char line[STRING_SIZE_LARGE];
	int commandId;
	Tokens *tokens;

	tokens = createTokens(DELIMITERS);

	while( fgets(line,STRING_SIZE_LARGE,stuff.inFileEc) != NULL ){
		defineTokens( tokens, line );
		commandId = parserEc( getToken(tokens, 0) );
		switch( commandId ){
			case 1: /* t */
				commandDescricao( cidade, line );
				break;
			case 2: /* e */
				commandInsertEstabComercial( cidade, line );
				break;
			case 3: /* d */
				commandRemoveEstabComercial( cidade, line );
				break;
			default:
				break;
		}
	}

	destroyTokens(tokens);
}

void runCommandsPm( Cidade *cidade, FileStuff stuff ){
	char line[STRING_SIZE_LARGE];
	int commandId;
	Tokens *tokens;

	tokens = createTokens(DELIMITERS);

	while( fgets(line,STRING_SIZE_LARGE,stuff.inFilePm) != NULL ){
		defineTokens( tokens, line );
		commandId = parserPm( getToken(tokens, 0) );
		switch( commandId ){
			case 1: /* p */
				commandInsertPessoa( cidade, line );
				break;
			case 2: /* m */
				commandMorador( cidade, line );
				break;
			default:
				break;
		}
	}

	destroyTokens(tokens);
}

void runCommandsTm( Cidade *cidade, FileStuff stuff ){
	char line[STRING_SIZE_LARGE];
	int commandId;
	Tokens *tokens;

	tokens = createTokens(DELIMITERS);

	while( fgets(line,STRING_SIZE_LARGE,stuff.inFileTm) != NULL ){
		defineTokens( tokens, line );
		commandId = parserTm( getToken(tokens, 0) );
		switch( commandId ){
			case 1: /* su */
			case 2: /* um */
				commandInsertClienteOperadora(line, commandId, cidade);
				break;
			default:
				break;
		}
	}

	destroyTokens(tokens);
}

void runCommandsVia( Cidade *cidade, FileStuff stuff ){
	char line[STRING_SIZE_LARGE];
	int commandId;
	Tokens *tokens;

	tokens = createTokens(DELIMITERS);

	while( fgets(line,STRING_SIZE_LARGE,stuff.inFileVia) != NULL ){
		defineTokens( tokens, line );
		commandId = parserVia( getToken(tokens, 0) );
		switch( commandId ){
			case 1: /* v */
				commandInsertVertice(line, cidade);
				break;
			case 2: /* e */
				commandInsertRua(line, cidade);
				break;
			default:
				break;
		}
	}

	destroyTokens(tokens);
}

void runCommandsQry( Cidade *cidade, FileStuff stuff, Resumo *res ){
	char line[STRING_SIZE_LARGE];
	int commandId;
	Tokens *tokens;

	tokens = createTokens(DELIMITERS);

	while( fgets(line,STRING_SIZE_LARGE,stuff.inFileQry) != NULL ){
		defineTokens( tokens, line );
		commandId = parserQry( getToken(tokens, 0) );
		switch( commandId ){
			case 1: /* dq */
			case 2: /* dh */
			case 3: /* ds */
			case 4: /* dt */
			case 5: /* Dq */
			case 6: /* Dh */
			case 7: /* Ds */
			case 8: /* Dt */
				commandCidadeDelete( line, cidade, stuff.outFileTxt, res );
				break;
			case 9: /* crd? */
				commandSearchIdCep( line, cidade, stuff.outFileTxt );
				break;
			case 10: /* pc? */
				commandPoligonoCobertura( line, cidade, stuff.nameFiles, stuff.outDir );
				break;
			case 11: /* ac? */
				commandPoligonoCoberturaArea( line, cidade, stuff.outFileTxt );
				break;
			case 12: /* mv */
				commandMoveCelular( line, cidade, stuff.outFileTxt );
				break;
			case 13: /* m? */
			case 14: /* mr? */
				commandListaMoradoresQuadra( line, commandId, cidade, stuff.outFileTxt );
				break;
			case 15: /* dm? */
				commandDumpDadosMorador( line, cidade, stuff.outFileTxt );
				break;
			case 16: /* de? */
				commandDumpDadosEstabComercial( line, cidade, stuff.outFileTxt );
				break;
			case 17: /* con */
				commandConectaCelular( line, cidade, stuff.outFileTxt );
				break;
			case 18: /* mse? */
				commandDumpMoradoresSexoCodtRegion( line, cidade, stuff.outFileTxt );
				break;
			case 19: /* rip */
				commandMatarPessoa( line, cidade, stuff.outFileTxt );
				break;
			case 20: /* lk? */
				commandDumpConexoesTorre( line, cidade, stuff.outFileTxt );
				break;
			case 21: /* rb? */
				commandTorreCelularConectado( line, cidade, stuff.outFileTxt );
				break;
			case 22: /* co? */
				commandListaClientesOperadora( line, cidade, stuff.outFileTxt );
				break;
			case 23: /* lnr? */
				commandListaConexoesTorresRegion( line, cidade, stuff.outFileTxt );
				break;
			case 24: /* ecq? */
				commandListaEstabComerciaisQuadra( line, cidade, stuff.outFileTxt );
				break;
			case 25: /* ecr? */
				commandListaEstabComerciaisTipoRegion( line, cidade, stuff.outFileTxt );
				break;
			case 26: /* tecq? */
				commandListaTiposCep( line, cidade, stuff.outFileTxt );
				break;
			case 27: /* tecr? */
				commandListaTiposRegion( line, cidade, stuff.outFileTxt );
				break;
			case 28: /* dc? */
			case 29: /* lec? */
			case 30: /* lcc? */
				commandDadosUsuarioLinhaMovel( line, commandId, cidade, stuff.outFileTxt );
				break;
			case 31: /* dpr */
				commandLimpaRegion( line, cidade, stuff.outFileTxt );
				break;
			case 32: /* @f? */
			case 33: /* @m? */
			case 34: /* @e? */
			case 35: /* @g? */
			case 36: /* @xy[?] */
			case 37: /* @tp? */
				commandRegistrador(line, commandId, cidade, stuff.outFileTxt);
				break;
			case 38: /* p? */
				commandDijkstra(line, tokens, cidade, stuff.outFileTxt, stuff.nameFileGeo, stuff.outDir );
				break;
			default:
				break;
		}
	}

	destroyTokens(tokens);
}
