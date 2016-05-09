#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>
#include "compressao.h"
#include "descompressao.h"
//#define LIMPA_TELA system("cls || clear")
//#define ESPERA_TECLA getch()
///#define MOSTRAR_DIRETORIO system("dir || ls")

int main(){
    int opcao = 0;
    char h[999];
    FILE *f = NULL;

    printf("LOCAL ATUAL: ");
 //   MOSTRAR_DIRETORIO;
    printf("DIGITE O ENDERECO DO ARQUIVO: \n");
    scanf("%[^\n]",h);

    f = fopen(h, "r");

    if(f == NULL){
    //    LIMPA_TELA;

    	printf("Arquivo invalido!\n");

    	//   ESPERA_TECLA;
        return -1;
    }

    while( opcao < 1 || opcao > 3 ){
      //  LIMPA_TELA;

    	printf("Arquivo selecionado: %s\n",h);
        printf("1 - COMPRESSAO\n");
        printf("2 - DESCOMPRESSAO\n");
        printf("3 - SAIR\n");
        printf("ESCOLHA UMA OPCAO: ");
        scanf("%d",&opcao);
    }
    if(opcao == 1){

    	compress(f,h);
    //  ESPERA_TECLA;

    }
    else if(opcao == 2){

    	int tam = strlen(h);

    	tam--;

    	//vrifica a extenção do arquivo
       if((h[tam-4]='.')  && (h[tam-3]='h')  && (h[tam-2]=='u') && (h[tam-1]=='f') && (h[tam]=='f')){

    	   printf("\nChamando decompress...");
    	   decompress(f,h);

       }else{
         printf("Arquivo Invalido!\n");
         printf("Selecione um arquivo com a extensao .huff\n");
       }
  //    ESPERA_TECLA;
      return 0;
    }
    else if(opcao == 3){
      return 0;
    }

    fclose(f);

    return 0;
}
