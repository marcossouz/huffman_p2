#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "freq_w.h"

int* freq_w(FILE *f){
    setlocale(LC_ALL,"");//DEFINE A LOCALIZACAO ATUAL.
    unsigned char x;
	int i;
	int *countsort;
	countsort = (int*)malloc(256*sizeof(int));
	for ( i = 0; i < 256; i++ ){
		countsort[i] = 0;
	}
	while(1){
		x = fgetc(f);
		if(feof(f)){
			break;
		}
		countsort[x]++;
	}
	return countsort;
}
