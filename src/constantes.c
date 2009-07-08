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

/* ************************************************************************************ */
