#include <stdio.h> 
#include <stdlib.h>
#include "objeto.h"
#include "lista.h"
#include "ChopObj.h"

/*Ao executar o programa ChopObj passando como entrada um arquivo.obj, este programa deve gerar como arquivo de saida um arquivo.obj 
que contenha o objeto do arquivo de entrada,  exceto que eliminando todas as faces que estejam contidas completamente na metade de cima do objeto.  
Para determinar quais faces estao contidas na metade de cima do objeto, calcule o ponto medio (xm, ym, zm) entre o vertice de menor coordenada z
e o vertice de maior coordenada z. As faces que devem ser eliminadas devem ser aquelas que tem todos os seus vertices acima deste ponto medio, ou seja, com 
coordenada z maiores do que zm.*/

int verifica_z(lista_vertice_t *v, int pos, double mediaz){
	vertice_t *aux = v->comec;
	while(aux){
		if ((aux->indice == pos) && (aux->z > mediaz))
			return 1;

		aux = aux->pro;
	}

	return 0;
}

void encontra_face(lista_face_t *f, lista_vertice_t *v, vertice_t *menor_coord, vertice_t *maior_coord, double pm){
	face_t *aux = f->comec;
	while(aux){
		if (verifica_z(v, aux->v1, pm) && verifica_z(v, aux->v2, pm) && verifica_z(v, aux->v3, pm)){
			remover_face(f,aux->v1,aux->v2,aux->v3);
		}

		aux = aux->pro;
	}
}
vertice_t *encontra_tam_verticez(lista_vertice_t *v, int boole){
	vertice_t *aux = v->comec;
	aux = aux->pro;
	vertice_t *coord = v->comec;
	if (boole == 1){ 		//procura menor
		while(aux){
			if (aux->z < coord->z){
				coord = aux;
			}
			aux = aux->pro;
		}
	}else if (boole == 0){	//procura maior
		while(aux){
			if (aux->z > coord->z){
				coord = aux;
			}
			aux = aux->pro;
		}
	}else printf("valor de entrada inválido, verifique se é 0 ou 1");

	return coord;
}

double media_pontos(vertice_t *menor, vertice_t *maior){
	double media;
	media = (menor->z + maior->z)/2;
	printf("Média de z: %lf\n", media);

	return media;
}

int main(){
	char nome_arquivo[50] = "teste4.obj";
	char nome_saida[50] = "saida.obj";
	// printf("%s\n","Entre com o nome do arquivo .obj: ");
	// scanf("%s", nome_arquivo);

	lista_vertice_t *v;
	lista_face_t *f;
	v = (lista_vertice_t *)malloc(sizeof(lista_vertice_t));
	f = (lista_face_t *)malloc(sizeof(lista_face_t));
	inicia_lista_vertice(v);
	inicia_lista_face(f);

	le_arquivo_obj(nome_arquivo,f,v);

	//encontra o vertice menor(1) ou maior(0) 
	vertice_t *menor_coord = encontra_tam_verticez(v, 1);
	vertice_t *maior_coord = encontra_tam_verticez(v, 0);

	//Calcula a media entre os vertices
	double pm = media_pontos(menor_coord, maior_coord);

	//Verifica o valor de z de cada vértice de cada face, se os tres forem > pm, retira face da lista
	encontra_face(f,v,menor_coord,maior_coord,pm);

	//Escreve no arquivo de saida.obj
	escreve_arquivo_obj(nome_saida,f,v);

	return 0;
}