#ifndef __ALU_H_INCLUDED__
#define __ALU_H_INCLUDED__
/*
 * =============================================================================
 *
 *       Arquivo:  alu.h
 *         Autores: Letícia Lana Cherchiglia, Leonardo Vilela Teixeira, Lucas Alves Guerra França
 *         email: letslc@dcc.ufmg.br, vilela@dcc.ufmg.br, lguerra@dcc.ufmg.br
 *
 * =============================================================================
 */

#include "defs.h"

/* ************************************************************************** */
/* ========================== ESTRUTURAS DE DADOS =========================== */
/* ************************************************************************** */

typedef struct fa_str
{
    bool neg;
    bool zero;
    bool carry;
    bool negzero;
    bool f_true;
    bool overflow;
} Flags_ALU;

/* ************************************************************************** */
/* ================================ FUNÃ‡Ã•ES ================================= */
/* ************************************************************************** */

void ALU_add(Word A, Word B, bool Cin, bool * Cout, Word C, bool * Overflow);
void ALU_and(Word A, Word B, Word C);
void ALU_or(Word A, Word B, Word C);
void ALU_xor(Word A, Word B, Word C);

void ALU_shift_left(Word A, Word C);
void ALU_shift_right(Word A, Word C);
void ALU_shift_left_a(Word A, Word C);
void ALU_shift_right_a(Word A, Word C);

void Complemento_de_Dois(Word A, Word Comp);

void ALU_controle( bool Op[5], bool opALU, bool bits_controle[7],
        bool ALUop[3] );
void ALU_opera( Word A, Word B, Word C, bool bits_controle[7], bool ALUop[3],
        Flags_ALU * Flags );

/* ************************************************************************** */

#endif /* __ALU_H_INCLUDED__ */
