#ifndef __MEMORIA_H_INCLUDED__
#define __MEMORIA_H_INCLUDED__

/*
 * =============================================================================
 *
 *      Arquivo: memoria.h
 *        Autor: Leonardo Vilela Teixeira
 *        email: vilela@dcc.ufmg.br
 *
 * =============================================================================
 */

#include "defs.h"

#include <stdbool.h>

/* ************************************************************************** */
/* ========================== ESTRUTURAS DE DADOS =========================== */
/* ************************************************************************** */

typedef struct mem_str
{
    Word posicao[TAM_MEMORIA];
} Memoria;

/* ************************************************************************** */
/* ================================ FUNÇÕES ================================= */
/* ************************************************************************** */

void Mem_Escreve_Endereco( Memoria * M, Word Endereco, Word Dados );
void Mem_Le_Endereco( Memoria M, Word Endereco, Word Destino );

/* ************************************************************************** */

#endif /* __MEMORIA_H_INCLUDED__ */
