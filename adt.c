#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "adt.h"
#include "compressao.h"
#include "bitop.h"

#define INFO if(1)

//STRUCTS
struct node{
    int v;
    unsigned char c;
    node *nextnode;
};

struct pnode{
    int v;
    unsigned char c;
    pnode *nextpnode;
    pnode *left;
    pnode *right;
};
//EndSTRUCTS

//FUNCTIONS
//NODE

// INICIA UMA VARIAVEL DO TIPO NODE
node *createnode(){
    return NULL;
}

//VERIFICA SE UMA VARIAVEL DO TIPO NODE EH VAZIA
int isEmpty(node *first){
    return (first == NULL);
}

// INSERE UMA VARIAVEL DO TIPO NODE EM UMA LISTA DE NODES
node *insertnode( node *first, int value, unsigned char character ){
    node *newnode = (node*)malloc(sizeof(node));
    newnode -> v = value;
    newnode -> c = character;
    newnode -> nextnode = first;
    return newnode;
}

//IMPRIME UMA LISTA DO TIPO NODE
void printlist(node *first){
    if(!isEmpty(first)){
        //printf("Letra %c com frequencia %d\n", first -> c, first -> v);
        printf("%d",first -> v);
        printlist(first -> nextnode);
    }
}
//EndNODE

//PNODE
//INICIA UMA VARIAVEL DO TIPO PNODE
pnode *startpnode(){
    return NULL;
}

//VERIFICA SE O ELEMENTO DO TIPO PNODE EH VAZIO
int ispEmpty(pnode *first){
    return (first == NULL);
}

//CRIA UMA VARIAVEL DO TIPO PNODE
pnode *createpnode(int value, char character, pnode *left, pnode *right){

	pnode *aux;
    aux = (pnode*)malloc(sizeof(pnode));
    aux -> v = value;
    aux -> c = character;
    aux -> left = left;
    aux -> right = right;
    aux -> nextpnode = NULL;

    return aux;
}

//INSERE UM PNODE EM UMA FILA DE PRIORIDADE
pnode *insertpnode(pnode *first, pnode *insert){
    if(ispEmpty(first) || insert -> v <= first -> v){
        insert -> nextpnode = first;
        return insert;
    }
    else{
        first -> nextpnode = insertpnode(first -> nextpnode, insert);
        return first;
    }
}

//CALCULA A ALTURA DE UMA ARVORE DO TIPO PNODE
int h_tree(pnode *root){
    if (ispEmpty(root)){
       return -1;
    }
    else{
        int h;
        int hleft;
        int hright;

        hleft = h_tree(root->left);
        hright = h_tree(root->right);
        h = hleft + 1;
        if (hleft < hright){
            h = hright + 1;
        }
        return h;
    }
}

//CRIA UMA LISTA DE PRIORIDADE DO TIPO PNODE A PARTIR DE UMA LISTA DO TIPO INT
pnode* plista(int *p){

	int i;
    pnode *pn;
    pnode *aux;

    pn = startpnode();
    aux = startpnode();

    for( i = 0; i <= 255; i++){
        if(p[i] != 0){
            aux = createpnode(p[i], i, NULL, NULL); //criando o noh tipo node com a frequencia correspondente
            pn = insertpnode(pn, aux); //agora inserindo esse noh em uma listade prioridade com nós..
        }
    }
    return pn;
}

//EndPNODE
//HUFFMAN_TREE:
//CRIA UMA ARVORE DE HUFFMAN(RECURSIVA)
pnode *makeHtree(pnode *first){

	if(!ispEmpty(first)){

		int value;
        pnode *root;
        root = startpnode();

        if(!ispEmpty(first -> nextpnode)){
            value = (first -> v) + (first -> nextpnode -> v);
            root = createpnode( value, '*', first, first -> nextpnode);
            first = insertpnode(first -> nextpnode -> nextpnode, root);
            first = makeHtree(first);
        }
        else if(h_tree(first) == 0){
            value = first -> v;
            first = createpnode( value, '*', first, first -> nextpnode);
        }
    }
    return first;
}

