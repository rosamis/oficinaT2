#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 
#include "objeto.h"
#include "lista.h"
#include "SimplifyObj.h"

/*Ao executar o programa SimplifyObj passando como entrada um arquivo.obj, este programa deve gerar como arquivo 
de saıda um arquivo.obj que contenha o objeto do arquivo de entrada, exceto que contendo 20% menos faces. 
As faces que devem ser removidas sao as 20% menores faces (ou seja, faces com menor superficie do objeto original).
Os vertices que nao fizerem parte de nenhuma face tambem devem ser removidos.*/

vertice_t *busca_v(lista_vertice_t *v, long int vert){
    vertice_t *aux = v->comec;
    //Busca na lista o vertice correspondente
    while(aux){
        if (aux->indice == vert)
            return aux;
        
        aux = aux->pro;
    }

    return NULL;
}

double distancia(lista_vertice_t *v, long int v1, long int v2){
    //Buscar na lista de vertices v1 e v2, quando achar calcula a distancia
    vertice_t *vet1 = busca_v(v,v1);
    vertice_t *vet2 = busca_v(v,v2);

    double subx = (vet2->x - vet1->x);
    double suby = (vet2->y - vet1->y);
    double subz = (vet2->z - vet1->z);

    subx = pow(subx, 2);
    suby = pow(suby, 2);
    subz = pow(subz, 2);


    double dist = sqrt((subx + suby + subz));

    return dist;
}

double area_face(double d1, double d2, double d3){
    double area, sp;
    //Calcula o semiperimetro dos lados
    sp = (d1 + d2 + d3)/2;

    d1 = sp - d1;
    d2 = sp - d2;
    d3 = sp - d3;

    //Calcula a área
    area = sqrt(sp*(d1*d2*d3));
    return area;
}

void calcula_dist_area(lista_face_t *f, lista_vertice_t *v){
    face_t *aux = f->comec;
    while(aux){
        //Verificar os vertices que pertencem aquela face e calcular a distancia entre v1v2, v2v3 e v3v1
        aux->d1 = distancia(v, aux->v1, aux->v2);
        aux->d2 = distancia(v, aux->v2, aux->v3);
        aux->d3 = distancia(v, aux->v1, aux->v3);

        //Calcula a area
        aux->area = area_face(aux->d1, aux->d2, aux->d3);

        aux = aux->pro;
    }
}


face_t* particiona(face_t *s, face_t *u){
    if(s == u) return s;

    double tmp;
    face_t *menor = s, *pivo = u, *curr = s;

    while(curr != NULL && curr != u){
        if(curr->area < pivo->area){
            tmp = menor->area;
            menor->area = curr->area;
            curr->area = tmp;
            menor = menor->pro;
        }
        curr = curr->pro;

    }
    tmp = pivo->area;
    pivo->area = menor->area;
    menor->area = tmp;
    return menor;
}

void quicksort(lista_face_t *lf, face_t *f, face_t *u){
    face_t *p;
    p = particiona(f, u);
    if(f != p)
        quicksort(lf, f, p->ant);
    if(p != u)
        quicksort(lf, p->pro, u);
}


void calcula_menores_remove(lista_face_t *lf){
    //As 20% menores faces
    int tam = lf->tam;
    tam = tam*(0.2);
    printf("Deve remover: %d\n", tam);
    int i = 0;
    //Remove as 20% menores faces que estão ordenadas
    while(i < tam){
        face_t *aux = lf->comec;
        remover_face(lf, aux->v1, aux->v2, aux->v3);
        i++;
    }
    printf("Removeu: %d\n", i);
}

void percorre_lv(lista_vertice_t *v){
    //percorre lista de vertices marcando boo com 0, para evitar lixo
    vertice_t *aux = v->comec;
    while(aux){
        aux->boo = 0;
        aux = aux->pro;
    }
}
void busca_e_marca(long int vert, lista_vertice_t *lv){
    //Procura o vertice correspondente a face e marca bool como 1
    vertice_t *v = lv->comec;
    while(v->indice != vert)
        v = v->pro;
    
    if (v)
        v->boo = 1;
    else printf("Vertice nao existe");


}
void percorre_lf(lista_face_t *lf, lista_vertice_t *lv){
    //Percorre a lista de faces, busca os vertices correspondentes e marca 1 em boo
    percorre_lv(lv);
    face_t *aux = lf->comec;
    while(aux){
        busca_e_marca(aux->v1,lv);
        busca_e_marca(aux->v2,lv);
        busca_e_marca(aux->v3,lv);
        aux = aux->pro;
    }
}

void verifica_e_remove_lv(lista_face_t *lf,lista_vertice_t *lv){
    percorre_lf(lf,lv);
    vertice_t *v = lv->comec;
    while(v){
        //Se v = 0, remove
        printf("v->boo: %d\n", v->boo);
        if(v->boo == 0)
            remover_vertice(lv,v->indice);
        v = v->pro;
    }
}
int main(){
	char nome_arquivo[50] = "teste1.obj";
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

    //Calcula o lado e a área de uma face
    calcula_dist_area(f,v);

    //Ordena lista de faces
    quicksort(f, f->comec, f->fim);

    //Calcula as menores faces e remove
    calcula_menores_remove(f);

    //Percorre a lista de vertices e remove os nao usados
    verifica_e_remove_lv(f,v);

    //Escreve no arquivo de saida.obj
	escreve_arquivo_obj(nome_saida,f,v);

	return 0;
}
