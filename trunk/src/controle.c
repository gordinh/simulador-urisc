/*
 * =============================================================================
 *
 *       Arquivo:  controle.c
 *         Autores: Let�cia Lana Cherchiglia, Leonardo Vilela Teixeira, Lucas Alves Guerra Fran�a
 *         email: letslc@dcc.ufmg.br, vilela@dcc.ufmg.br, lguerra@dcc.ufmg.br
 *
 * =============================================================================
 */

#include "controle.h"

#include "registradores.h"
#include "jumps.h"

#include <stdio.h>
#include <stdlib.h>

/* ************************************************************************** */
/* ========================== UNIDADE DE CONTROLE =========================== */
/* ************************************************************************** */

void Executa_Ciclo(bool * Halt,
        estado * Atual, Registrador * IR, Bits_Controle * bc,
        Registrador * PC, Registrador * A, Registrador * B, Flags_ALU * Flags,
        Registrador * Const, Registrador * Jump, Registrador * Saida_ALU, 
        Registrador * Dados, Memoria * Mem, Banco_de_Registradores * B_Reg)
{
    /* Decodifica Instrução */
    Word Inst;
    Word Halt_Inst = {0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1};
    Reg_Le_Word( *IR, Inst );
    bool NOP = true;
    *Halt = true;
    /* Verifica se é Halt ou NOP*/
    int i;
    for (i = 0 ; i < BITS_ARQ ; i++)
    {
        if (Inst[i] != 0) NOP = false;
        if (Inst[i] != Halt_Inst[i]) *Halt = false;
    }
    if ( *Halt ) return;
    if ( NOP )
    {
        *Atual = IF;
    }
    /* Estado comum: IF */
    else if (*Atual == IF)
    {
        Instruction_Fetch( *Mem, PC, IR);
        *Atual = ID;
    }
    /* Estado comum: ID */
    else if (*Atual == ID)
    {
        Instruction_Decode(*B_Reg, *IR, A, B, Jump);
        *Atual = EXE_MEM;
    }
    /* Estado: EXE/MEM */
    else if (*Atual == EXE_MEM)
    {
        /* Instrução: Jump */
        if ( !Inst[0] && !Inst [1] )
        {
            bc->EscrevePC = 1;
            bc->LeMem = 0;
            bc->EscreveMem = 0;
            bc->SalvaFlags = 0;
            bc->EscreveReg = 0;
            bc->OrigAALU = 0;
            bc->OrigBALU[0] = 1;
            bc->OrigBALU[1] = 0;
            bc->OpAlu = 0; 
            *Atual = WB;
        }
        /* Instruções: ALU e Memoria */
        else if ( !Inst[0] && Inst[1] )
        {
            /* Load */
            if ( Inst[5] && !Inst[6] && Inst[7] && !Inst [8] && !Inst[9] )
            {
                bc->EscreveReg = 0;
                bc->LeMem = 1;
                bc->EscreveMem = 0;
                bc->SalvaFlags = 0;
                bc->EscreveReg = 1;
                bc->OrigDadosEscrita[0] = 0;
                bc->OrigDadosEscrita[1] = 1;
                *Atual = WB;
            }
            /* Store */
            else if ( Inst[5] && !Inst[6] && Inst[7] && Inst[8] && !Inst[9] )
            {
                bc->EscrevePC = 0;
                bc->LeMem = 0;
                bc->EscreveMem = 1;
                bc->OrigDadosEscrita[0] = 0;
                bc->OrigDadosEscrita[1] = 1;
                bc->SalvaFlags = 0;
                bc->EscreveReg = 0;
                *Atual = IF;
            }
            /* ALU */
            else 
            {
                bc->EscrevePC = 0;
                bc->LeMem = 0;
                bc->EscreveMem = 0;
                bc->OrigDadosEscrita[0] = 1;
                bc->OrigDadosEscrita[1] = 0;
                bc->SalvaFlags = 1;
                bc->EscreveReg = 1;
                bc->OrigAALU = 1;
                bc->OrigBALU[0] = 0;
                bc->OrigBALU[1] = 0;
                bc->OpAlu = 1;
                *Atual = WB;
            }
        }
        /* Constante */
        else 
        {
            bc->EscrevePC = 0;
            bc->LeMem = 0;
            bc->EscreveMem = 0;
            bc->OrigDadosEscrita[0] = 0;
            bc->OrigDadosEscrita[1] = 0;
            /* Tipo 2 ou Tipo 3 */
            if (Inst[1])
                bc->Constante = 1;
            else
                bc->Constante = 0;
            bc->SalvaFlags = 0;
            bc->EscreveReg = 1;
            *Atual = WB;
        }

        Execute_and_Memory(Mem, *bc, *A, *B, *Jump, Saida_ALU, Dados, 
                Const, *IR, *PC, Flags, *B_Reg);
    }
    /* Write Back */
    else if (*Atual == WB)
    {
        Write_Back(B_Reg, *Const, PC, *Saida_ALU, *B, *bc, *IR, *Dados, *Flags);
        *Atual = IF;
    }

}