//VERIFICA SE O NO DA ARVORE EH UMA FOLHA
int isLeaf(pnode *root){
    return (ispEmpty(root -> left) && ispEmpty(root -> right));
}

//IMPRIME NA TELA UMA ARVORE(RECURSIVA)
void printHtree(pnode *root){
    if(!ispEmpty(root)){
        printf("%c",root -> c);
        printHtree(root -> left);
        printHtree(root -> right);
    }
}

// CALCULA A QUANTIDADE DE ELEMENTOS QUE TEM NA ARVORE
int qtnodes(pnode *root){
    int qt = 0;
    if(!ispEmpty(root)){
        qt = 1;
        qt += qtnodes(root -> left) + qtnodes(root -> right);
    }
    return qt;
}

//EndHUFFMAN_TREE
//HUFFMAN_HASH

//ADICIONA O CAMINHO DA FOLHA NA HASHTABLE
void hashvalue(pnode* first, int posi,char **h,char *bitschar){

	if(!ispEmpty(first)){

        if((first->left==NULL )&& (first->right==NULL)){

        	int i, local;

        	local = first->c;

            for(i = 0 ; i < posi; i++){
                h[local][i] = bitschar[i];
            }
         h[local][posi]='\0';
         INFO printf("\n%c: %s", local, h[local] );

        }else{

            int lef = posi;
            bitschar[lef]='0';
            lef++;
            hashvalue(first->left, lef, h , bitschar);

            int rig = posi;
            bitschar[rig]='1';
            rig++;
            hashvalue(first->right, rig, h , bitschar);
         }
    }
}

//CRIA UMA HASHTABLE COM OS CAMINHOS DE SUAS RESPECTIVAS FOLHAS
char **hasharvore(pnode* first){

	int posi=0, i;
    char *bitschar;
    char **has;

    bitschar = (char*)malloc(256*sizeof(char)); //ponteiro que vai armazenando o caminho ate a folha
    pnode* no = first;

    has = (char**)malloc(256*sizeof(char*)); //Aloco memoria para a has

    for(i=0;i<256;i++){
        has[i] = (char*)malloc(256*sizeof(char)); //matriz de ponteiros toda alocada
    }

    hashvalue(no, posi, has, bitschar);
    return has;
}

//EndHUFFMAN_HASH
//CALCULA O LIXO
int getTrash(FILE* input, char **hash){

	int trash;
	int sizeBits = 0;
	unsigned char c;

	rewind(input);

	while(!feof(input))
	{
		c = fgetc(input);

		sizeBits += strlen(hash[c]); //conta todos os bits do texto
	}
		INFO printf("\n\nsizeBits: %d", sizeBits);

		trash = 8 - (sizeBits%8);

		if(trash == 8) trash = 0; //caso de nao haver resto

	return trash;
}


//Escreve os 2 primeiros bytes no arquivo comprimido
void putTwoFirstBytes(FILE *out, int trash, int qt){

    unsigned char firstByte;
    unsigned char secondByte;
    int auxqt = 0;
    /*
     * Inicializa os primeiros Bytes.
    */
    firstByte = 0;
    secondByte = 0;

    /*
     * O primeiro byte recebe o trash deslocado para a esquerda 5 vezes.
    */

    firstByte = firstByte | (trash << 5);
    auxqt = qt;

    /*
     * O primeiro byte recebe o qt deslocado para a direita 8 vezes.
     * com isso o primeiro byte fica completo.
     * Foi preenchido os bits 7, 6 e 5 no primeiro deslocamento
     * e no segundo os bits 4, 3, 2, 1, 0.
     * Totalizando 8 bits.
    */
    auxqt = auxqt >> 8;
    firstByte = firstByte | (auxqt);

    /*
     * O qt tem o seu tamanho reduzido, pois ja foi colocado no primeiro byte uma parte
     * de seu conteudo.
    */

    auxqt = auxqt << 8;
    qt = qt - auxqt;

    /*
     * O segundo byte recebe o que sobrou do qt.
    */

    secondByte = secondByte | qt;

    /*
     * Agora so resta imprimir no arquivo os dois bytes.
    */

    fputc(firstByte,out);
    fputc(secondByte,out);

}

