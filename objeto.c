#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "objeto.h"
#include "lista.h"

//DÁ  PROBLEMA QUANDO TEM UMA LINHA EM BRANCO!!!!! VER DEPOIS
void le_arquivo_obj(char nome_arquivo[],lista_face_t *f, lista_vertice_t *v){
	char ch, pr;
	double x,y,z;
	long int v1,v2,v3;
	int indice = 0;

	FILE *fp = fopen(nome_arquivo, "r");
	if(fp == NULL){
		printf("%s\n","Erro na abertura do arquivo!" );
		exit(1);
	}

	while((ch = fgetc(fp)) != EOF && (pr = fgetc(fp)) != EOF){ 
		if (ch == 'v' && pr == ' ' ){
			//insere na lista de vertice
			fscanf(fp, "%lf %lf %lf\n", &x, &y, &z);
			indice++;
			inserir_vertice(v,x,y,z,indice);

		}else if (ch == 'f' && pr == ' '){
			//insere na lista de faces
			fscanf(fp, "%ld %ld %ld\n", &v1, &v2, &v3);
			inserir_face(f,v1,v2,v3);
		}else{
			//ignora linha
		//	fscanf(fp, "%s\n", str);
			while((ch=fgetc(fp)) != '\n' && ch != EOF);
		}

	}

	fclose(fp);

}

void escreve_arquivo_obj(char nome_saida[],lista_face_t *f, lista_vertice_t *v){
	FILE *fp;
	fp = fopen(nome_saida ,"w+");

	if (fp == NULL){
	printf("Um erro ocorreu ao tentar criar o arquivo.\n");
	}

	vertice_t *auxv = v->comec;
	while(auxv!=NULL){
		fprintf(fp, "v %lf %lf %lf\n", auxv->x, auxv->y, auxv->z);
		auxv = auxv->pro;
	}

	face_t *auxf = f->comec;
	while(auxf!=NULL){
		fprintf(fp, "f %ld %ld %ld\n", auxf->v1, auxf->v2, auxf->v3);
		auxf = auxf->pro;
	}

	printf("Arquivo escrito com sucesso\n");

	fclose(fp);
}