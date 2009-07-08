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

typedef struct bc_str
{
    bool EscrevePC;
    bool LeMem;
    bool EscreveMem;
    bool OrigDadosEscrita;
    bool EscreveIR;
    bool OrigPC;
    bool IouD;
    bool Constante;
    bool Jumper;
    bool EscreveReg;
    bool OrigAALU;
    bool OrigBALU[2];
    bool OpAlu;
} Bits_Controle;

/* ************************************************************************** */
/* ================================ FUNÇÕES ================================= */
/* ************************************************************************** */

void Instruction_Fetch(Memoria Mem, Registrador * PC, Registrador * IR, 
        Flags_ALU * Flags);
void Instruction_Decode( Banco_de_Registradores B_Reg, Registrador IR, 
        Registrador * A, Registrador * B );
void Execute_and_Memory( Memoria * Mem, Bits_Controle bc, Registrador A, 
        Registrador B, Registrador Temp, Registrador * Saida_ALU,
        Registrador * Reg_Dados, Registrador * C, Registrador IR );
void Write_Back();

/* ************************************************************************** */

#endif /* __CONTROLE_H_INCLUDED__ */
