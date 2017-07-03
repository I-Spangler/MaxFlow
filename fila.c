/*
 * fila.c
 * Copyright (C) 2017 Ingrid Spangler
 *
 * Distributed under terms of the MIT license.
 */

#include "fila.h"

/*===================================================================
*
*	função : Fila F_init
*		.Retorna uma fila inicializada como nula
*	input : 
*		.void
*	output :
*		.Fila f : a fila criada
*	
*
===================================================================*/
Fila F_init(){
    Fila f;
    f.Proxima = NULL;    
    return f;
}

/*===================================================================
*
*	função : void F_push
*		.Insere um elemento no final da fila
*	input : 
*		.Fila* f : a fila
*		.int c : o elemento
*	output :
*		.void
*	
*
===================================================================*/
void F_push(Fila* f, int c){
    Fila* tmp = f;
    while((*tmp).Proxima != NULL){
        tmp = tmp->Proxima;
    }
    (*tmp).Proxima = calloc(1, sizeof(Fila));
    (*tmp).valor = c;
    (*tmp).Proxima->Proxima = NULL;
}

/*===================================================================
*
*	função : int F_pop
*		.Remove o elemento do início da fila e desaloca espaço
*	input : Fila* f
*		.a fila
*	output :
*		.int ret : o primeiro elemento da fila
*	
*
===================================================================*/
int F_pop(Fila* f){
    if(f->Proxima == NULL){
        printf("Fila Vazia");
        return -3;
    }
    int ret;
    ret = f->valor;
    Fila *next = f->Proxima;
    *f = *next;
    free(next);
    return ret;
}

/*===================================================================
*
*	função : bool F_vazia
*		.confere se a fila está vazia ou não
*	input : 
*		.Fila f : a fila, passada como parâmetro
*	output :
*		.bool, true se a fila estiver vazia, false caso contrário
*	
*
===================================================================*/
bool F_vazia(Fila f){
    return (f.Proxima == NULL);
}

/*===================================================================
*
*	função : void F_free
*		.desaloca o espaço utilizado pela fila
*	input : 
*		.Fila* f : a fila a ser desalocada
*	output :
*		.void
*	
*
===================================================================*/
void F_free(Fila* f){
    Fila *aDeletar = f->Proxima;
    while(aDeletar != NULL){  
        Fila *cp = aDeletar;
        aDeletar = aDeletar->Proxima;
        free(cp);
    }
}
