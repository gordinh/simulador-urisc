/*
 * =============================================================================
 *
 *       Arquivo:  alu.c
 *         Autor:  Leonardo Vilela Teixeira
 *         email:  vilela@dcc.ufmg.br
 *
 * =============================================================================
 */

#include "alu.h"


/* ************************************************************************** */
/* ========================= ARITHMETIC LOGIC UNIT ========================== */
/* ************************************************************************** */

void ALU_add(Word A, Word B, bool Cin, bool * Cout, Word C, bool * Overflow)
{
    int i;
    bool tmp_Cin = Cin;
    bool Cin_sign = false;
    for (i = BITS_ARQ-1 ; i >= 0 ; i--)
    {
        if (i == 0) Cin_sign = tmp_Cin;
        bool tmp_A = A[i];
        bool tmp_B = B[i];
        C[i] = (!tmp_A && tmp_B && !tmp_Cin) || (tmp_A && !tmp_B && !tmp_Cin) 
            || (!tmp_A && !tmp_B && tmp_Cin) || (tmp_A && tmp_B && tmp_Cin);
        tmp_Cin = (tmp_A && tmp_B) || (tmp_B && tmp_Cin) || (tmp_A && tmp_Cin);
    }
    (*Cout) = tmp_Cin;
    *Overflow = (Cin_sign != tmp_Cin);
}

/* ========================================================================== */

void ALU_and(Word A, Word B, Word C)
{
    int i;
    for (i = 0 ; i < BITS_ARQ ; i++)
    {
        C[i] = A[i] && B[i];
    }
}

/* ========================================================================== */

void ALU_or(Word A, Word B, Word C)
{
    int i;
    for (i = 0 ; i < BITS_ARQ ; i++)
    {
        C[i] = A[i] || B[i];
    }
}

/* ========================================================================== */

void ALU_xor(Word A, Word B, Word C)
{
    int i;
    for (i = 0 ; i < BITS_ARQ ; i++)
    {
        C[i] = (A[i] != B[i]);
    }
}

/* ========================================================================== */

void Complemento_de_Dois(Word A, Word Comp)
{
    int i;
    bool inverte = false;
    for ( i = BITS_ARQ-1 ; i>=0 ; i--)
    {
        if ( !inverte )
        {
            Comp[i] = A[i];
            if ( A[i] ) inverte = true;
        }
        else
        {
            Comp[i] = !A[i];
        }
    }
}

/* ========================================================================== */

void ALU_shift_left(Word A, Word C)
{
    int i;
    for (i = 0 ; i < BITS_ARQ-1 ; i++)
    {
        C[i] = A[i+1];
    }
    C[BITS_ARQ-1] = 0;
}

/* ========================================================================== */

void ALU_shift_right(Word A, Word C)
{
    int i;
    for (i = BITS_ARQ-1 ; i > 0 ; i--)
    {
        C[i] = A[i-1];
    }
    C[0] = 0;
}

/* ========================================================================== */

void ALU_shift_left_a(Word A, Word C)
{
    int i;
    for (i = 0 ; i < BITS_ARQ-1 ; i++)
    {
        C[i] = A[i+1];
    }
    C[BITS_ARQ-1] = 0;
}

/* ========================================================================== */

void ALU_shift_right_a(Word A, Word C)
{
    int i;
    for (i = BITS_ARQ-1 ; i > 0 ; i--)
    {
        C[i] = A[i-1];
    }
    C[0] = A[BITS_ARQ-1];
}

/* ========================================================================== */

/*  ALU_controle => Processa a isntrução para gerar os bits de controle da ALU.
 *
 *  bits_controle e ALUop são determinados a partir de equações booleanas 
 *  derivadas a partir de tabela-verdade e minimizadas.
 *
 *  bits_controle indicam operações nos operandos ou resultado, como inversão, 
 *  zerar, negar resultado, etc.
 *  ALUop escolhe uma entre as cinco operações da ALU: AND, OR, XOR, SOMA, e 
 *  os shifts lógicos e aritiméticos para a esquerda e direita
 */
