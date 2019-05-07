#ifndef LISTA_H
#define LISTA_H

typedef struct vertice_s {
	double x,y,z;
	long int indice;
	int boo;
	struct vertice_s *pro, *ant;
} vertice_t;

typedef struct face_s {
	long int v1, v2, v3;
	double d1, d2, d3, area;
	struct face_s *pro, *ant;
} face_t;

typedef struct lista_vertice_s {
	struct vertice_s *comec, *fim;
	int tam;
} lista_vertice_t;

typedef struct lista_face_s {
	struct face_s *comec, *fim;
	int tam;
} lista_face_t;

typedef struct objeto_s {
	struct lista_vertice_s *v;
	struct lista_face_s *f;
} objeto_t;

void inicia_lista_vertice(lista_vertice_t* lv);

void inicia_lista_face(lista_face_t* lf);

vertice_t* cria_vertice(double x,double y,double z, long int indice);

face_t* cria_face(long int v1, long int v2, long int v3);

void inserir_vertice(lista_vertice_t *lv, double x, double y, double z, long int indice);

void inserir_face(lista_face_t *lf, long int v1,long int v2, long int v3);

void remover_face(lista_face_t *lf, long int v1, long int v2, long int v3);

void remover_vertice(lista_vertice_t *lv, long int indice);

#endif
