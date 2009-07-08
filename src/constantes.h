#ifndef __CONSTANTES_H_INCLUDED__
#define __CONSTANTES_H_INCLUDED__

/*
 * =============================================================================
 *
 *      Arquivo: constantes.h
 *        Autor: Lucas Alves Guerra França
 *        email: lguerra@dcc.ufmg.br
 *
 * =============================================================================
 */

#include "defs.h"
#include "registradores.h"

#include <stdbool.h>


/* ************************************************************************** */
/* ================================ FUNÇÕES ================================= */
/* ************************************************************************** */

/* ================================ FORMATO III ============================= */
void Const_Carrega_Bits_Mais_Significativos( Word *C, bool offset[8]);
void Const_Carrega_Bits_Menos_Significativos( Word *C, bool offset[8]);

void Const_Opera_Formato_III( Word *C, bool *R, bool offset[8]);

/* ================================ FORMATO II ============================== */
void Const_Estende_e_Carrega_Constante( Word *C, bool offset[11]);

/* ========================================================================== */
void Opera_Constantes( Registrador *Destino, bool bit_constante, Registrador IR);

/* ************************************************************************** */

#endif /* __CONSTANTES_H_INCLUDED__ */
