/*
 * main.c
 * Copyright (C) 2017 Ingrid Spangler
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "entregas.h"

int main(){
    
    int V, E, F, C, u, v, m, f, c, i, max_flow;
    Grafo g;
    scanf("%d %d %d %d", &V, &E, &F, &C);
    G_init(&g, V, E, F);
    for (i = 0; i < E; ++i) {
        scanf("%d %d %d", &u, &v, &m);
        G_insere(&g, u, v, m);
    }
    for (i = 0; i < F; ++i) {
        scanf("%d", &f);
        Franquia(&g, f);
    }
    for (i = 0; i < C; ++i) {
        scanf("%d", &c);
        Cliente(&g, c);
    }
    
    max_flow = G_Ford_Fulkerson(g);
    printf("%d\n", max_flow);
    G_free(&g);
    return 0;
}