/* ========================================================================== */

/* 
 *  Instruction Fetch:
 *
 *  Busca a próxima instrução no PC e a 
 *  grava no IR (Registrador de Instrução). Incrementa PC;
 */
void Instruction_Fetch(Memoria  Mem, Registrador * PC, Registrador * IR)
{
    /* Lê a instrução e armazena no IR */
    Word End_Instrucao;
    Word Instrucao;
    Reg_Le_Word( *PC , End_Instrucao );
    Mem_Le_Endereco(Mem, End_Instrucao, Instrucao);
    Reg_Escreve_Word( IR, Instrucao );

    /* Incrementa PC */
    Word Nova_Instrucao;
    Word Um = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
    bool bits_controle[7];
    bool ALUop[3];
    Flags_ALU tmp_Flags;
    ALU_controle(NULL, false, bits_controle, ALUop);
    ALU_opera(End_Instrucao, Um, Nova_Instrucao, 
            bits_controle, ALUop, &tmp_Flags);

    /* Escreve novo PC */
    Reg_Escreve_Word( PC, Nova_Instrucao );
}

/* ========================================================================== */

/*
 *  Instrucion Decode 
 *
 *  Decodifica a instrução, lê o conteúdo dos registradores.
 */
void Instruction_Decode( Banco_de_Registradores B_Reg, Registrador IR, 
        Registrador * A, Registrador * B, Registrador * Temp )
{
    /* Lê instrução */
    Word Inst;
    Reg_Le_Word(IR, Inst);

    /* Decodifica endereço e lê registrador */
    bool end_A[3] = { Inst[BITS_ARQ-6], Inst[BITS_ARQ-5], Inst[BITS_ARQ-4] };
    bool end_B[3] = { Inst[BITS_ARQ-3], Inst[BITS_ARQ-2], Inst[BITS_ARQ-1]};
    Word Valor_A, Valor_B;
    B_Reg_Le_Word( B_Reg, end_A, Valor_A );
    B_Reg_Le_Word( B_Reg, end_B, Valor_B );

    /* Extensão de Sinal dos offsets de Jumps */
    Word TempWord;
    Jump_Extende_Sinal_Offset_Desvio( &TempWord, IR );
    Reg_Escreve_Word( Temp, TempWord );

    /* Armazena valores nos registradores auxiliares */
    Reg_Escreve_Word(A, Valor_A);
    Reg_Escreve_Word(B, Valor_B);
}

/* ========================================================================== */

/* 
 *  Execute And Memory:
 *
 *  A partir dos bits de controle ativados, 
 *  executa e opera na memória.
 */
