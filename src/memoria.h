#ifndef __MEMORIA_H_INCLUDED__
#define __MEMORIA_H_INCLUDED__

/*
 * =============================================================================
 *
 *      Arquivo: memoria.h
 *        Autores: Letícia Lana Cherchiglia, Leonardo Vilela Teixeira, Lucas Alves Guerra França
 *        email: letslc@dcc.ufmg.br, vilela@dcc.ufmg.br, lguerra@dcc.ufmg.br
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
/* ================================ FUNÃ‡Ã•ES ================================= */
/* ************************************************************************** */

void Mem_Escreve_Endereco( Memoria * M, Word Endereco, Word Dados );
void Mem_Le_Endereco( Memoria M, Word Endereco, Word Destino );

/* ************************************************************************** */

#endif /* __MEMORIA_H_INCLUDED__ */
