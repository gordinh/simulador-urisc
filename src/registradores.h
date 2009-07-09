#ifndef __REGISTRADORES_H_INCLUDED__
#define __REGISTRADORES_H_INCLUDED__

/*
 * =============================================================================
 *
 *      Arquivo: registradores.h
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

typedef bool Registrador[BITS_ARQ];

/* ========================================================================== */

typedef struct bnc_reg_str
{
    Registrador Regs[NUM_REGS];
} Banco_de_Registradores;

/* ************************************************************************** */
/* ================================ FUNÃ‡Ã•ES ================================= */
/* ************************************************************************** */

void Reg_Escreve_Word( Registrador * R, Word W );
void Reg_Le_Word( Registrador R, Word Destino );

/* ========================================================================== */

void B_Reg_Escreve_Word( Banco_de_Registradores * B, bool reg_num[3], Word D );
void B_Reg_Le_Word( Banco_de_Registradores B, bool reg_num[3], Word Destino );


/* ************************************************************************** */

#endif /* __REGISTRADORES_H_INCLUDED__ */
