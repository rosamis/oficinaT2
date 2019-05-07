#ifndef CHOP_H
#define CHOP_H

int verifica_z(lista_vertice_t *v, int pos, double mediaz);

void encontra_face(lista_face_t *f, lista_vertice_t *v, vertice_t *menor_coord, vertice_t *maior_coord, double pm);

vertice_t *encontra_tam_verticez(lista_vertice_t *v, int boole);

double media_pontos(vertice_t *menor, vertice_t *maior);

#endif