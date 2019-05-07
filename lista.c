#include <stdio.h> 
#include <stdlib.h>
#include "lista.h"
#include "objeto.h"

void inicia_lista_vertice(lista_vertice_t* lv){
	lv->tam=0;
	lv->comec=NULL;
	lv->fim=NULL;
}

void inicia_lista_face(lista_face_t* lf){
	lf->tam=0;
	lf->comec=NULL;
	lf->fim=NULL;
}

vertice_t* cria_vertice(double x,double y,double z, long int indice){
	vertice_t* v = (vertice_t*)malloc(sizeof(vertice_t));
	v->pro = NULL;
	v->ant = NULL;
	v->x = x;
	v->y = y;
	v->z = z;
	v->indice = indice;
	return v;   
}

face_t* cria_face(long int v1, long int v2, long int v3){
	face_t* f = (face_t*)malloc(sizeof(face_t));
	f->pro = NULL;
	f->ant = NULL;
	f->v1 = v1;
	f->v2 = v2;
	f->v3 = v3;
	return f;
}

void inserir_vertice(lista_vertice_t *lv, double x, double y, double z, long int indice){
    vertice_t* v = cria_vertice(x,y,z,indice);
    
	if(lv->tam==0){
		lv->comec = v;
		lv->fim = v;
		lv->tam++;
	}else{
		v->ant = lv->fim;
		v->pro = NULL;
		
		lv->fim->pro = v;
		lv->fim = v;
		lv->tam++;
	}
	
}

void inserir_face(lista_face_t *lf, long int v1, long int v2, long int v3){
    face_t* f = cria_face(v1,v2,v3);
    
	if(lf->tam == 0){
		lf->comec = f;
		lf->fim = f;
		lf->tam++;
	}else{
		f->ant = lf->fim;
		f->pro = NULL;
		
		lf->fim->pro = f;
		lf->fim = f;
		lf->tam++;
	}
		
}

void remover_face(lista_face_t *lf, long int v1, long int v2, long int v3){
	//Se a lista está vazia, sai da funçao
	if (lf->comec == NULL)
		return;

	face_t *aux = lf->comec;
	//Senão, se o primeiro for o elemento, remove do início
	if((lf->comec->v1 == v1) && (lf->comec->v2 == v2) && (lf->comec->v3 == v3)){
		//printf("Face que sera removida: v1 %ld v2 %ld v3 %ld\n", v1, v2, v3);
		lf->comec = lf->comec->pro;
		if (lf->comec)
			lf->comec->ant = NULL;
		else				//Se ele for o último elemento
			lf->fim=NULL;
		
		free(aux);
		lf->tam--;
		//printf("Face removida com sucesso!\n");
		return;
	}
	//Senão anda até achar
	while(aux){
		if((aux->v1 == v1) && (aux->v2 == v2) && (aux->v3 == v3)){
			//printf("Face que sera removida: v1 %ld v2 %ld v3 %ld\n", v1, v2, v3);
			if (aux->pro == NULL){
				//É o último elemento
				aux->ant->pro = NULL;
				lf->fim = aux->ant;
			}else{
				//É um elemento no meio da lista
				aux->ant->pro = aux->pro;
				aux->pro->ant = aux->ant;
			}

			free(aux);
			lf->tam--;
			//printf("Face removida com sucesso!\n");
			return;
		}

		aux = aux->pro;
	}
}

void remover_vertice(lista_vertice_t *lv, long int indice){
	//Se a lista está vazia, sai da funçao
	if (lv->comec == NULL)
		return;

	vertice_t *aux = lv->comec;
	//Senão, se o primeiro for o elemento, remove do início
	if((lv->comec->indice == indice)){
		lv->comec = lv->comec->pro;
		if (lv->comec)
			lv->comec->ant = NULL;
		else				//Se ele for o último elemento
			lv->fim=NULL;
		
		free(aux);
		lv->tam--;
		printf("Vertice removido com sucesso!\n");
		return;
	}
	//Senão anda até achar
	while(aux){
		if((aux->indice == indice)){
			if (aux->pro == NULL){
				//É o último elemento
				aux->ant->pro = NULL;
				lv->fim = aux->ant;
			}else{
				//É um elemento no meio da lista
				aux->ant->pro = aux->pro;
				aux->pro->ant = aux->ant;
			}

			free(aux);
			lv->tam--;
			printf("Vertice removido com sucesso!\n");
			return;
		}

		aux = aux->pro;
	}
}
