#ifndef OBJETO_H
#define OBJETO_H
#include "lista.h"

void le_arquivo_obj(char nome_arquivo[],lista_face_t *f, lista_vertice_t *v);

void escreve_arquivo_obj(char nome_saida[],lista_face_t *f, lista_vertice_t *v);

#endif

