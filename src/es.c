/*
 * =======================================================================================
 *
 *      Arquivo: es.c
 *        Autor: Lucas Alves Guerra França
 *        email: lguerra@dcc.ufmg.br
 *
 * =======================================================================================
 */

#include "es.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ****************************************************************************** */
/* ============================== ENTRADA E SAÍDA =============================== */
/* ****************************************************************************** */

/* ==================================================================================== */

void es_abre_Arquivo_para_Leitura( FILE **arquivo, char* nome_arquivo )
{
    *arquivo = fopen(nome_arquivo, "r");
}

/* ===================================================================================== */

void es_Inicializa_Variaveis_Parametros_Execucao( int *argc, char ***argv, char** nome_arq_entrada, char** dump_pos_inicial, int *num_palavras, bool *screen, bool *pausa )
{
    int opt = 0;

    opt = getopt( *argc, *argv, "e:d:n:s:p:");
    while (opt  != -1) {
        switch (opt) {
            case 'e':
                *nome_arq_entrada = optarg;
                break;
            case 'd':
                *dump_pos_inicial = optarg;
                break;
            case 'n':
                *num_palavras = atoi(optarg);
                break;
            case 's':
                *screen = true;
                break;
            case 'p':
                *pausa = true;
                break;
            default:
                printf( "Uso de parametro invalido" );
                exit(1);
        }
        opt = getopt( *argc, *argv, "e:d:n:s:p:");
    }
}

/* ===================================================================================== */

void es_Le_Arquivo_Armazena_Instrucoes_Memoria( FILE **entrada, Memoria *M )
{
    char* string_lida = (char*) calloc(8, sizeof(char));

    Word endereco_atual, dados;
    int i;
    for(i = 0; i < BITS_ARQ; i++)
        endereco_atual[i] = 0;

    while( feof(*entrada) == 0 ) {

        fscanf(*entrada, "%s", string_lida);

        //Se a string lida foi 'address', le a próxima string para atualizar o endereço de escrita atual.
        if( strcmp(string_lida, "address") == 0 ) {
            fscanf(*entrada, " %s\n", string_lida);
            es_Transforma_Hexadecimal_em_Binario(&endereco_atual, &string_lida);
        }
        //Se a string lida não foi address, e sim um valor(hexadecimal), transforma esse valor em binário
        //e escreve esse dado na memória, no endereço de escrita atual. Incrementa em 1 o endereço de escrita atual.
        else {
            fscanf(*entrada, "\n");
            es_Transforma_Hexadecimal_em_Binario(&dados, &string_lida);
            Mem_Escreve_Endereco(M, endereco_atual, dados);
            es_Incrementa_Endereco_em_Word(&endereco_atual);
        }
    }
    free(string_lida);
}

/* ===================================================================================== */

void es_Imprime_Pedido_de_Dump( Memoria *M, char** endereco_hexadecimal, int *num_words )
{
    Word endereco_binario, dados;
    char* dados_hexadecimal = (char*) calloc(5, sizeof(char));
    es_Transforma_Hexadecimal_em_Binario(&endereco_binario, endereco_hexadecimal);

    int i;
    for(i = 0; i < *num_words; i++) {
        Mem_Le_Endereco(M, endereco_binario, dados);
        es_Transforma_Binario_em_Hexadecimal(&dados, &dados_hexadecimal);
        printf("%s\n", dados_hexadecimal);
        es_Incrementa_Endereco_em_Word(&endereco_binario);
    }
    free(dados_hexadecimal);
}

/* ===================================================================================== */

