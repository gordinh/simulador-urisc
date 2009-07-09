#ifndef __CONTROLE_H_INCLUDED__
#define __CONTROLE_H_INCLUDED__
/*
 * =============================================================================
 *
 *       Arquivo:  controle.h
 *         Autor:  Leonardo Vilela Teixeira
 *         email:  vilela@dcc.ufmg.br
 *
 * =============================================================================
 */

#include "defs.h"
#include "constantes.h"
#include "registradores.h"
#include "memoria.h"
#include "alu.h"

/* ************************************************************************** */
/* ========================== ESTRUTURAS DE DADOS =========================== */
/* ************************************************************************** */

typedef enum
{
    IF,
    ID,
    EXE_MEM,
    WB
} estado;

/* ========================================================================== */

typedef struct bc_str
{
    bool EscrevePC;
    bool LeMem;
    bool EscreveMem;
    bool OrigDadosEscrita[2];
    bool Constante;
    bool SalvaFlags;
    bool EscreveReg;
    bool OrigAALU;
    bool OrigBALU[2];
    bool OpAlu;
} Bits_Controle;

/* ************************************************************************** */
/* ================================ FUNÇÕES ================================= */
/* ************************************************************************** */
/*
void Clock(bool * Halt, estado * Estado_Atual, Memoria * Mem, 
        Banco_de_Registradores);
*/


void Instruction_Fetch(Memoria Mem, Registrador * PC, Registrador * IR);
void Instruction_Decode( Banco_de_Registradores B_Reg, Registrador IR, 
        Registrador * A, Registrador * B, Registrador Temp );
void Execute_and_Memory( Memoria * Mem, Bits_Controle bc, Registrador A, 
        Registrador B, Registrador Temp, Registrador * Saida_ALU,
        Registrador * Reg_Dados, Registrador * C, Registrador IR,
        Registrador PC, Flags_ALU * flags );
void Write_Back(Banco_de_Registradores * BReg, Registrador Temp, 
        Registrador * PC, Registrador Saida_ALU, Registrador B, 
        Bits_Controle bc, Registrador IR, Registrador Dados, Flags_ALU Flags);

/* ************************************************************************** */

#endif /* __CONTROLE_H_INCLUDED__ */
