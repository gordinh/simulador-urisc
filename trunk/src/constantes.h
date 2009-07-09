#ifndef __CONSTANTES_H_INCLUDED__
#define __CONSTANTES_H_INCLUDED__

/*
 * =============================================================================
 *
 *      Arquivo: constantes.h
 *        Autores: Letícia Lana Cherchiglia, Leonardo Vilela Teixeira, Lucas Alves Guerra França
 *        email: letslc@dcc.ufmg.br, vilela@dcc.ufmg.br, lguerra@dcc.ufmg.br
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
void Const_Carrega_Bits_Mais_Significativos( Word *C, bool offset[8], Word temp_C);
void Const_Carrega_Bits_Menos_Significativos( Word *C, bool offset[8], 
        Word temp_C);

void Const_Opera_Formato_III( Word *C, bool *R, bool offset[8], Word temp_C);

/* ================================ FORMATO II ============================== */
void Const_Extende_e_Carrega_Constante( Word *C, bool offset[11]);

/* ========================================================================== */
void Opera_Constantes( Registrador *Destino, bool bit_constante, Word temp_C,
        Registrador IR);

/* ************************************************************************** */

#endif /* __CONSTANTES_H_INCLUDED__ */