void Execute_and_Memory( Memoria * Mem, Bits_Controle bc, Registrador A, 
        Registrador B, Registrador Temp, Registrador * Saida_ALU,
        Registrador * Reg_Dados, Registrador * C, Registrador IR,
        Registrador PC, Flags_ALU * flags, Banco_de_Registradores BR )
{
    /* LêMem => Lê da memória */
    if (bc.LeMem)
    {
        /* Pega Endereço */
        Word End;
        Reg_Le_Word(A, End);

        /* Lê Dados */
        Word Dados;
        Mem_Le_Endereco(*Mem, End, Dados);

        /* Armazena no registrador de dados */
        Reg_Escreve_Word(Reg_Dados, Dados);
    }

    /* EscreveMem => Escreve na memória */
    if (bc.EscreveMem)
    {
        /* Pega endereço */
        Word End;
        Reg_Le_Word(A, End);
        
        /* Escreve Dados */
        Word Dados;
        Reg_Le_Word(B, Dados);
        Mem_Escreve_Endereco(Mem, End, Dados);

    }

    /* Constante => Cria a constante e armazena em C */
    Word Const_C;
    bool reg_num[3] = {IR[2], IR[3], IR[4]};
    B_Reg_Le_Word(BR, reg_num, Const_C);
    Opera_Constantes( C, bc.Constante, Const_C, IR);

    /* ALU => Realiza operações */
    bool bc_ALU[7];
    bool ALUop[3];
    Word tmp_A, tmp_B, tmp_C;

    /* Obtem entradas da ALU */
    if (bc.OrigAALU) Reg_Le_Word(A, tmp_A);
    else Reg_Le_Word(PC, tmp_A);

    /* Origem B => B */
    if (!bc.OrigBALU[0] && !bc.OrigBALU[1]) Reg_Le_Word(B, tmp_B);
    /* Origem B => Temp (Jump) */
    else if (bc.OrigBALU[0] && !bc.OrigBALU[1] ) Reg_Le_Word(Temp, tmp_B);
    /* Origem B => 1 */
    else
    {
        int i;
        for (i = 0 ; i < BITS_ARQ ; i++) tmp_B[i] = 0;
        tmp_B[BITS_ARQ-1] = 1;
    }

    /* Obtém Opcode */
    Word Inst;
    Reg_Le_Word(IR, Inst);
    bool Opcode[5] = { Inst[5], Inst[6], Inst[7], Inst[8], Inst[9] };

    /* ALU Controle => gera bits de controle da ALU */
    /* ALU opera => Opera e armazena resultado em temp_C */
    ALU_controle(Opcode, bc.OpAlu, bc_ALU, ALUop);
    Flags_ALU tmp_flags;
    if (bc.SalvaFlags)
        ALU_opera( tmp_A, tmp_B, tmp_C, bc_ALU, ALUop, flags  );
    else
        ALU_opera( tmp_A, tmp_B, tmp_C, bc_ALU, ALUop, &tmp_flags  );

    /* Salva resultado da ALU */
    Reg_Escreve_Word(Saida_ALU, tmp_C);
/*    int i;
    for (i = 0 ; i < 16 ; i++)
        printf("%d",tmp_B[i]);
    printf("\n");*/
}

/* ========================================================================== */

/*
 *  Write Back
 *
 *  Escreve resultado das operações nos registradores correspondentes.
 */
void Write_Back(Banco_de_Registradores * BReg, Registrador Temp, 
        Registrador * PC, Registrador Saida_ALU, Registrador B,
        Bits_Controle bc, Registrador IR, Registrador Dados, Flags_ALU Flags)
{
    /* Atualiza PC */
    if (bc.EscrevePC)
    {
        Word Novo_PC;
        Jump_Calcula_Endereco_Desvio ( &Novo_PC, B, Saida_ALU, PC, IR,
                BReg, &Flags );
        Reg_Escreve_Word(PC, Novo_PC);
    }

    /* Escreve no Registrador */
    if (bc.EscreveReg)
    {
        /* Lê endereço de Escrita */
        Word Inst;
        Reg_Le_Word(IR, Inst);
        bool End[3] = {Inst[2], Inst[3], Inst[4]};

        Word Valor;
        /* Origem 0 => Constante */
        if ( !bc.OrigDadosEscrita[0] && !bc.OrigDadosEscrita[1]  ) 
        {
            Reg_Le_Word(Temp, Valor);
        /* Origem 1 => Memória */
        } else if ( !bc.OrigDadosEscrita[0] && bc.OrigDadosEscrita[1] )
        {
            Reg_Le_Word(Dados, Valor);
        /* Origem 2 => ALU */
        } else if ( bc.OrigDadosEscrita[0] && !bc.OrigDadosEscrita[1] )
        {
            Reg_Le_Word(Saida_ALU, Valor);
        }
        B_Reg_Escreve_Word(BReg, End, Valor);

    }
}

/* ************************************************************************** */
