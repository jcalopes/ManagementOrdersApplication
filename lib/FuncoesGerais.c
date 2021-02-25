/** 
 * @file
 * @author Leandro
 *
 * @brief Biblioteca com funções gerais.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "FuncoesGerais.h"

/**
 * 
 * Esta função serve para guardar os dados em ficheiro.
 * 
 * @param nomeficheiro este parâmetro é o nome do ficheiro que guardará toda a informção.
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param numEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param arrayClientes este parâmetro é a lista de todas as encomendas existentes.
 * @param numClientes este parâmetro é o numero de clientes existentes (contador).
 * @param tabela este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 * @param tamanhoClientes é o tamanho de memoria alocada para a lista de clientes.
 * @param tamanhoEncomendas é o tamanho de memoria alocada para a lista de encomendas.
 * @return returna 0 ou 1 mediante o ocorrido.
 */
int guardarInformacao(char* nomeficheiro, struct Encomenda *arrayEncomendas, int numEncomendas,
        struct Cliente *arrayClientes, int numClientes, struct Custo tabela, int tamanhoClientes, int tamanhoEncomendas) {
    FILE *ficheiro;
    int i;
    ficheiro = fopen(nomeficheiro, "wb");

    if ((ficheiro) == NULL) {
        printf("Não foi possível abrir o ficheiro!\n");
        return 0;
    } else {
        fwrite(&numEncomendas, sizeof (int), 1, ficheiro);
        fwrite(&numClientes, sizeof (int), 1, ficheiro);
        fwrite(&tamanhoEncomendas, sizeof (int), 1, ficheiro);
        fwrite(&tamanhoClientes, sizeof (int), 1, ficheiro);
        fwrite(arrayEncomendas, sizeof (struct Encomenda), numEncomendas, ficheiro);
        fwrite(arrayClientes, sizeof (struct Cliente), numClientes, ficheiro);

        for (i = 0; i < numEncomendas; i++)
            fwrite(arrayEncomendas[i].artigos, 
                    sizeof (struct Artigo), arrayEncomendas[i].contadorArtigos, ficheiro);

        fwrite(&tabela, sizeof (struct Custo), 1, ficheiro);
        fclose(ficheiro);
        return 1;
    }
}

/**
 * 
 * Esta função serve para ler a informação de um ficheiro.
 * 
 * @param nomeficheiro este parâmetro é o nome do ficheiro que guardará toda a informção.
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param nEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param arrayClientes este parâmetro é a lista de todas as encomendas existentes.
 * @param nClientes este parâmetro é o numero de clientes existentes (contador).
 * @param tabela este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 * @param tamanhoClientes é o tamanho de memoria alocada para a lista de clientes.
 * @param tamanhoEncomendas é o tamanho de memoria alocada para a lista de encomendas.
 * @return 
 */
int carregarInformacao(char* nomeficheiro, struct Encomenda **arrayEncomendas, int *nEncomendas,
        struct Cliente **arrayClientes, int *nClientes, struct Custo *tabela, int *tamanhoClientes, int *tamanhoEncomendas) {

    FILE *ficheiro;
    int n1 = 0, n2 = 0, n3 = 0, n4 = 0, i = 0, j = 0;

    ficheiro = fopen(nomeficheiro, "rb");

    if (ficheiro == NULL) {
        perror("Erro ao abrir ficheiro!\n");
        *nEncomendas = 0;
        *nClientes = 0;
        return 0;
    } else {
        n1 = fread(nEncomendas, sizeof (int), 1, ficheiro);
        n2 = fread(nClientes, sizeof (int), 1, ficheiro);
        n3 = fread(tamanhoEncomendas, sizeof (int), 1, ficheiro);
        n4 = fread(tamanhoClientes, sizeof (int), 1, ficheiro);
        printf("%d clientes carregados!\n", *nClientes);
        printf("%d encomendas carregadas!\n", *nEncomendas);  

        if (n1 != 1 || n2 != 1 || n3 != 1 || n4 != 1) {
            printf("Erro ao ler o ficheiro!\n");
            *nEncomendas = 0;
            *nClientes = 0;
            *tamanhoEncomendas = 0;
            *tamanhoClientes = 0;
            fclose(ficheiro);
            return 0;
        }
        
        (*arrayEncomendas) = (struct Encomenda*) 
                malloc(*tamanhoEncomendas * sizeof (struct Encomenda));
        if ((*arrayEncomendas) == NULL) {
            printf("Erro ao alocar memória!\n");
            *nEncomendas = 0;
            *nClientes = 0;
            fclose(ficheiro);
            return 0;
        }
       
        n1 = fread((*arrayEncomendas), sizeof (struct Encomenda), *nEncomendas, ficheiro);
        if (n1 != *nEncomendas) {
            printf("Erro ao ler o ficheiro!\n");
            *nEncomendas = 0;
            *nClientes = 0;
            free(*arrayEncomendas);
            fclose(ficheiro);
            return 0;
        }

        //alocar espaco para os clientes
        (*arrayClientes) = (struct Cliente*) malloc(*tamanhoClientes * sizeof (struct Cliente));
        if (*arrayClientes == NULL) {
            printf("Erro ao alocar memória!\n");
            *nEncomendas = 0;
            *nClientes = 0;
            free(*arrayEncomendas);
            fclose(ficheiro);
            return 0;
        }
        //ler os dados dos clientes
        n1 = fread((*arrayClientes), sizeof (struct Cliente), *nClientes, ficheiro);
        if (n1 != *nClientes) {
            printf("Erro ao ler o ficheiro!\n");
            *nEncomendas = 0;
            *nClientes = 0;
            free(*arrayEncomendas);
            free(*arrayClientes);
            fclose(ficheiro);
            return 0;
        }

        //alocar espaco para artigos em cada encomenda
        for (i = 0; i<*nEncomendas; i++) {
            int n_artigos = (*arrayEncomendas)[i].contadorArtigos;

            (*arrayEncomendas)[i].artigos = (struct Artigo*) malloc(n_artigos * sizeof (struct Artigo));
            if ((*arrayEncomendas)[i].artigos == NULL) {
                printf("Erro ao alocar memória!\n");
                for (j = i - 1; j >= 0; i--) {
                    free((*arrayEncomendas)[j].artigos);
                }
                free(*arrayEncomendas);
                free(*arrayClientes);
                *nEncomendas = 0;
                *nClientes = 0;
                fclose(ficheiro);
                return 0;
            }

            //ler dados dos artigos em cada encomenda
            n1 = fread((*arrayEncomendas)[i].artigos, sizeof (struct Artigo), n_artigos, ficheiro);
            if (n1 != n_artigos) {
                printf("Erro ao ler o ficheiro!\n");
                free(*arrayClientes);
                *nClientes = 0;
                for (j = i - 1; j >= 0; i--) {
                    free((*arrayEncomendas)[j].artigos);
                }
                *nEncomendas = 0;
                free(*arrayEncomendas);
                fclose(ficheiro);
                return 0;
            }
        }

        //ler tabela de precos
        n1 = fread(tabela, sizeof (struct Custo), 1, ficheiro);
        if (n1 != 1) {
            printf("Erro no carregamento de dados da tabela de preços!\n");
            *nEncomendas = 0;
            for (j = i - 1; j >= 0; i--) {
                free((*arrayEncomendas)[j].artigos);
            }
            free(*arrayEncomendas);
            *nClientes = 0;
            fclose(ficheiro);
            return 0;
        }

        fclose(ficheiro);
        return 1;
    }
}
