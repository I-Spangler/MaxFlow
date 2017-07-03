/*
 * entregas.c
 * Copyright (C) 2017 Ingrid Spangler
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include "entregas.h"
#include "grafo.h"
/*===================================================================
*
*	função : void Cliente
*		.Marca os clientes no grafo, insere a g.Sink como vértice final
*		e seta o fluxo final como INFINITO.
*	input : 
*		.Grafo* g : o grafo onde os clientes serão marcados
*		.int c : o número do vértice onde há um cliente
*	output :
*		.void
*
===================================================================*/

void Cliente(Grafo* g, int c){
    Confere(g, c);
    g->Vert[c].tam++;
    g->Vert[c].tipo = CLIENTE;
    g->Vert[c].data = realloc(g->Vert[c].data, sizeof(Data)*(g->Vert[c].tam));
    g->Vert[c].data[g->Vert[c].tam-1].adjacente = g->Sink;
    g->Vert[c].data[g->Vert[c].tam-1].fluxo = INFINITO;
    g->Vert[c].data[g->Vert[c].tam-1].residual = INFINITO;
}

/*===================================================================
*
*	função : void Confere
*		.Confere se um cliente é pai de uma ou mais franquias e as
*		remove de sua lista de adjacência, caso positivo.
*	input : 
*		.Grafo* g
*		.int c : o vértice cliente a ser conferido.
*	output :
*		.void
*	
*
===================================================================*/
void Confere(Grafo* g, int c){
    int i, j;
    for (i = 0; i < g->Vert[c].tam; ++i) {
        if(g->Vert[g->Vert[c].data[i].adjacente].tipo == FRANQUIA){
            g->Vert[c].tam--;
            j = i;
            //remove a franquia e reposiciona os demais
            while(j < g->Vert[c].tam-1){
                g->Vert[c].data[j].adjacente = g->Vert[c].data[j+1].adjacente;
                g->Vert[c].data[j].fluxo = g->Vert[c].data[j+1].fluxo;
                g->Vert[c].data[j].residual = g->Vert[c].data[j+1].residual;
                j++;
            }
        }
    }
}

/*===================================================================
*
*	função : void Franquia
*		.Marca as franquias no grafo, e as insere no vetor de adjacência
*		do vértice Source
*	input : 
*		.Grafo* g : o grafo onde as franquias serão marcadas
*		.int f : o número do vértice onde há uma franquia
*	output :
*		.void
*	
*
===================================================================*/

void Franquia(Grafo* g, int f){
    g->Vert[f].tipo = FRANQUIA;
    S_insere(g, f);
}

/*===================================================================
*
*	função : void Source_init
*		.Inicializa o espaço no heap do vértice inicial Source
*	input : 
*		.Grafo* g : o grafo
*		.int F : o número de franquias no grafo
*	output :
*		.void
*	
*
===================================================================*/

void Source_init(Grafo* g, int F){
    int i;
    Vertice src;
    src.tam = 0;
    src.data = calloc(F, sizeof(Data));
    g->Vert[g->Source] = src;
    for (i = 0; i < F; i++) {
        g->Vert[g->Source].data[i].fluxo = INFINITO;
        g->Vert[g->Source].data[i].residual = INFINITO;
    }
}

/*===================================================================
*
*	função : int min
*		.função auxiliar para o algoritmo de Fulkerson, computa o
*		mínimo entre dois fluxos
*	input : 
*		.int a, int b: dois inteiros
*	output :
*		.int min: o mínimo entre os dois
*	
*
===================================================================*/

int min(int a, int b){
    int min = a;
    if(a > b)
        min = b;
    return min;
}

/*===================================================================
*
*	função : void M_insere
*		.Insere os vértices de franquia na lista de adjacencia da Source
*	input : 
*		.Grafo* g : o grafo
*		.int f : o vértice onde há uma franquia
*	output :
*		.void
*	
*
===================================================================*/

void S_insere(Grafo* g, int f){
    g->Vert[g->Source].data[g->Vert[g->Source].tam].adjacente = f;
    g->Vert[g->Source].tam++;
}
