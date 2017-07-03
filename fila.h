/*
 * fila.h
 * Copyright (C) 2017 Ingrid Spangler
 *
 * Distributed under terms of the MIT license.
 */

#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*! \struct Fila 
 *  \brief Fila
 *
 *  valor: dado atual
 *  *Proxima: próxima célula
 */
typedef struct Fila{
    int valor;    
    struct Fila *Proxima;
}Fila;

Fila F_init();
void F_push(Fila* f, int c);
int F_pop(Fila* f);
void F_free(Fila* f);
bool F_vazia(Fila f);

#endif /* !FILA_H */
