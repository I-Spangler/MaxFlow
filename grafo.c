/*
 * grafo.c
 * Copyright (C) 2017 Ingrid Spangler
 *
 * Distributed under terms of the MIT license.
 */

#include "grafo.h"
#include "fila.h"
#include "entregas.h"

/*===================================================================
*
*	função : void G_init
*		.inicializa a struct Grafo g, aloca espaço para seus vértices
*		e para cada vértice aloca espaço para sua lista de adjacência
*	input : 
*		.Grafo* g
*		.int V : o número de vértices
*		.int E : o número de arestas
*		.int F : o número de franquias
*	output :
*		.void
*	
===================================================================*/
void G_init(Grafo* g, int V, int E, int F){
    int i;
    g->V = V;
    g->E = E;
    g->Sink = V;
    g->Source = V+1;
    g->Vert = (Vertice*)malloc(sizeof(Vertice)*(V+2));
    Source_init(g, F);
    for(i = 0; i < V+1; i++) {
        g->Vert[i].data = calloc(1, sizeof(Data));
        g->Vert[i].tipo = NORMAL;
        g->Vert[i].tam = 0;
    }
   g->Vert[i].tam = 0;
}

/*===================================================================
*
*	função : void G_free
*		.Desaloca a memória consumida pelo grafo
*	input : 
*		.Grafo* g
*	output :
*		.void
*	
===================================================================*/
void G_free(Grafo* g){
    int i;
    free(g->Vert[g->Source].data);
    for (i = 0; i < g->V+1; ++i) {
        free(g->Vert[i].data);
    }
    free(g->Vert);
}

/*===================================================================
*
*	função : void G_insere
*		.Aloca um espaço extra para a nova aresta adjacente,
*		insere uma aresta com fluxo partindo do vértice g.Vert[v]
*		direcionado ao vértice adjacente na posição g.Vert[v].tam-1
*		do vetor.
*	input : 
*		.Grafo* g
*		.int v : vértice origem
*		.int adjacente : vértice destino
*		.int fluxo : fluxo da aresta entre os dois.
*	output :
*		.void
*
===================================================================*/
void G_insere(Grafo* g, int v, int adjacente, int fluxo){
    g->Vert[v].tam++;
    g->Vert[v].data = realloc(g->Vert[v].data, sizeof(Data)*(g->Vert[v].tam));
    g->Vert[v].data[g->Vert[v].tam-1].adjacente = adjacente;
    g->Vert[v].data[g->Vert[v].tam-1].residual = fluxo; 

    g->Vert[adjacente].tam++;
    g->Vert[adjacente].data = realloc(g->Vert[adjacente].data, sizeof(Data)*(g->Vert[adjacente].tam));
    g->Vert[adjacente].data[g->Vert[adjacente].tam-1].adjacente = v;
    g->Vert[adjacente].data[g->Vert[adjacente].tam-1].residual = 0;
}

/*===================================================================
*
*	função : int G_encontra
*		.Encontra o índice do vetor de adjacência de v que contém o 
*		vértice adj
*	input : 
*		.Grafo* g
*		.int v : vértice origem
*		.int adj : vértice destino
*	output :
*		.index : o índice do vértice destino
*	
===================================================================*/
int G_encontra(Grafo g, int v, int adj){
    int index;
    for (index = 0; index < g.Vert[v].tam; index++) {
        if(g.Vert[v].data[index].adjacente == adj)
            return index;
    }
    return -1;
}
    
/*===================================================================
*
*	função : bool G_BFS
*		.Performa uma busca de largura no grafo g, do vétrice Source
*		ao vértice Sink, e preenche um vetor de antecessores (origens)
*		dos vértices.
*	input : 
*		.Grafo g
*		.int* origens : o vetor de antecedência
*	output :
*		.bool (visitado[g.Sink] == true) : retorna 1 se há um caminho
*		e 0 se não há
*	
===================================================================*/
bool G_BFS(Grafo g, int* origens){
    Fila q = F_init();
    int i, prox;
    bool visitado[(g.V)+2];
    //nenhum foi visitado
    for (i = 0; i < g.V+2; i++){
        visitado[i] = false;
    }
    //push a matriz
    F_push(&q, g.Source);
    //enquanto a fila estiver pendente
    while(!F_vazia(q)){
        prox = F_pop(&q);
        //enfileira os vertices adjacentes ao da frente da fila
        //que não foram visitados ainda
        for(i = 0; i < g.Vert[prox].tam; i++){
            if(visitado[g.Vert[prox].data[i].adjacente] == false && g.Vert[prox].data[i].residual != 0){
                F_push(&q, g.Vert[prox].data[i].adjacente);
                //grava a origem de cada um

        //printf("%d max \n", g.Vert[prox].data[i].adjacente);
                origens[g.Vert[prox].data[i].adjacente] = prox;
                visitado[g.Vert[prox].data[i].adjacente] = true;
            }
        }
    }
    F_free(&q);
    return (visitado[g.Sink] == true);
}
/*===================================================================
*
*	função : int G_Ford_Fulkerson
*		.encontra o fluxo máximo entre a g.Source e a g.Sink
*	input : 
*		.Grafo g
*	output :
*		.int max_fluxo : o fluxo máximo encontrado
*
===================================================================*/
int G_Ford_Fulkerson(Grafo g){
    //vertice anterior, atual
    int ant, index, atual;
    int max_fluxo = 0;
    //vetor de origens
    int* origens = malloc(sizeof(int)*(g.V+2));
    for (int i=0; i<(g.V+2); i++){
        origens[i] = i;
    }

    //encontra as origens
    G_BFS(g, origens);
    while (G_BFS(g, origens)){
        int fluxo_parcial = INT_MAX;
        //encontra o fluxo minimo do caminho todo
        for (atual=g.Sink; atual!=g.Source; atual=origens[atual]){
            //printf("mat %d atual! %d\n", g.Source, atual);
            ant = origens[atual];
            //printf("ant! %d atual! %d\n", ant, atual);
            index = G_encontra(g, ant, atual);
            fluxo_parcial = min(fluxo_parcial, g.Vert[ant].data[index].residual);
        }
        //monta o caminho de retorno
        for (atual=g.Sink; atual != g.Source; atual=origens[atual]){
            ant = origens[atual];

            index = G_encontra(g, ant, atual);
            //diminui o fluxo
            g.Vert[ant].data[index].residual -= fluxo_parcial;
            //caminho inverso
            
            index = G_encontra(g, atual, ant);
            if(index != -1)
            g.Vert[atual].data[index].residual += fluxo_parcial;
        }
        max_fluxo += fluxo_parcial;
    }
    free(origens);
    return max_fluxo;
}
