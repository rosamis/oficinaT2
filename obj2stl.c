/* obj2stl.c
 * 
 * Copyright 2018 Júlio César Luppi Doebeli <julio dot doebeli at gmail dot com>
 *                Roberta Samistraro Tomigian <ro dot samis dot comp at gmail dot com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

/* Ao executar o programa obj2stl passando como entrada um arquivo .obj, este programa deve gerar como
arquivo de saída um arquivo .stl do tipo binário que contenha exatamente o mesmo objeto do arquivo de
entrada (ou seja, seu programa é um conversor do formato obj para o formato stl). Para simplificar, você
pode assumir que o arquivo de entrada contém apenas triângulos como faces.*/

#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "objeto.h"

vertice_t* getVertice(lista_vertice_t *lv, long int indice){
    fprintf(stdout,"vertice_t* getVertice(lista_vertice_t *lv, long int indice)"); fflush(stdin);
    vertice_t *ve = lv->comec;
    long int i;

    for(i=1 ; i <= indice ; i++){
        //if(i > lv->tam) return NULL;
        //if(ve->pro == NULL) return NULL;
        ve = ve->pro;
    }
    fprintf(stdout,"  return %p\n",ve); fflush(stdin);
    return ve;
}

/*  
void escreve_arquivo_stl_ASCII(char nome_arquivo_de_saida[],lista_face_t *lf, lista_vertice_t *lv){
	FILE *arquivo_de_saida = NULL;
    vertice_t *v1 = NULL, *v2 = NULL, *v3 = NULL;
    face_t *fa = NULL;

    if( (lf==NULL) && (lf->comec==NULL) && (lv==NULL) && (lv->comec==NULL) ) {
        fprintf(stderr, " Erro de execução de função devido a parametros invalidos!\n");
        fprintf(stderr, "void escreve_arquivo_stl(char %s,lista_face_t %x, lista_vertice_t %x)\n",(unsigned int)nome_arquivo_de_saida, (unsigned int)lf, (unsigned int)lv);
		fprintf(stderr, "                                     lf->comec = %x, lc->comec = %x\n\n",(unsigned int)lf->comec , (unsigned int)lv->comec);
        exit(1);
	}


    FILE *arquivo_de_saida = fopen(nome_arquivo_de_saida, "w+");
	if(arquivo_de_saida == NULL){
		printf("%s\n","Erro na escrita do arquivo!" );
		exit(1);
	}

	
    fa = lf->comec;
    v1 = getVertice(lv, fa->v1);
    v2 = getVertice(lv, fa->v3);
    v3 = getVertice(lv, fa->v3);

    fprintf( arquivo_de_saida, "solid \n");
    do{
        fprintf( arquivo_de_saida, "\t facet normal %df %df %df\n", fa->v1, fa->v2, fa->v3);
        fprintf( arquivo_de_saida, "\t\t outer loop\n"); 
        fprintf( arquivo_de_saida, "\t\t\t vertex %df %df %df \n", v1->x, v1->y, v1->z);
        fprintf( arquivo_de_saida, "\t\t\t vertex %df %df %df \n", v2->x, v2->y, v2->z);
        fprintf( arquivo_de_saida, "\t\t\t vertex %df %df %df \n", v3->x, v3->y, v3->z);
        fprintf( arquivo_de_saida, "\t\t endloop\n");
        fprintf( arquivo_de_saida, "\t endfacet\n");

        fa = fa->pro;
        v1 = getVertice(lv, fa->v1);
        v2 = getVertice(lv, fa->v3);
        v3 = getVertice(lv, fa->v3);
    }while(fa != NULL);
	fprintf( arquivo_de_saida, "endsolid \n");
	fclose(arquivo_de_saida);
}*/

