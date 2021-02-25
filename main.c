/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Leandro
 *
 * Created on 9 de Dezembro de 2019, 17:03
 */

#include "lib/GestaoUtilizadores.h"
#include "lib/FuncoesGerais.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMANHO_ARRAY_INICIAL 6


int main(int argc, char** argv) {
    struct Cliente *arrayClientes;
    int contadorClientes;

    struct Encomenda *arrayEncomendas;
    int contadorEncomendas;
    int tamanhoEncomendas;
    int codigoEncomenda=1000;

    struct Custo tabelaPrecos;
    int tamanho, i = 0;
    arrayClientes = (struct Cliente *) malloc(sizeof (struct Cliente)*TAMANHO_ARRAY_INICIAL);
    tamanho = TAMANHO_ARRAY_INICIAL;
    arrayEncomendas = (struct Encomenda *) malloc(sizeof (struct Encomenda)*TAMANHO_ARRAY_INICIAL);
    tamanhoEncomendas = TAMANHO_ARRAY_INICIAL;
    seedDataTabela(&tabelaPrecos);
    menu(&arrayClientes, &arrayEncomendas, &tabelaPrecos, &contadorClientes, &contadorEncomendas, &tamanho,
            &tamanhoEncomendas, &codigoEncomenda);

    free(arrayClientes);
    while (i < contadorEncomendas) {
        free(arrayEncomendas[i].artigos);
        i++;
    }
    free(arrayEncomendas);

    return (EXIT_SUCCESS);
}