/** 
 * @file
 * @author Leandro
 *
 * @brief Biblioteca com funções para gestão de tabelas de custo.
 *
 */
#include <stdio.h>

#include "GestaoTabelaPrecos.h"

#include "API_Leitura.h"
#include "API_Utils.h"

#include "FuncoesGerais.h"

#define TAMANHO_ORIGEM_DESTINO 9


/**
 * 
 * Esta função serve para listar a tabela de custos de transporte.
 * 
 * @param tabelaPrecos este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 */
void listarTabelaPrecos(struct Custo tabelaPrecos) {
    int opcap, i, j;
    printf("---------------------------------------\n");
    printf("Tabela Custo Transporte (Origem/Destino\n");
    printf("---------------------------------------\n");
    printf("\tDestino\t1 \t\t2 \t\t 3 \t\t 4 \t\t 5 \t\t 6 \t\t 7 \t\t 8 \t\t 9\n");
    printf("Origem");

    for (i = 0; i < TAMANHO_ORIGEM_DESTINO; i++) {
        printf("\n");
        printf("%d", i + 1);
        for (j = 0; j < TAMANHO_ORIGEM_DESTINO; j++) {
            printf("\t\t %.2f ", tabelaPrecos.custoCodigoPostal[i][j]);
        }
    }
    printf("\n---------------------------------------\n");
    printf("Tabela Custo Tipo Transporte\n");
    printf("---------------------------------------\n");
    printf("Regular- %.2f\n", tabelaPrecos.custoRegular);
    printf("Urgente- %.2f\n", tabelaPrecos.custoUrgente);
    printf("Volumosa- %.2f\n", tabelaPrecos.custoVolumoso);
    printf("Frágil- %.2f\n", tabelaPrecos.custoFragil);
    printf("Pesado- %.2f\n", tabelaPrecos.custoPesado);
    printf("Custo Por Km- %.2f\n", tabelaPrecos.custoPorQuilometro);

}

/**
 * Esta função serve para editar o custo de transporte das encomendas com base no seu volume/tratamento/necessidade/peso.
 * 
 * @param tabelaPrecos este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 */
void menuEditaTabelaPrecos(struct Custo* tabelaPrecos,struct Cliente **arrayclientes,int contadorClientes) {
    int opcao;
    do {
        printf("1-Alterar Preços Origem/Destino\n");
        printf("2-Alterar Preço Transporte Regular\n");
        printf("3-Alterar Preço Transporte Urgente\n");
        printf("4-Alterar Preço Transporte Volumoso\n");
        printf("5-Alterar Preço Transporte Frágil\n");
        printf("6-Alterar Preço Transporte Pesado\n");
        printf("7-Alterar Preço Por Quilometro\n");
        printf("8-Sair");
        readInt(&opcao, 1, 8, "Escolha a opcao: ");
        do {
            switch (opcao) {
                case 1:
                    editaPrecoCodigoPostal(tabelaPrecos);
                    avisaClientes(*arrayclientes,contadorClientes);
                    break;

                case 2:
                    readFloat(&tabelaPrecos->custoRegular, 0, 1000, "Introduza o novo preço: ");
                    printf("AVISO:Preço do Transporte Regular modificado!\n");
                    avisaClientes(*arrayclientes,contadorClientes);
                    break;

                case 3:
                    readFloat(&tabelaPrecos->custoUrgente, 0, 1000, "Introduza o novo preço: ");
                    printf("AVISO:Preço do Transporte Urgente modificado!\n");
                    avisaClientes(*arrayclientes,contadorClientes);
                    break;

                case 4:
                    readFloat(&tabelaPrecos->custoVolumoso, 0, 1000, "Introduza o novo preço: ");
                    printf("AVISO:Preço do Transporte Volumoso modificado!\n");
                    avisaClientes(*arrayclientes,contadorClientes);
                    break;

                case 5:
                    readFloat(&tabelaPrecos->custoFragil, 0, 1000, "Introduza o novo preço: ");
                    printf("AVISO:Preço do Transporte Frágil modificado!\n");
                    avisaClientes(*arrayclientes,contadorClientes);
                    break;
                case 6:
                    readFloat(&tabelaPrecos->custoPesado, 0, 1000, "Introduza o novo preço: ");
                    printf("AVISO:Preço do Transporte Pesado modificado!\n");
                    avisaClientes(*arrayclientes,contadorClientes);
                    break;
                case 7:
                    readFloat(&tabelaPrecos->custoPorQuilometro, 0, 1000, "Introduza o novo preço: ");
                    printf("AVISO:Preço por Quilometro modificado!\n");
                    avisaClientes(*arrayclientes,contadorClientes);
                    break;
                case 8:
                    break;
            }
        } while (opcao < 1 || opcao > 8);

    } while (opcao != 8);
}

/**
 * 
 * Esta função serve para editar a tabela de custos de uma encomenda com base na origem/destino.
 * 
 * @param tabelaPrecos este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 */
void editaPrecoCodigoPostal(struct Custo* tabelaPrecos) {
    int origem, destino;

    readInt(&origem, 1, 9, "Introduza o primeiro digito do código postal da origem: ");
    readInt(&destino, 1, 9, "Introduza o primeiro digito do código postal do destino: ");

    readFloat(&(*tabelaPrecos).custoCodigoPostal[origem - 1][destino - 1], 0, 1000, "Introduza o novo preço: ");
    printf("AVISO:Preço do Transporte Origem: %d e Destino: %d modificado!\n\n", origem, destino);
}

/**
 * 
 * Esta função serve para avisar todos os clientes que a tabela de custos foi alterada.
 * 
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 */
void avisaClientes(struct Cliente *arrayClientes,int contadorClientes){
    int i = 0;
    while (i < contadorClientes) {
        arrayClientes[i].avisoAlteracaoTabelaPrecos = 1;
        i++;
    }

}
