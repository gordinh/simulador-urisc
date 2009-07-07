#ifndef __MEMORIA_H_INCLUDED__
#define __MEMORIA_H_INCLUDED__

/*
 *
 *      Arquivo: memoria.h
 *        Autor: Leonardo Vilela Teixeira
 *        email: vilela@dcc.ufmg.br
 *
 */

#include "defs.h"

#include <stdbool.h>

/* ************************************************************************** */
/* ========================== ESTRUTURAS DE DADOS =========================== */
/* ************************************************************************** */

typedef bool Registrador[BITS_ARQ];

/* ========================================================================== */

typedef struct bnc_reg_str
{
    Registrador Regs[NUM_REGS];
} Banco_de_Registradores;

/* ========================================================================== */

typedef struct mem_str
{
    Word posicao[TAM_MEMORIA];
} Memoria;

/* ************************************************************************** */
/* ================================ FUNÇÕES ================================= */
/* ************************************************************************** */

void Reg_Escreve_Word( Registrador * R, Word W );
void Reg_Le_Word( Registrador R, Word Destino );

/* ========================================================================== */

void B_Reg_Escreve_Word( Banco_de_Registradores * B, bool reg_num[3], Word D );
void B_Reg_Le_Word( Banco_de_Registradores B, bool reg_num[3], Word Destino );

/* ========================================================================== */

void Mem_Escreve_Endereco( Memoria * M, Word Endereco, Word Dados );
void Mem_Le_Endereco( Memoria M, Word Endereco, Word Destino );

/* ************************************************************************** */

#endif /* __MEMORIA_H_INCLUDED__ */
