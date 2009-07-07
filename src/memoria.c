/*
 *
 *      Arquivo: memoria.c
 *        Autor: Leonardo Vilela Teixeira
 *        email: vilela@dcc.ufmg.br
 *
 */

#include "memoria.h"

/* ************************************************************************** */
/* ============================== REGISTRADOR =============================== */
/* ************************************************************************** */

void Reg_Escreve_Word( Registrador * R, Word W )
{
    int i;
    for (i = 0 ; i < BITS_ARQ ; i++)
        (*R)[i] = W[i];
}

/* ========================================================================== */

void Reg_Le_Word( Registrador R, Word Destino )
{
    int i;
    for (i = 0 ; i < BITS_ARQ ; i++)
        Destino[i] = R[i];

}

/* ************************************************************************** */
/* ========================= BANCO DE REGISTRADORES ========================= */
/* ************************************************************************** */

void B_Reg_Escreve_Word( Banco_de_Registradores * B, bool reg_num[3], Word D )
{
    /* Calcula Endereço */
    int End = 0;
    End += reg_num[0] ? 1 : 0;
    End += reg_num[1] ? 2 : 0;
    End += reg_num[2] ? 4 : 0;

    /* Copia Word */
    int i;
    for (i = 0 ; i < BITS_ARQ ; i++)
        B->Regs[End][i] = D[i];
}

/* ========================================================================== */

void B_Reg_Le_Word( Banco_de_Registradores B, bool reg_num[3], Word Destino )
{
    /* Calcula Endereço */
    int End = 0;
    End += reg_num[0] ? 1 : 0;
    End += reg_num[1] ? 2 : 0;
    End += reg_num[2] ? 4 : 0;

    /* Copia Word */
    int i;
    for (i = 0 ; i < BITS_ARQ ; i++)
    {
       Destino[i] = B.Regs[End][i];
    }

}

/* ************************************************************************** */
/* ================================ MEMÓRIA ================================= */
/* ************************************************************************** */

void Mem_Escreve_Endereco( Memoria * M, Word Endereco, Word Dados )
{
    /* Cálculo do Endereço */
    int i;
    unsigned int End = 0;
    for (i = 0 ; i < BITS_ARQ ; i++)
    {
        End += Endereco[i] << (BITS_ARQ-i-1);
    }

    /* Copia Word */
    for ( i = 0 ; i < BITS_ARQ ; i++)
    {
        M->posicao[End][i] = Dados[i];
    }
}

/* ========================================================================== */

void Mem_Le_Endereco( Memoria M, Word Endereco, Word Destino )
{
    /* Cálculo do Endereço */
    int i;
    unsigned int End = 0;
    for (i = 0 ; i < BITS_ARQ ; i++)
    {
        End += Endereco[i] << (BITS_ARQ-i-1);
    }

    /* Copia a Word */
    for (i = 0 ; i< BITS_ARQ ; i++)
    {
        Destino[i] = M.posicao[End][i];
    }
}

/* ************************************************************************** */
