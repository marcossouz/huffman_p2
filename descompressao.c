#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include "compressao.h"
#include "adt.h"
#include "bitop.h"

#define DEBUG 1

void decompress(FILE *f,  char *h){
    setlocale(LC_ALL,"");

    //Tamanho do Lixo
    int trash;
    
	//Tamanho da  arvore
    int sizeTree, savesizeTree;
  
 	//Para Obter a arvore do arquivo
    pnode *huff;
    
	//Um novo arquivo com o nome e a extenção original
    FILE *writeoutput; //descompactado
    FILE *fbin;

    fbin = fopen(h,"rb");

    //Remove a extenção .huff
    h[strlen(h) - 5] = '\0';
    
	//Cria um novo arquivo com o nome e a extenção original
    writeoutput = fopen(h,"w");
    
	//Fecha o arquivo
    //fclose(Writeoutput);
    
	//Abre o arquivo para se modificado
   // Writeoutput = fopen(h,"r+");
    
	// Inicializa a Lista
    huff = startpnode();
    
    printf("\ngivemethetrash...");
	//Recebe o tamanho do lixo
	trash = givemethetrash(f);
    printf("\nreturn trash....");

    printf("\ngivemethesizeTree...");
	//Recebe o tamanho da arvore
    sizeTree = givemethesizeTree(f);
    printf("\nreturn sizeTree....\n");

    
	//Tamanho original da arvore
    savesizeTree = sizeTree;
    
	//Obtem a arvore do arquivo
    huff = givemeHtree(f,&sizeTree);

	//INICIA A DESCOMPRESSAO DO ARQUIVO
    makedecompressOutputfile(fbin, writeoutput, huff, trash, savesizeTree);


    if(DEBUG){
        printf("TRASH: %d\n",trash);
        printf("SIZETREE: %d\n",savesizeTree);
        printHtree(huff);
        printf("\n");
        //makeallchars();
    }
    printf("FIM DA DESCOMPRESSAO!\n");
}
