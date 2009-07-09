/*
 * =======================================================================================
 *
 *      Arquivo: processador.c
 *        Autor: Lucas Alves Guerra França
 *        email: lguerra@dcc.ufmg.br
 *
 * =======================================================================================
 */

#include "processador.h"

/* ************************************************************************************ */
/* ============================== PROCESSADOR ========================================= */
/* ************************************************************************************ */

/* ==================================================================================== */

void Executa_Processamento( Processador *processador )
{
    int i;
    //Zera o registrador PC.
    for (i = 0 ; i < BITS_ARQ; i++)
        processador->PC[i] = 0;

    //Declara o estado atual como sendo o estado 'Instruction Fetch'.
    processador->estado_atual = IF;
    
    bool Halt = false;
    while(!Halt) {
        Executa_Ciclo(&Halt, &processador->estado_atual, &processador->IR, &processador->bits_controle, &processador->PC, &processador->A, &processador->B, &processador->flags, &processador->Constantes, &processador->Jump, &processador->SaidaALU, &processador->Dados, &processador->memoria, &processador->banco_reg);
    }
}

/* ************************************************************************************ */
