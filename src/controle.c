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

void Instruction_Fetch(Memoria Mem, Registrador * PC, Registrador * IR, 
        Flags_ALU * Flags)
{
    /* Lê a instrução e armazena no IR */
    Word End_Instrucao;
    Word Instrucao;
    Reg_Le_Word( *PC , End_Instrucao );
    Mem_Le_Endereco(Mem, End_Instrucao, Instrucao);
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
    bool end_A[3] = { Inst[BITS_ARQ-6], Inst[BITS_ARQ-5], Inst[BITS_ARQ-4] };
    bool end_B[3] = { Inst[BITS_ARQ-3], Inst[BITS_ARQ-2], Inst[BITS_ARQ-1]};
    Word Valor_A, Valor_B;
    B_Reg_Le_Word( B_Reg, end_A, Valor_A );
    B_Reg_Le_Word( B_Reg, end_B, Valor_B );

    /* Extensão de Sinal dos offsets de Jumps */
    /* AQUI */

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
void Execute_and_Memory( Memoria * Mem, Bits_Controle bc, Registrador A, 
        Registrador B, Registrador * Saida_ALU, Registrador * Reg_Dados, 
        Registrador * C )
{
    /* LêMem => Lê da memória */
    if (bc.LeMem)
    {
        /* Pega Endereço */
        Word End;
        Reg_Le_Word(A, End);

        /* Lê Dados */
        Word Dados;
        Mem_Le_Endereco(*Mem, End, Dados);

        /* Armazena no registrador de dados */
        Reg_Escreve_Word(Reg_Dados, Dados);
    }

    /* EscreveMem => Escreve na memória */
    if (bc.EscreveMem)
    {
        /* Pega endereço */
        Word End;
        Reg_Le_Word(A, End);
        
        /* Escreve Dados */
        Word Dados;
        Reg_Le_Word(B, Dados);
        Mem_Escreve_Endereco(Mem, End, Dados);
    }
}

/* ************************************************************************** */
