/*
 * =======================================================================================
 *
 *      Arquivo: processador.c
 *        Autores: Letícia Lana Cherchiglia, Leonardo Vilela Teixeira, Lucas Alves Guerra França
 *        email: letslc@dcc.ufmg.br, vilela@dcc.ufmg.br, lguerra@dcc.ufmg.br
 *
 * =======================================================================================
 */

#include "processador.h"

/* ************************************************************************************ */
/* ============================== PROCESSADOR ========================================= */
/* ************************************************************************************ */

/* ==================================================================================== */

void Inicializa_Processador( Processador *processador )
{
    int i;
    //Zera o registrador PC e faz o registrador IR = 1.
    for (i = 0 ; i < BITS_ARQ - 1; i++) {
        processador->PC[i] = 0;
        processador->IR[i] = 0;
    }
    processador->PC[BITS_ARQ - 1] = 0;
    processador->IR[BITS_ARQ - 1] = 1;
}

/* ==================================================================================== */

void Executa_Processamento( Processador *processador, bool *screen, char** dump_pos_inicial, int *dump_num_palavras )
{

    //Declara o estado atual como sendo o estado 'Instruction Fetch'.
    processador->estado_atual = IF;
    
    Word aux;
    bool Halt = false;
    while(!Halt) {
        if(*screen == true)
            Reg_Le_Word(processador->PC, aux);

        Executa_Ciclo(&Halt, &processador->estado_atual, &processador->IR, &processador->bits_controle, &processador->PC, &processador->A, &processador->B, &processador->flags, &processador->Constantes, &processador->Jump, &processador->SaidaALU, &processador->Dados, &processador->memoria, &processador->banco_reg);

        if(*screen == true)
            Imprime_Status_Processador( &processador->banco_reg, &processador->PC, &processador->IR, &processador->flags, &aux);
    }
    //Imprime as 'dump_num_palavras' words a partir da posição 'dump_pos_inicial' da memória.
    es_Imprime_Pedido_de_Dump( &processador->memoria, dump_pos_inicial, dump_num_palavras );
}

/* ************************************************************************************ */
