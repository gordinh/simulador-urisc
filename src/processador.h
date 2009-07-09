#ifndef __PROCESSADOR_H_INCLUDED__
#define __PROCESSADOR_H_INCLUDED__

/*
 * =============================================================================
 *
 *      Arquivo: processador.h
 *        Autores: Letícia Lana Cherchiglia, Leonardo Vilela Teixeira, Lucas Alves Guerra França
 *        email: letslc@dcc.ufmg.br, vilela@dcc.ufmg.br, lguerra@dcc.ufmg.br
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
#include "es.h"

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

void Inicializa_Processador( Processador *processador );
void Executa_Processamento( Processador *processador, bool *screen, char** dump_pos_inicial, int *dump_num_palavras );

/* ************************************************************************** */

#endif /* __PROCESSADOR_H_INCLUDED__ */
