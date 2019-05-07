#ifndef SIMPLIFY_H
#define SIMPLIFY_H
#include "lista.h"

vertice_t *busca_v(lista_vertice_t *v, long int vert);

double distancia(lista_vertice_t *v, long int v1, long int v2);

double area_face(double d1, double d2, double d3);

void calcula_dist_area(lista_face_t *f, lista_vertice_t *v);

face_t* particiona(face_t *s, face_t *u);

void quicksort(lista_face_t *lf, face_t *f, face_t *u);

void calcula_menores_remove(lista_face_t *lf);

void percorre_lv(lista_vertice_t *v);

void busca_e_marca(long int vert, lista_vertice_t *lv);

void percorre_lf(lista_face_t *lf, lista_vertice_t *lv);

void verifica_e_remove_lv(lista_face_t *lf,lista_vertice_t *lv);


#endif
