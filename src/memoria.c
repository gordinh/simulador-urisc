/*
 * =============================================================================
 *
 *      Arquivo: memoria.c
 *        Autores: Let�cia Lana Cherchiglia, Leonardo Vilela Teixeira, Lucas Alves Guerra Fran�a
 *        email: letslc@dcc.ufmg.br, vilela@dcc.ufmg.br, lguerra@dcc.ufmg.br
 *
 * =============================================================================
 */

#include "memoria.h"

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
