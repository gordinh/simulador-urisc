#ifndef __ES_H_INCLUDED__
#define __ES_H_INCLUDED__

/*
 * =============================================================================
 *
 *      Arquivo: es.h
 *        Autor: Lucas Alves Guerra França
 *        email: lguerra@dcc.ufmg.br
 *
 * =============================================================================
 */

#include "defs.h"
#include "memoria.h"

#include <stdbool.h>
#include <stdio.h>


/* ************************************************************************** */
/* ================================ FUNÇÕES ================================= */
/* ************************************************************************** */

void es_abre_Arquivo_para_Leitura( FILE **arquivo, char* nome_arquivo );
void es_Inicializa_Variaveis_Parametros_Execucao( int *argc, char ***argv, char** nome_arq_entrada, char** dump_pos_inicial, int *num_palavras, bool *screen, bool *pausa );

void es_Le_Arquivo_Armazena_Instrucoes_Memoria( FILE **entrada, Memoria *M );
void es_Imprime_Pedido_de_Dump( Memoria *M, char** endereco_hexadecimal, int *num_words );
void es_Imprime_Status_Processador( Banco_de_Registradores *Banco, Registrador *PC, Registrador *IR, Flags_ALU *flags, Word *Instrucao_Executada);

/* ========================================================================== */

void es_Transforma_Hexadecimal_em_Binario( Word *forma_binaria, char** forma_hexadecimal );
void es_Transforma_Binario_em_Hexadecimal( Word *forma_binaria, char** forma_hexadecimal );
void es_Incrementa_Endereco_em_Word( Word *endereco );

/* ************************************************************************** */

#endif /* __ES_H_INCLUDED__ */
