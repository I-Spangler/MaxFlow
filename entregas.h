/*
 * entregas.h
 * Copyright (C) 2017 Ingrid Spangler
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ENTREGAS_H
#define ENTREGAS_H
#include "grafo.h"

void Cliente(Grafo* g, int c);
void Franquia(Grafo* g, int f);
void Source_init(Grafo* g, int F);
void S_insere(Grafo* g, int f);
void Confere(Grafo* g, int c);
int min(int a, int b);

#endif /* !ENTREGAS_H */