void es_Transforma_Hexadecimal_em_Binario( Word *forma_binaria, char** forma_hexadecimal )
{
    int i;
    char aux;
    for(i = 0; i < 4; i++) {
        aux = (*forma_hexadecimal)[i];
        switch(aux) {
            case '0':
                (*forma_binaria)[i * 4] = 0;         (*forma_binaria)[(i * 4) + 1] = 0;
                (*forma_binaria)[(i * 4) + 2] = 0;   (*forma_binaria)[(i * 4) + 3] = 0;
                break;
            case '1':
                (*forma_binaria)[i * 4] = 0;         (*forma_binaria)[(i * 4) + 1] = 0;
                (*forma_binaria)[(i * 4) + 2] = 0;   (*forma_binaria)[(i * 4) + 3] = 1;
                break;
            case '2':
                (*forma_binaria)[i * 4] = 0;         (*forma_binaria)[(i * 4) + 1] = 0;
                (*forma_binaria)[(i * 4) + 2] = 1;   (*forma_binaria)[(i * 4) + 3] = 0;
                break;
            case '3':
                (*forma_binaria)[i * 4] = 0;         (*forma_binaria)[(i * 4) + 1] = 0;
                (*forma_binaria)[(i * 4) + 2] = 1;   (*forma_binaria)[(i * 4) + 3] = 1;
                break;
            case '4':
                (*forma_binaria)[i * 4] = 0;         (*forma_binaria)[(i * 4) + 1] = 1;
                (*forma_binaria)[(i * 4) + 2] = 0;   (*forma_binaria)[(i * 4) + 3] = 0;
                break;
            case '5':
                (*forma_binaria)[i * 4] = 0;         (*forma_binaria)[(i * 4) + 1] = 1;
                (*forma_binaria)[(i * 4) + 2] = 0;   (*forma_binaria)[(i * 4) + 3] = 1;
                break;
            case '6':
                (*forma_binaria)[i * 4] = 0;         (*forma_binaria)[(i * 4) + 1] = 1;
                (*forma_binaria)[(i * 4) + 2] = 1;   (*forma_binaria)[(i * 4) + 3] = 0;
                break;
            case '7':
                (*forma_binaria)[i * 4] = 0;         (*forma_binaria)[(i * 4) + 1] = 1;
                (*forma_binaria)[(i * 4) + 2] = 1;   (*forma_binaria)[(i * 4) + 3] = 1;
                break;
            case '8':
                (*forma_binaria)[i * 4] = 1;         (*forma_binaria)[(i * 4) + 1] = 0;
                (*forma_binaria)[(i * 4) + 2] = 0;   (*forma_binaria)[(i * 4) + 3] = 0;
                break;
            case '9':
                (*forma_binaria)[i * 4] = 1;         (*forma_binaria)[(i * 4) + 1] = 0;
                (*forma_binaria)[(i * 4) + 2] = 0;   (*forma_binaria)[(i * 4) + 3] = 1;
                break;
            case 'a':
                (*forma_binaria)[i * 4] = 1;         (*forma_binaria)[(i * 4) + 1] = 0;
                (*forma_binaria)[(i * 4) + 2] = 1;   (*forma_binaria)[(i * 4) + 3] = 0;
                break;
            case 'b':
                (*forma_binaria)[i * 4] = 1;         (*forma_binaria)[(i * 4) + 1] = 0;
                (*forma_binaria)[(i * 4) + 2] = 1;   (*forma_binaria)[(i * 4) + 3] = 1;
                break;
            case 'c':
                (*forma_binaria)[i * 4] = 1;         (*forma_binaria)[(i * 4) + 1] = 1;
                (*forma_binaria)[(i * 4) + 2] = 0;   (*forma_binaria)[(i * 4) + 3] = 0;
                break;
            case 'd':
                (*forma_binaria)[i * 4] = 1;         (*forma_binaria)[(i * 4) + 1] = 1;
                (*forma_binaria)[(i * 4) + 2] = 0;   (*forma_binaria)[(i * 4) + 3] = 1;
                break;
            case 'e':
                (*forma_binaria)[i * 4] = 1;         (*forma_binaria)[(i * 4) + 1] = 1;
                (*forma_binaria)[(i * 4) + 2] = 1;   (*forma_binaria)[(i * 4) + 3] = 0;
                break;
            case 'f':
                (*forma_binaria)[i * 4] = 1;         (*forma_binaria)[(i * 4) + 1] = 1;
                (*forma_binaria)[(i * 4) + 2] = 1;   (*forma_binaria)[(i * 4) + 3] = 1;
                break;
        }
    }
}

/* ===================================================================================== */

void es_Transforma_Binario_em_Hexadecimal( Word *forma_binaria, char** forma_hexadecimal )
{
    char hexadecimais[17] = "0123456789abcdef";
    int i;
    for(i = 0; i < 4; i++) {
        int valor = (8 *(*forma_binaria)[i * 4]) + (4 *(*forma_binaria)[(i * 4) + 1]) + (2 *(*forma_binaria)[(i * 4) + 2]) + (*forma_binaria)[(i * 4) + 3];
        (*forma_hexadecimal)[i] = hexadecimais[valor];
    }
}

/* ===================================================================================== */

//Incrementa o endereço presente na word 'endereco' em 1.
void es_Incrementa_Endereco_em_Word( Word *endereco )
{
    int i, j;
    bool sinal = false;
    for(i = BITS_ARQ - 1; i >= 0; i--) {
        if( ((*endereco)[i] == 0) && (sinal == false) ) {
            (*endereco)[i] = 1;
            return;
        }
        else {
            if( (*endereco)[i] == 0 ) {
                (*endereco)[i] = 1;
                for(j = i + 1; j < BITS_ARQ; j++)
                    (*endereco)[j] = 0;
            }
            else 
                sinal = true;
        }
    }
}
/* ************************************************************************************ */
