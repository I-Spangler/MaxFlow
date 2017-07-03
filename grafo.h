/*
 * grafo.h
 * Copyright (C) 2017 Ingrid Spangler
 *
 * Distributed under terms of the MIT license.
 */

#ifndef GRAFO_H
#define GRAFO_H
#define MATRIZ 0
#define INFINITO INT_MAX
#define NORMAL 3
#define CLIENTE 1
#define FRANQUIA 2
#include <stdbool.h>
#include <limits.h>

/*! \struct Data 
 *  \brief Conteúdo de cada vetor de adjacência
 *
 *  Adjacente: índice do vértice adjacente
 *  fluxo: valor do fluxo na aresta
 *  residual: valor residual da aresta
 */
typedef struct Data {
    int adjacente;
    int fluxo;
    int residual;
}Data;
/*! \struct Vertice 
 *  \brief Vetor com todos os vértices do grafo
 *
 *  tam: número de arestas
 *  tipo: cliente, franquia ou normal
 *  *data: vetor de vértices adjacentes
 */

typedef struct Vertice{
    int tam;
    int tipo;
    Data *data;
}Vertice;


/*! \struct Grafo
 *  \brief Grafo unidirecional com peso nas arestas
 *
 *  V: número de vértices
 *  E: número de arestas
 *  *Vert: vetor de vértices
 *  Source: vértice extra para a distribuidora
 *  Sink: vértice extra para o fim
 */
typedef struct Grafo{
    int V;
    int E;
    Vertice *Vert;
	int Source;
    int Sink;
}Grafo;

void G_init(Grafo* g, int V, int E, int F);
void G_insere(Grafo* g, int v, int adjacente, int fluxo);
int G_encontra(Grafo g, int v, int adj);
bool G_BFS(Grafo g, int* origens);
void G_free(Grafo* g);
int G_Ford_Fulkerson(Grafo g);

#endif /* !GRAFO_H */
