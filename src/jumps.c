/*
 * =======================================================================================
 *
 *      Arquivo: jumps.c
 *        Autores: Letícia Lana Cherchiglia, Leonardo Vilela Teixeira, Lucas Alves Guerra França
 *        email: letslc@dcc.ufmg.br, vilela@dcc.ufmg.br, lguerra@dcc.ufmg.br
 *
 * =======================================================================================
 */

#include "jumps.h"
#include "registradores.h"
#include "alu.h"

/* ************************************************************************************ */
/* ============================== UNIDADE DE DESVIOS (JUMPS) ========================== */
/* ************************************************************************************ */

/* ==================================================================================== */

//Extende o sinal do campo offset presente nas instruções jump condicional e incondicional e coloca
//o offset extendido na word 'ALU_B'. Se a instrução não possui offset(jump and link e jump register),
//a word 'ALU_B' é zerada.
void Jump_Extende_Sinal_Offset_Desvio( Word *ALU_B, Registrador IR )
{
    int i;
    //Se o jump é condicional, de formato IV.
    if( (IR)[2] == 0 ) {

        //Transfere o offset presente no registrador de instrução para a word "ALU_B".
        for(i = BITS_ARQ / 2; i < BITS_ARQ; i++)
            (*ALU_B)[i] = (IR)[i];

        //Extende o sinal do offset.
        for(i = 0; i < BITS_ARQ /2; i ++)
            (*ALU_B)[i] = (*ALU_B)[BITS_ARQ / 2];
    }
    else {

        //Se o jump é incondicional, de formato V.
        if( (IR)[3] == 0 ) {

            //Transfere o offset presente no registrador de instrução para a word "ALU_B".     
            for(i = BITS_ARQ - 12; i < BITS_ARQ; i++)
                (*ALU_B)[i] = (IR)[i];

            //Extende o sinal do offset.
            for(i = 0; i < BITS_ARQ - 12; i++)
                (*ALU_B)[i] = (*ALU_B)[BITS_ARQ - 12];
        }
        
        //Se o jump é 'jump and link' ou 'jump register'(ambos de formato VI), a word 'ALU_B' é definida como sendo zero.
        else {
            for(i = 0; i < BITS_ARQ; i++)
              (*ALU_B)[i] = 0;
        }
    }
}

/* ============================== FORMATO V =========================================== */

//Coloca o endereço de destino do desvio incondicional(presente no registrador 'B') na word 'end_destino'.
void Jump_Incondicional( Word *end_destino, Registrador B )
{
    int i;
    for (i = 0 ; i < BITS_ARQ; i++)
        (*end_destino)[i] = (B)[i];
}

/* ============================== FORMATO IV ========================================== */

void Jump_Condicional_True( Word *end_destino, Registrador SaidaALU, Flags_ALU *flags, Registrador *PC, Registrador IR )
{
    int i;
    bool condicao_satisfeita = false;
    // Checa qual é a condição da instrução de desvio e se ela é verdadeira.
    //Checa se a condição é o resultado da ALU ser diferente de zero (representada pela flag 'f_true').
    if( ((IR)[5] == 0) && ((IR)[6] == 0) ) {
        if(flags->f_true == true)
            condicao_satisfeita = true;
    }
    else {
        //Checa se a condição é o resultado da ALU ter sofrido overflow (representada pela flag 'overflow').
        if((IR)[5] == 0) {
            if(flags->overflow == true)
                condicao_satisfeita = true;              
        }
        else {
            //Checa se a condição é o resultado da ALU ser negativo (representada pela flag 'neg').
            if( ((IR)[6] == 0) && ((IR)[7] == 0) ) {
                if(flags->neg == true)
                    condicao_satisfeita = true;
            }
            else {
                //Checa se a condição é o resultado da ALU ser igual a zero (representada pela flag 'zero').
                if((IR)[6] == 0) {
                    if(flags->zero == true)
                        condicao_satisfeita = true;
                }
                else {
                    //Checa se a condição é o resultado da ALU ter tido carry (representada pela flag 'carry').
                    if((IR)[7] == 0) {
                        if(flags->carry == true)
                            condicao_satisfeita = true;
                    }
                    else {
                        //Checa se a condição é o resultado da ALU ser negativo ou igual a zero (representada pela flag 'negzero').
                        if(flags->negzero == true)
                            condicao_satisfeita = true;
                    }
                }
            }
        }
    }
    //Se a condição de desvio for verdadeira, coloca o endereço presente no registrador 'SaidaALU' na word 'end_destino'.
    if(condicao_satisfeita == true)
        for(i = 0; i < BITS_ARQ; i++)
            (*end_destino)[i] = (SaidaALU)[i];
    //Se a condição de desvio for falsa, coloca o endereço presente no registrador 'PC' na word 'end_destino'.
    else
        for(i = 0; i < BITS_ARQ; i++)
            (*end_destino)[i] = (*PC)[i];
}