void ALU_controle( bool Op[5], bool opALU, bool bits_controle[7],
        bool ALUop[3] )
{
    /* Operação é definida pelo OP campo da instrução */
    if (opALU)
    {   
        /* Operação da ALU */
        ALUop[0] = (Op[0] && !Op[1] && !Op[2]);
        ALUop[1] = (!Op[0] && !Op[1] && !Op[3] && Op[4]) ||
                   (!Op[0] && !Op[1] && Op[2] && !Op[3]) || 
                   (Op[1] && !Op[2] && Op[3] && Op[4])   ||
                   (Op[0] && Op[1] && !Op[3]) || 
                   (Op[0] && !Op[2] && Op[4]) || (Op[0] && Op[1] && !Op[2]);
        ALUop[2] = (!Op[0] && !Op[1] && Op[2] && Op[3]) || 
                   (Op[0] && !Op[2] && Op[3] && !Op[4]) || 
                   (Op[0] && !Op[2] && !Op[3] && Op[4]) || 
                   (Op[0] && Op[1] && !Op[3]) || (Op[0] && Op[1] && !Op[2]);

        /* Bits de controle da manipulação da ALU */
        bits_controle[0] = (!Op[0] && Op[1] && !Op[2] && !Op[4]);
        bits_controle[1] = (Op[1] && !Op[2] && Op[3] && Op[4]) || 
                           (Op[0] && Op[1] && !Op[2] && Op[4]);
        bits_controle[2] = !(Op[0] || Op[1] || Op[2] || Op[3] || Op[4]) || 
                           (Op[0] && Op[1] && Op[2] && !Op[3] && !Op[4]);
        bits_controle[3] = (Op[0] && Op[1] && !Op[2] && Op[3] && Op[4]) || 
                           (Op[0] && Op[1] && Op[2] && !Op[3] && Op[4]);
        bits_controle[4] = (!Op[0] && Op[1] && !Op[2] && !Op[3]) || 
                           (!Op[0] && !Op[2] && !Op[3] && Op[4]);
        bits_controle[5] = (!Op[0] && !Op[1] && Op[2] && Op[4]) || 
                           (!Op[0] && !Op[1] && Op[3] && Op[4]);
        bits_controle[6] = (Op[0] && Op[1] && !Op[2] && Op[3] && !Op[4]) || 
                           (Op[0] && Op[1] && Op[2] && !Op[3] && !Op[4]);
    }

    /* Operação é SOMA */
    else
    {
        ALUop[0] = 0;
        ALUop[1] = 1;
        ALUop[2] = 1;
        bits_controle[0] = 0;
        bits_controle[1] = 0;
        bits_controle[2] = 0;
        bits_controle[3] = 0;
        bits_controle[4] = 0;
        bits_controle[5] = 0;
        bits_controle[6] = 0;
    }
}

/* ========================================================================== */

/* Bits de Controle:
 *     Bit 0: Inverte A;
 *     Bit 1: Inverte B;
 *     Bit 2: Utiliza '0's no lugar de B;
 *     Bit 3: Indica que haverá decremento
 *     Bit 4: Utiliza '1's no lugar de B;
 *     Bit 5: Inverte o resultado final.
 *     Bit 6: Indica que é um incremento.
 *
 * ALUop: 
 *     000 : AND
 *     001 : XOR
 *     010 : OR
 *     011 : ADD
 *     100 : >> (lógico)
 *     101 : << (lógico)
 *     110 : >> (aritmético)
 *     111 : << (aritmético)
 */
void ALU_opera( Word A, Word B, Word C, bool bits_controle[7], bool ALUop[3],
        Flags_ALU * Flags )
{
    /* Word temporárias, utilizadas nos cáculos */ 
    Word temp_A;
    Word temp_B;
    Word temp_C;
    bool Cout = false;
    bool Overflow = false;

    /* Pré-Operações */
    int i;
    for (i = 0 ; i < BITS_ARQ ; i++)
    {
        temp_A[i] = A[i]; temp_B[i] = B[i];
        if (bits_controle[0]) temp_A[i] = !A[i];
        if (bits_controle[1]) temp_B[i] = !B[i];
        if (bits_controle[2]) temp_B[i] = 0;
        if (bits_controle[4]) temp_B[i] = 1;
    }

    /* Checa por subtração => Complemento de Dois */
    if ( bits_controle[1] && !ALUop[0] && ALUop[1] && ALUop[2] )
        Complemento_de_Dois(B, temp_B);

    /* Escolhe a operação e a executa */
    if (!ALUop[0] && !ALUop[1] && !ALUop[2]) 
        ALU_and(temp_A, temp_B, temp_C);
    else if (!ALUop[0] && !ALUop[1] && ALUop[2]) 
        ALU_xor(temp_A, temp_B, temp_C);
    else if (!ALUop[0] && ALUop[1] && !ALUop[2]) 
        ALU_or(temp_A, temp_B, temp_C);
    else if (!ALUop[0] && ALUop[1] && ALUop[2]) 
    {
        if (bits_controle[6]) 
            ALU_add(temp_A, temp_B, true, &Cout, temp_C, &Overflow);
        else 
            ALU_add(temp_A, temp_B, false, &Cout, temp_C, &Overflow);
    } else if (ALUop[0] && !ALUop[1] && !ALUop[2]) 
        ALU_shift_right(temp_A, temp_C);
    else if (ALUop[0] && !ALUop[1] && ALUop[2]) 
    {
        ALU_shift_left(temp_A, temp_C);
        Cout = A[0];
    }
    else if (ALUop[0] && ALUop[1] && !ALUop[2]) 
        ALU_shift_right_a(temp_A, temp_C);
    else if (ALUop[0] && ALUop[1] && ALUop[2]) 
    {
        ALU_shift_left_a(temp_A, temp_C);
        Cout = A[0];
        Overflow = (A[0] != A[1]);
    }

    /* Pós operações */
    /* Checa Flags e Inverte resultado, se necessário */
    Word Menos_Um = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    if (bits_controle[3]) 
    {
        bool Novo_Overflow;
        ALU_add(temp_C, Menos_Um, false, &Cout, C, &Novo_Overflow );
        Overflow = Overflow || Novo_Overflow;
    }
    for (i = 0 ; i < BITS_ARQ ; i++)
    {
        C[i] = !C[i];
        if (C[i] == true) Flags->zero = 0;
    }
    if ( C[0] == true) Flags->neg = true;
    Flags->negzero = Flags->neg || Flags->zero;
    Flags->carry = Cout;
    Flags->f_true = !Flags->zero;
    Flags->overflow = Overflow;
}

/* ========================================================================== */

/* ************************************************************************** */
