#ifndef __REGISTRADORES_H_INCLUDED__
#define __REGISTRADORES_H_INCLUDED__

/*
 * =============================================================================
 *
 *      Arquivo: registradores.h
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

typedef bool Registrador[BITS_ARQ];

/* ========================================================================== */

typedef struct bnc_reg_str
{
    Registrador Regs[NUM_REGS];
} Banco_de_Registradores;

/* ************************************************************************** */
/* ================================ FUNÇÕES ================================= */
/* ************************************************************************** */

void Reg_Escreve_Word( Registrador * R, Word W );
void Reg_Le_Word( Registrador R, Word Destino );

/* ========================================================================== */

void B_Reg_Escreve_Word( Banco_de_Registradores * B, bool reg_num[3], Word D );
void B_Reg_Le_Word( Banco_de_Registradores B, bool reg_num[3], Word Destino );


/* ************************************************************************** */

#endif /* __REGISTRADORES_H_INCLUDED__ */