void escreve_arquivo_stl_Binary(char nome_arquivo_de_saida[],lista_face_t *lf, lista_vertice_t *lv){
	fprintf(stdout,"escreve_arquivo_stl_Binary(char nome_arquivo_de_saida[],lista_face_t *lf, lista_vertice_t *lv)\n");
    FILE *arquivo_de_saida = NULL;
    vertice_t *v1 = NULL, *v2 = NULL, *v3 = NULL;
    face_t *fa = NULL;

   /* if( (lf==NULL) && (lf->comec==NULL) && (lv==NULL) && (lv->comec==NULL) ) {
        //fprintf(stderr, " Erro de execução de função devido a parametros invalidos!\n");
        //fprintf(stderr, "void escreve_arquivo_stl(char %s,lista_face_t %x, lista_vertice_t %x)\n",nome_arquivo_de_saida, lf, lv);
		//fprintf(stderr, "                                     lf->comec = %x, lc->comec = %x\n\n",lf->comec , lv->comec);
        exit(1);
	}*/

    
    arquivo_de_saida = fopen(nome_arquivo_de_saida, "w+");
	if(arquivo_de_saida == NULL){
		fprintf(stderr, "%s\n","Erro na escrita do arquivo!" );
		exit(1);
	}
	
    
    fa = lf->comec;
    v1 = getVertice(lv, fa->v1);    fprintf(stdout,"v1 = getVertice(lv, fa->v1), x= %lf y= %lf z= %lf\n", v1->x, v1->y, v1->z); fflush(stdout);
    v2 = getVertice(lv, fa->v2);    fprintf(stdout,"v2 = getVertice(lv, fa->v2), x= %lf y= %lf z= %lf\n", v2->x, v2->y, v2->z); fflush(stdout);
    v3 = getVertice(lv, fa->v3);    fprintf(stdout,"v3 = getVertice(lv, fa->v3), x= %lf y= %lf z= %lf\n\n", v3->x, v3->y, v3->z); fflush(stdout);
    long int *pch, ch = 0;  
    pch = &ch;
    char *str = "0123456789012345678901234567890123456789001234567890123456789012345678901234567890";
    //UINT8[80] – Header
    //for(int i=1; i<=80; i++) 
        fwrite(str,1,80,arquivo_de_saida);
    fflush(arquivo_de_saida);
    
    //UINT32 – Number of triangles
    unsigned int tam = (unsigned int)lf->tam;
    fwrite(&tam,4,1,arquivo_de_saida); fflush(arquivo_de_saida);
    
    do{ //foreach triangle
        fprintf( stdout,"REAL32[3] – Normal vector;   "); fflush(stdout);
        fwrite(pch,4,1,arquivo_de_saida); fflush(arquivo_de_saida);
        fwrite(pch,4,1,arquivo_de_saida); fflush(arquivo_de_saida);
        fwrite(pch,4,1,arquivo_de_saida); fflush(arquivo_de_saida);

        fprintf( stdout,"REAL32[3] – Vertex 1;   "); fflush(stdout);
        fwrite(&(v1->x),4,1,arquivo_de_saida); fflush(arquivo_de_saida);
        fwrite(&(v1->y),4,1,arquivo_de_saida); fflush(arquivo_de_saida);
        fwrite(&(v1->z),4,1,arquivo_de_saida); fflush(arquivo_de_saida);
        
        fprintf( stdout,"REAL32[3] – Vertex 2;   "); fflush(stdout);
        fwrite(&(v2->x),4,1,arquivo_de_saida); fflush(arquivo_de_saida);
        fwrite(&(v2->y),4,1,arquivo_de_saida); fflush(arquivo_de_saida);
        fwrite(&(v2->z),4,1,arquivo_de_saida); fflush(arquivo_de_saida);
        
        fprintf( stdout,"REAL32[3] – Vertex 3;   "); fflush(stdout);
        fwrite(&(v3->x),4,1,arquivo_de_saida); fflush(arquivo_de_saida);
        fwrite(&(v3->y),4,1,arquivo_de_saida); fflush(arquivo_de_saida);
        fwrite(&(v3->z),4,1,arquivo_de_saida); fflush(arquivo_de_saida);
        
        fprintf( stdout,"UINT16 – Attribute byte count \n\n"); fflush(stdout);
        fwrite(pch,2,1,arquivo_de_saida);

        fa = fa->pro;
        v1 = getVertice(lv, fa->v1);    fprintf(stdout,"v1 = getVertice(lv, fa->v1), x= %lf y= %lf z= %lf\n", v1->x, v1->y, v1->z); fflush(stdout);
        v2 = getVertice(lv, fa->v2);    fprintf(stdout,"v2 = getVertice(lv, fa->v2), x= %lf y= %lf z= %lf\n", v2->x, v2->y, v2->z); fflush(stdout);
        v3 = getVertice(lv, fa->v3);    fprintf(stdout,"v3 = getVertice(lv, fa->v3), x= %lf y= %lf z= %lf\n\n", v3->x, v3->y, v3->z); fflush(stdout);
    }while(fa->pro != NULL);
	fprintf(stdout,"fclose(arquivo_de_saida);\n\n");
    fflush(stdout);
    
    fclose(arquivo_de_saida);
}

int main(){
	char *nome_arquivo = "teste2.obj";
	//printf("%s\n","Entre com o nome do arquivo .obj: " );
	//scanf("%s", nome_arquivo);

	lista_vertice_t *lv;
	lista_face_t *lf;
	lv=(lista_vertice_t *)malloc(sizeof(lista_vertice_t));
	lf=(lista_face_t *)malloc(sizeof(lista_face_t));
	
    inicia_lista_vertice(lv);
	inicia_lista_face(lf);
	le_arquivo_obj(nome_arquivo,lf,lv);

    //printf("%s\n","Entre com o nome do arquivo .stl: " );
	//scanf("%s", nome_arquivo);
    nome_arquivo = "teste2.stl";
    escreve_arquivo_stl_Binary(nome_arquivo,lf,lv);    
    return 0;
}