/* ====================================================================================== */

void Jump_Condicional_False( Word *end_destino, Registrador SaidaALU, Flags_ALU *flags, Registrador *PC, Registrador IR )
{
    int i;
    bool condicao_satisfeita = false;
    // Checa qual é a condição da instrução de desvio e se ela é verdadeira.
    //Checa se a condição é o resultado da ALU não ser diferente de zero (representada pela flag 'f_true').
    if( ((IR)[5] == 0) && ((IR)[6] == 0) ) {
        if(flags->f_true == false)
            condicao_satisfeita = true;
    }
    else {
        //Checa se a condição é o resultado da ALU não ter sofrido overflow (representada pela flag 'overflow').
        if((IR)[5] == 0) {
            if(flags->overflow == false)
                condicao_satisfeita = true;              
        }
        else {
            //Checa se a condição é o resultado da ALU não ser negativo (representada pela flag 'neg').
            if( ((IR)[6] == 0) && ((IR)[7] == 0) ) {
                if(flags->neg == false)
                    condicao_satisfeita = true;
            }
            else {
                //Checa se a condição é o resultado da ALU não ser igual a zero (representada pela flag 'zero').
                if((IR)[6] == 0) {
                    if(flags->zero == false)
                        condicao_satisfeita = true;
                }
                else {
                    //Checa se a condição é o resultado da ALU não ter tido carry (representada pela flag 'carry').
                    if((IR)[7] == 0) {
                        if(flags->carry == false)
                            condicao_satisfeita = true;
                    }
                    else {
                        //Checa se a condição é o resultado da ALU não ser negativo ou igual a zero (representada pela flag 'negzero').
                        if(flags->negzero == false)
                            condicao_satisfeita = true;
                    }
                }
            }
        }
    }
    //Se a condição de desvio for satisfeita, coloca o endereço presente no registrador 'SaidaALU' na word 'end_destino'.
    if(condicao_satisfeita == true)
        for(i = 0; i < BITS_ARQ; i++)
            (*end_destino)[i] = (SaidaALU)[i];
    //Se a condição de desvio não for satisfeita, coloca o endereço presente no registrador 'PC' na word 'end_destino'.
    else
        for(i = 0; i < BITS_ARQ; i++)
            (*end_destino)[i] = (*PC)[i];
}

/* ============================== FORMATO VI ========================================== */

void Jump_and_Link( Word *end_destino, Registrador B, Registrador *PC, Banco_de_Registradores *Breg )
{
    int i;
    //Coloca o endereço de destino do desvio (presente no registrador 'B') na word 'end_destino'.
    for (i = 0 ; i < BITS_ARQ; i++)
        (*end_destino)[i] = (B)[i];

    Word posicao_atual;
    for (i = 0 ; i < BITS_ARQ; i++)
        posicao_atual[i] = (*PC)[i];
    
    bool reg_num[3];
    for(i = 0; i < 3; i++)
        reg_num[i] = 1;

    //Escreve o endereço presente no registrador 'PC' no registrador 7 do banco de registradores.
    B_Reg_Escreve_Word( Breg, reg_num, posicao_atual);
}

/* ====================================================================================== */

void Jump_Register( Word *end_destino, Registrador B )
{
    int i;
    for (i = 0 ; i < BITS_ARQ; i++)
        (*end_destino)[i] = (B)[i];
}

/* ====================================================================================== */

void Jump_Calcula_Endereco_Desvio ( Word *end_destino, Registrador B, Registrador SaidaALU, Registrador *PC, Registrador IR, Banco_de_Registradores *Breg, Flags_ALU *flags )
{
    //Se o jump é condicional.
    if( (IR)[2] == 0 ) {
        //Se o jump é condicional false.
        if( (IR)[3] == 0 )
            Jump_Condicional_False(end_destino, SaidaALU, flags, PC, IR);
        //Se o jump é condicional true.
        else
            Jump_Condicional_True(end_destino, SaidaALU, flags, PC, IR);
    }
    else {
        //Se o jump é incondicional.
        if( (IR)[3] == 0 )
            Jump_Incondicional(end_destino, B);
        else {
            //Se o jump é 'jump and link'.
            if( (IR)[4] == 0 )
                Jump_and_Link(end_destino, B, PC, Breg);
            //Se o jump é 'jump register'.
            else
                Jump_Register(end_destino, B);
        }
    }
}
    
/* ************************************************************************************ */
