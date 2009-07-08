/*
 * =============================================================================
 *
 *       Arquivo:  controle.c
 *         Autor:  Leonardo Vilela Teixeira
 *         email:  vilela@dcc.ufmg.br
 *
 * =============================================================================
 */

#include "controle.h"
#include "registradores.h"

#include <stdlib.h>

/* ************************************************************************** */
/* ========================== UNIDADE DE CONTROLE =========================== */
/* ************************************************************************** */


/* 
 *  Instruction Fetch:
 *
 *  Busca a próxima instrução no PC e a 
 *  grava no IR (Registrador de Instrução). Incrementa PC;
 */

void Instruction_Fetch(Registrador * PC, Registrador * IR, Flags_ALU * Flags)
{
    /* Lê a instrução e armazena no IR */
    Word Instrucao;
    Reg_Le_Word( *PC , Instrucao );
    Reg_Escreve_Word( IR, Instrucao );

    /* Incrementa PC */
    Word Nova_Instrucao;
    bool bits_controle[7];
    bool ALUop[3];
    ALU_controle(NULL, false, bits_controle, ALUop);
    ALU_opera(Instrucao, Instrucao, Nova_Instrucao, 
            bits_controle, ALUop, Flags);

    /* Escreve novo PC */
    Reg_Escreve_Word( PC, Nova_Instrucao );

}

/* ========================================================================== */

/*
 *  Instrucion Decode 
 *
 *  Decodifica a instrução, lê o conteúdo dos registradores.
 */
void Instruction_Decode( Banco_de_Registradores B_Reg, Registrador IR, 
        Registrador * A, Registrador * B )
{
    /* Lê instrução */
    Word Inst;
    Reg_Le_Word(IR, Inst);

    /* Decodifica endereço e lê registrador */
    bool end_A[3] = { Inst[0], Inst[0], Inst[0] };
    bool end_B[3] = {};
    Word Valor_A, Valor_B;
    B_Reg_Le_Word( B_Reg, end_A, Valor_A );
    B_Reg_Le_Word( B_Reg, end_B, Valor_B );

    /* Armazena valores nos registradores auxiliares */
    Reg_Escreve_Word(A, Valor_A);
    Reg_Escreve_Word(B, Valor_B);
}

/* ========================================================================== */

/* 
 *  Execute And Memory:
 *
 *  A partir dos bits de controle ativados, 
 *  executa e opera na memória.
 */
void Execute_and_Memory( Bits_Controle bc, Registrador A, Registrador B )
{

}

/* ************************************************************************** */