//Escreve a arvore no arquivo de saida
void writeTree(pnode *huff, FILE *out)
{
	if(huff != NULL)
	{
		if(isLeaf(huff) && (huff->c == '*' || huff->c == '\\'))
		{
			fputc('\\', out);
			INFO printf("%c", '\\');
		}

		fputc(huff->c, out);

		INFO printf("%c", huff->c);

		writeTree(huff->left, out);
		writeTree(huff->right, out);
	}
}

void writeFileOut(FILE *input, FILE *outfile, char **hash)
{
	rewind(input);
	unsigned char ch, chOut[256] = "", ctemp[256], c[9];
	int cont=0;
	int k= 0, j, i = -1;

	INFO printf("\n\nCombinacao de bits em bytes.....");
	/*
	 * No primeiro While, a variavel chOut sai com o resto dos bits...
	 * 
	*/
	while(!feof(input))
		{
			ch = fgetc(input);
			cont += strlen(hash[ch]); //conta todos os bits do texto
			//printf("\ncont: %d", cont);


			strcat(chOut, hash[ch]);
			//printf("\n%s ", chOut);


			if(cont > 7)
			{
				//SALVANDO O RESTO DE BITS EM CTEMP E DEPOIS EM chOut
				k=0;
				for(j = 0; j <= 7; j++)
				{
					c[j] = chOut[j];
				}
				c[j]='\0';
				while(chOut[j] != '\0')
				{
					ctemp[k] = chOut[j];
					j++;
					k++;
					//printf("\nctemp: %s", ctemp);
				}
				ctemp[k] = '\0';
				strcpy(chOut, ctemp);
				//RESTO DO chOut salvo.

		//INFO printf("\n%s", c);

				cont -= 8;
				//printf("\nzera");

				ch = 0;
				for (i = 0, j = 7; i <= 7; i++, j--) {

					if(c[i]  == '1') ch = setBit(ch, j);
				}
				fputc(ch, outfile);

			//	strcpy(chOut, ctemp);
			}

		}

	INFO printf("\nrestaram: %d", cont);
	INFO printf(" -> %s", chOut);
	INFO printf("\n\nEscrevendo ultimo simbolo.....");

	//escrevendo ultimo byte(bits que ficaram salvo em chOut)
	if(cont > 0)
	{
		for(i = 0; i <= (cont); i++)
		{
			c[i] = chOut[i];
		}

		for( ; i <= 7; i++) c[i] = '0'; //escrevendo o lixo

		ch = 0;
		for (i = 0, j = 7; i <= 7; i++, j--) {

			if(c[i]  == '1') ch = setBit(ch, j);
		}
		fputc(ch, outfile);


	}


		INFO printf("\n\nCOMPRESSAO FINALIZADA COM SUCESSO...\n\n");

}

/*
 *  @param trash - valor do lixo
 *  @param qt - tamanho da arvore
 *  @param huff - arvore de huffman
 *  @param hash - tabela com a codificação
 *  @param input - arquivo principal
 *  @param file_name - nome do arquivo principal
 */
void writeOutputfile(int trash, int qt, pnode *huff, char **hash, FILE *input, char *file_name)
{
	strcat(file_name, ".huff");
    FILE *outfile = fopen(file_name, "w");

	//escreve os 2 primeiros bytes
	putTwoFirstBytes(outfile, trash, qt);

	//escreve a arvore
	INFO printf("\n\n");
	writeTree(huff, outfile);

	//escreve o arquivo compactado
	writeFileOut(input, outfile, hash);

	fclose(outfile);
}
//DESCOMPRESS

//Retorna o tamanho do lixo
int givemethetrash(FILE *f){
    
	int i, ch = 0, trash = 0;
    //fseek(f,0,SEEK_SET);
    ch = fgetc(f);
    
	for(i = 5; i <= 7; i++){
        if(isBitISet(ch,i) > 0){
            trash = setBit(trash, i - 5);
        }
    }

	printf("\n\ntrash(givemethetrash): %d\n", trash);
    return trash;
}

