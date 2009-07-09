#ifndef __PROCESSADOR_H_INCLUDED__
#define __PROCESSADOR_H_INCLUDED__

/*
 * =============================================================================
 *
 *      Arquivo: processador.h
 *        Autor: Lucas Alves Guerra França
 *        email: lguerra@dcc.ufmg.br
 *
 * =============================================================================
 */

#include "defs.h"
#include "registradores.h"
#include "alu.h"
#include "memoria.h"
#include "controle.h"
#include "constantes.h"
#include "jumps.h"

#include <stdbool.h>


/* ************************************************************************** */
/* ========================== ESTRUTURA DE DADOS ============================ */
/* ************************************************************************** */

typedef struct processador_str {
    Flags_ALU flags;
    estado estado_atual;
    Bits_Controle bits_controle;
    Memoria memoria;
    Banco_de_Registradores banco_reg;
    Registrador PC, IR, Dados, A, B, Constantes, Jump, SaidaALU;
} Processador;

/* ************************************************************************** */
/* ================================ FUNÇÃO ================================== */
/* ************************************************************************** */

/* ========================================================================== */

void Executa_Processamento( Processador *processador, bool *screen );

/* ************************************************************************** */

#endif /* __PROCESSADOR_H_INCLUDED__ */
