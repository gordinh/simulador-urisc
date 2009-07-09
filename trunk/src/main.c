/*
 * =============================================================================
 * 
 *      Arquivo: main.c
 *        Autores: Letícia Lana Cherchiglia, Leonardo Vilela Teixeira, Lucas Alves Guerra França
 *        email: letslc@dcc.ufmg.br, vilela@dcc.ufmg.br, lguerra@dcc.ufmg.br
 *
 * =============================================================================
 */

#include "defs.h"
#include "registradores.h"
#include "memoria.h"
#include "alu.h"
#include "constantes.h"
#include "jumps.h"
#include "controle.h"
#include "es.h"
#include "processador.h"

#include <stdlib.h>
#include <stdio.h>

/* ========================================================================== */

int main(int argc, char * argv[])
{

    //Declara variáveis e as inicializa por meio da função seguinte.
    char *nome_arq_entrada = NULL;
    char *dump_pos_inicial = NULL;
    int dump_num_palavras = 0;
    bool screen = false;
    bool pausa = false;

    es_Inicializa_Variaveis_Parametros_Execucao( int *argc, char ***argv, &nome_arq_entrada, &dump_pos_inicial, &dump_num_palavras, &screen, &pausa );

    //Cria e inicializa um processador.
    Processador processador;
    Inicializa_Processador(&processador);

    //Abre o arquivo de entrada.
    FILE *arq_entrada;
    abreArquivoLeitura(&arq_entrada, nome_arq_entrada);

    //Carrega a memória a partir dos dados do arquivo de entrada.
    es_Le_Arquivo_Armazena_Instrucoes_Memoria(&arq_entrada, &processador->memoria);

    //Inicia o processamento.
    Executa_Processamento(&processador, &screen, &dump_pos_inicial, &dump_num_palavras);

    //Fecha o arquivo de entrada.
    fclose(arq_entrada);    
}

/* ========================================================================== */

