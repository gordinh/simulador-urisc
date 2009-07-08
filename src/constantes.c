/*
 * =======================================================================================
 *
 *      Arquivo: constantes.c
 *        Autor: Lucas Alves Guerra França
 *        email: lguerra@dcc.ufmg.br
 *
 * =======================================================================================
 */

#include "constantes.h"
#include "registradores.h"

/* ************************************************************************************ */
/* ============================== UNIDADE DE CONSTANTES =============================== */
/* ************************************************************************************ */

/* ============================== FORMATO III ========================================= */

void Const_Carrega_Bits_Mais_Significativos( Word *C, bool offset[8])
{
    int i;
    for (i = 0 ; i < BITS_ARQ / 2 ; i++)
        (*C)[i] = offset[i];
    for (i = BITS_ARQ / 2; i < BITS_ARQ; i++)
        (*C)[i] = 0;
}

/* ===================================================================================== */

void Const_Carrega_Bits_Menos_Significativos( Word *C, bool offset[8])
{
    int i;
    for (i = 0 ; i < BITS_ARQ / 2 ; i++)
        (*C)[i] = 0;
    for (i = BITS_ARQ / 2; i < BITS_ARQ; i++)
        (*C)[i] = offset[i - (BITS_ARQ / 2)];
}

/* ===================================================================================== */

void Const_Opera_Formato_III( Word *C, bool *R, bool offset[8])
{
    /* Checa o valor do bit R para decidir se carrega a constante nos bits mais ou menos significativos */
    if ( (*R) == 0 )
      Const_Carrega_Bits_Menos_Significativos(C, offset);
    else
      Const_Carrega_Bits_Mais_Significativos(C, offset);

}

/* ============================== FORMATO II =========================================== */

void Const_Estende_e_Carrega_Constante( Word *C, bool offset[11])
{
    int i;
    for (i = 0 ; i < BITS_ARQ - 11 ; i++)
        (*C)[i] = offset[0];
    for (i = BITS_ARQ - 11; i < BITS_ARQ; i++)
        (*C)[i] = offset[i - (BITS_ARQ - 11)];
}

/* ===================================================================================== */

void Opera_Constantes( Registrador *Destino, bool bit_constante, Registrador *IR)
{
    int i;
    Word instrucao;
    Reg_Le_Word( *IR, instrucao);
    //Se a instrução é do tipo II.
    if( bit_constante == 0 ) {
        bool offset[11];
        for(i = 0; i < 11; i++)
            offset[i] = instrucao[(BITS_ARQ - 11) + i];

        Word temp;
        Const_Estende_e_Carrega_Constante( &temp, offset );
        //Escreve a constante no registrador temporário.
        Reg_Escreve_Word(Destino, temp);
    }

    //Se a instrução é do tipo III.
    else {
        bool R = instrucao[5];
        bool offset[8];
        for(i = 0; i < 8; i++)
            offset[i] = instrucao[(BITS_ARQ - 8) + i];

        Word temp;
        Const_Opera_Formato_III( &temp, &R, offset );
        //Escreve a constante no registrador temporário.
        Reg_Escreve_Word(Destino, temp);
    }
}
/* ************************************************************************************ */