//OBTEM O TAMANHO DA ARVORE DO ARQUIVO A SER DESCOMPRIMIDO
int givemethesizeTree(FILE *f){

	printf("\nDentro na função gimethesizeTree");
	int i, ch = 0, sizeTree = 0;
    rewind(f);
	//fseek(f,0,SEEK_SET);
    ch = fgetc(f);

    for(i = 0; i <= 4; i++){
        if(isBitISet(ch,i) > 0){
            sizeTree = setBit(sizeTree, i + 8);
        }
    }
    ch = fgetc(f);
    for(i = 0; i <= 7; i++){
        if(isBitISet(ch,i) > 0){
            sizeTree = setBit(sizeTree, i);
        }
    }

    printf("\nsizeTree(funcao givemesizeTheTree): %d\n", sizeTree);
    return sizeTree;
}

//OBTEM A ARVORE DO ARQUIVO A SER DESCOMPRIMIDO(RECURSIVA)
pnode *givemeHtree(FILE *f, int *sizeTree){

	if(*sizeTree > 0){

		pnode *root;
        root = createpnode(0,0,NULL,NULL);
        unsigned char ch = 0;
        ch = fgetc(f);
        if(ch == '*'){
            --*sizeTree;
            root -> c = ch;
            root -> left = givemeHtree(f,sizeTree);
            root -> right = givemeHtree(f,sizeTree);
        }
        else{
            if(ch == '\\'){
                ch = fgetc(f);
            }
            --*sizeTree;
            root -> c = ch;
            root -> left = NULL;
            root -> right = NULL;
        }
        return root;
    }
    return NULL;
}

//INICIA A DESCOMPRESSAO DO ARQUIVO
void makedecompressOutputfile(FILE *f,FILE *writeoutput,pnode *huff,int trash, int sizeTree){

	int i = 0, ch = 0;
	pnode *node = NULL;
	node = huff;
	rewind(f);

	//setando para o inicio do arquivo comprimido - "pulando" os 2 bytes iniciais e a arvore.
	while( i < sizeTree + 2)
	{

		if(ch == '\\')
		{
			fgetc(f);
			ch = fgetc(f);
			//printf("%c", ch);
		}
		else
		{
			ch = fgetc(f);
			//printf("%c", ch);

		}


		i++;
	}
	/*
	 * Esse proximo passo precisa do auxch fora do while para funcionar e funciona assim:
	 * primeiro: Na primeira execucao ele entra no primeiro if, coloca o atual byte em ch, e guarda o proximo em auxch.
	 * segundo:  O ch eh verificado ate o ultimo bit
	 * terceiro: Depois que o ultimo bit do ch eh verificado, o contador i volta pro 7, o ch recebe o auxch e auxch guarda o proximo byte...
	 * Quatro: Tudo se repete ate o final de arquivo ser encontrado, dai o auxch sai do while guardando o ultimo byte.
	*/
	
	i = -1;
	int auxch = fgetc(f);
	while (!feof(f)) {

		if(i <= -1)
			{
				i = 7;
				ch = auxch;
				auxch = fgetc(f);

			}

			if(isBitISet(ch, i))
			{
				node = node->right;

				if(isLeaf(node))
				{

					fputc(node->c, writeoutput);
					node = huff;
				}

			} else {
				node = node->left;

				if(isLeaf(node))
				{
					fputc(node->c, writeoutput);
					node = huff;
				}
			}
		i--;
	}

	// escrevendo o ultimo byte
	for(i = 7; i >= trash; i-- )
	{
		if(isBitISet(auxch, i))
		{
			node = node->right;

			if(isLeaf(node))
			{

				fputc(node->c, writeoutput);
				node = huff;
			}

		} else {
			node = node->left;

			if(isLeaf(node))
			{
				fputc(node->c, writeoutput);
				node = huff;
			}
		}
	}

}
//EndDESCOMPRESS
//EndFunctions
