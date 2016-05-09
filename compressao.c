#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "freq_w.h"
#include "compressao.h"
#include "adt.h"
#include "bitop.h"

#define INFO if(1)

#define DEBUG 1

void compress(FILE *f,  char *h){

    setlocale(LC_ALL,"");

    /*
     * ---------------- declaracoes --------------------
     */

    pnode *huff; //Lista

    char **hash; //Tabela Hash - guardara os simbolos

    int *freq; //Frequencia - ponteiro de inteiros

	int qt, trash; // Tamanho da arvore e Tamanho do lixo

	/*
	 *  ------------- fim declaracoes ------------------
	 */


	/*
	 *  ------------ frequencia de caracteres -------------
	 */

	INFO printf("\nGerando frequencia de caracteres.....\n");

	freq = freq_w(f); // Frequencia - retorna um ponteiro de inteiros

    huff = startpnode(); // Inicializa a Lista com NULL

    huff = plista(freq); // Passa a frequencia para a lista

    /*
     *  ------------- fim frequencia ---------------------
     */

    INFO printf("\nConstrucao da arvore de huffman.....\n");

    /*
     * ----------- construcao da arvore e tabela ------------
     */

    huff = makeHtree(huff); // Cria a arvore de huffman

    qt = qtnodes(huff); //Tamanho da arvore

    hash = hasharvore(huff); //Tabela HASH

    /*
     * ------------------ fim construcao arvore e tabela -------------------
     */




    trash = getTrash(f, hash); //Recebe o tamanho do lixo


    //escreve todas as informacoes no arquivo compactado
    writeOutputfile(trash, qt, huff, hash, f, h);

    INFO printf("\nNome do arquivo comprimido: %s\n", h);

}
