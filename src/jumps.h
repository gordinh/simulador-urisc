#ifndef __JUMPS_H_INCLUDED__
#define __JUMPS_H_INCLUDED__

/*
 * =============================================================================
 *
 *      Arquivo: jumps.h
 *        Autor: Lucas Alves Guerra França
 *        email: lguerra@dcc.ufmg.br
 *
 * =============================================================================
 */

#include "defs.h"
#include "registradores.h"
#include "alu.h"

#include <stdbool.h>


/* ************************************************************************** */
/* ================================ FUNÇÕES ================================= */
/* ************************************************************************** */

void Jump_Extende_Sinal_Offset_Desvio( Word *ALU_B, Registrador *IR );

/* ================================ FORMATO V =============================== */

void Jump_Incondicional( Word *end_destino, Registrador *B );

/* ================================ FORMATO IV ============================== */

void Jump_Condicional_True( Word *end_destino, Registrador *SaidaALU, Flags_ALU *flags, Registrador *PC, Registrador *IR );
void Jump_Condicional_False( Word *end_destino, Registrador *SaidaALU, Flags_ALU *flags, Registrador *PC, Registrador *IR );

/* ================================ FORMATO VI ============================== */

void Jump_and_Link( Word *end_destino, Registrador *B, Registrador *PC, Banco_de_Registradores *Breg );
void Jump_Register( Word *end_destino, Registrador *B );

/* ========================================================================== */

void Jump_Calcula_Endereco_Desvio ( Word *end_destino, Registrador *B, Registrador *SaidaALU, Registrador *PC, Registrador *IR, Banco_de_Registradores *Breg, Flags_ALU *flags );

/* ************************************************************************** */

#endif /* __JUMPS_H_INCLUDED__ */
