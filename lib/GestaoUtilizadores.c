/** 
 * @file
 * @author Leandro
 *
 * @brief Biblioteca com funções para gestão de utilizadores.
 *
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "API_Leitura.h"
#include "API_Utils.h"

#include "FuncoesGerais.h"

#include "GestaoUtilizadores.h"
#define TAMANHO_AUMENTA_REALLOC 20
#define TAMANHOS_STRINGS 20
#define TAMANHO_ARRAY_INICIAL 6

/**
 * 
 * Esta função serve para apresentar o sub-menu do cliente.
 * 
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param tabelaPreco este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param tamanho é o tamanho de memoria alocada para a lista de clientes.
 * @param tamanhoEncomendas é o tamanho de memoria alocada para a lista de encomendas.
 * @param codigoEncomendas este parâmetro é o próximo código disponível da encomenda.
 */
void subMenuCliente(struct Cliente **arrayClientes, struct Encomenda **arrayEncomendas, struct Custo tabelaPreco,
        int *contadorClientes, int *contadorEncomendas, int *tamanho, int *tamanhoEncomendas, int*codigoEncomendas) {
    int opcao;
    do {
        printf("------------------------------\n");
        printf("MENU CLIENTE\n");
        printf("------------------------------\n");
        printf("\n");
        printf("1 - Criar Conta\n");
        printf("2 - Login\n");
        printf("3 - Sair\n");
        do {
            readInt(&opcao, 1, 3, "Insira a sua opção: ");
            switch (opcao) {
                case 1:
                    criar(arrayClientes, contadorClientes, tamanho);
                    break;
                case 2:
                    login(arrayClientes, arrayEncomendas, tabelaPreco, contadorClientes, contadorEncomendas, tamanhoEncomendas, codigoEncomendas);
                    break;
                case 3:
                    break;
            }

        } while (opcao < 1 || opcao > 3);
    } while (opcao != 3);

}

/**
 * 
 * Esta função serve para o cliente realizar o login na sua conta através da sua password e nif.
 * 
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param tabelaPreco este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param tamanhoEncomendas é o tamanho de memoria alocada para a lista de encomendas.
 * @param codigoEncomendas este parâmetro é o próximo código disponível da encomenda.
 */
void login(struct Cliente **arrayClientes, struct Encomenda **arrayEncomendas, struct Custo tabelaPreco,
        int *contadorClientes, int *contadorEncomendas, int *tamanhoEncomendas, int *codigoEncomendas) {
    int nif, existe = -1;
    char password[TAMANHOS_STRINGS];
    printf("------------------------------\n");
    printf("LOGIN\n");
    printf("------------------------------\n");
    readInt(&nif, 100000000, 999999999, "Por favor insira o seu nif: ");
    existeNIF(*arrayClientes, *contadorClientes, &existe, nif);

    if (existe == -1) {
        printf("AVISO: Não existe nenhum cliente registado com o NIF: %d, por favor registe-se!\n", nif);
    } else {
        readString(password, TAMANHOS_STRINGS, "Por favor insira a sua password: ");
        if (strcmp(password, (*arrayClientes)[existe].password) == 0) {

            if ((*arrayClientes)[existe].removido != 1) {
                if ((*arrayClientes)[existe].avisoAlteracaoTabelaPrecos == 1 || (*arrayClientes)[existe].avisoExpedicao == 1) {
                    printf("---------AVISOS---------\n");
                    if ((*arrayClientes)[existe].avisoAlteracaoTabelaPrecos == 1) {
                        printf("[ALTERAÇÃO] A tabela de preços foi alterada, por favor consulte a nova tabela!\n");
                        (*arrayClientes)[existe].avisoAlteracaoTabelaPrecos = 0;
                    }
                    if ((*arrayClientes)[existe].avisoExpedicao == 1) {
                        printf("[EXPEDIÇÃO] Uma ou mais encomendas suas foram expedida(s)!\n");
                        (*arrayClientes)[existe].avisoExpedicao = 0;
                    }
                }
                menuClienteLogado(arrayClientes, arrayEncomendas, tabelaPreco, contadorClientes, contadorEncomendas, existe, tamanhoEncomendas, codigoEncomendas);
            } else {
                printf("A conta foi removida, por favor fale com o diretor\n");
            }
        } else {
            printf("Password errada!\n");
        }
    }
}

/**
 * 
 * Esta função serve para apresentar o menu principal.
 * 
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param tabelaPreco este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param tamanho é o tamanho de memoria alocada para a lista de clientes.
 * @param tamanhoEncomendas é o tamanho de memoria alocada para a lista de encomendas.
 * @param codigoEncomendas este parâmetro é o próximo código disponível da encomenda.
 */
void menu(struct Cliente **arrayClientes, struct Encomenda **arrayEncomendas, struct Custo *tabelaPreco,
        int *contadorClientes, int *contadorEncomendas, int *tamanho, int * tamanhoEncomendas, int*codigoEncomendas) {
    int opcao;
    do {
        printf("\n");
        printf("1 - Cliente\n");
        printf("2 - Diretor\n");
        printf("3 - Ler dados\n");
        printf("4 - Guardar dados\n");
        printf("5 - Sair\n");
        do {
            readInt(&opcao, 1, 5, "Insira a sua opção: ");
            switch (opcao) {
                case 1:
                    subMenuCliente(arrayClientes, arrayEncomendas, *tabelaPreco,
                            contadorClientes, contadorEncomendas, tamanho, tamanhoEncomendas, codigoEncomendas);
                    break;
                case 2:
                    subMenuDiretor(arrayClientes, arrayEncomendas, contadorEncomendas, tabelaPreco, contadorClientes, tamanho, tamanhoEncomendas);
                    break;
                case 3:
                    chamarDados(arrayEncomendas, contadorEncomendas, arrayClientes,
                            contadorClientes, tabelaPreco, tamanho, tamanhoEncomendas, codigoEncomendas);
                    break;
                case 4:
                    if (guardarInformacao("basededados.dat", *arrayEncomendas, *contadorEncomendas,
                            *arrayClientes, *contadorClientes, *tabelaPreco, *tamanho, *tamanhoEncomendas))
                        printf("Dados guardados com sucesso!\n");
                    else
                        printf("Não foi possível guardar os dados!");
                    break;
                case 5:
                    break;
            }
        } while (opcao < 1 || opcao > 5);

    } while (opcao != 5);
}

/**
 * 
 * Esta função serve para criar uma nova conta de cliente.
 * 
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 * @param tamanho é o tamanho de memoria alocada para a lista de clientes.
 */
void criar(struct Cliente **arrayClientes, int *contadorClientes, int *tamanho) {
    struct Cliente *apontador_temporario;
    int i = 0, vagas = 0, existe = -1;
    int nif;
    if (*contadorClientes == *tamanho) {
        printf("AVISO: A realocar memoria...\n");
        apontador_temporario = (struct Cliente *) realloc(*arrayClientes, sizeof (struct Cliente)* ((*tamanho) + TAMANHO_AUMENTA_REALLOC));
        if (apontador_temporario != NULL) {
            *tamanho += TAMANHO_AUMENTA_REALLOC;
            (*arrayClientes) = apontador_temporario;
            printf("Memória realocada com sucesso!\n");

            vagas = *tamanho - *contadorClientes;
            printf("\nHa %d vagas!\n\n", vagas);
            printf("Existe %d clientes registados", *contadorClientes);

            readInt(&nif, 100000000, 999999999, "Introduza o seu nif: ");
            existeNIF(*arrayClientes, *contadorClientes, &existe, nif);
            if (existe == -1) {
                pedirDados(*arrayClientes, *contadorClientes, nif);
                (*contadorClientes)++;
            } else {
                printf("Este NIF já está registado!\n");

            }

        } else
            printf("ERRO AO ALOCAR MEMORIA");

    } else {
        readInt(&nif, 100000000, 999999999, "Introduza o seu nif: ");
        existeNIF(*arrayClientes, *contadorClientes, &existe, nif);
        if (existe == -1) {
            pedirDados(*arrayClientes, *contadorClientes, nif);
            (*contadorClientes)++;
        } else {
            printf("Este NIF já está registado!\n");
        }
    }
}

/**
 * 
 * Esta função serve para verificar se ja existe algum cliente com determinado nif.
 * 
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param contador este parâmetro é o numero de clientes existentes (contador).
 * @param existe este parâmetro recebe valor -1 caso não exista e recebe o valor da sua posição caso exista.
 * @param nif este parâmetro é o nif a ser pesquisado.
 */
void existeNIF(struct Cliente *arrayClientes, int contador, int *existe, int nif) {
    int i = 0;
    while (i < contador && arrayClientes[i].nif != nif)
        i++;
    if (i != contador)
        (*existe) = i;
    else
        (*existe) = -1;

}

/**
 * 
 * Esta função serve para listar todos os clientes existentes.
 * 
 * @param array este parâmetro é a lista de todos os clientes existentes.
 * @param contador este parâmetro é o numero de clientes existentes (contador).
 */
void listarTodos(struct Cliente *array, int contador) {
    int i = 0;
    int contador2 = 0;
    if (contador != 0) {
        printf("\n\nExistem as seguintes pessoas na lista: \n");
        while (i < contador) {
            if (array[i].removido == 0) {
                printf("NOME: %s - Ativo\n", array[i].nome);
            } else {
                printf("NOME: %s - Removido\n", array[i].nome);
            }
            i++;
            contador2++;

        }

    }
    if (contador2 == 0) {
        printf("A lista esta vazia!\n\n");
    }
}

/**
 * 
 * Esta função serve para pedir os seus dados ao cliente.
 * 
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 * @param nif este parâmetro é o nif do cliente.
 */
void pedirDados(struct Cliente *arrayClientes, int contadorClientes, int nif) {

    arrayClientes[contadorClientes].nif = nif;
    readInt(&arrayClientes[contadorClientes].cc, 10000000, 99999999, "Introduza o seu cc: ");
    readString(arrayClientes[contadorClientes].nome, TAMANHOS_STRINGS, "Introduza o seu nome: ");
    readString(arrayClientes[contadorClientes].password, TAMANHOS_STRINGS, "Introduza a sua password: ");
    readString(arrayClientes[contadorClientes].morada.rua, TAMANHOS_STRINGS, "Introduza a sua rua: ");
    readInt(&arrayClientes[contadorClientes].morada.codigoPostal, 1000000, 9999999, "Introduza o seu código postal: ");
    readString(arrayClientes[contadorClientes].morada.localidade, TAMANHOS_STRINGS, "Introduza a sua localidade:");
    readInt(&arrayClientes[contadorClientes].morada.numero, 1, 4000, "Introduza o seu número da porta: ");
    readString(arrayClientes[contadorClientes].morada.pais, TAMANHOS_STRINGS, "Introduza o seu país: ");
}

/**
 * 
 * Esta função serve para apresentar o menu do cliente quando se encontra logado.
 * 
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param tabelaPreco este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param posicao é a posição do cliente na lista de clientes.
 * @param tamanhoEncomendas é o tamanho de memoria alocada para a lista de encomendas.
 * @param codigoEncomendas este parâmetro é o próximo código disponível da encomenda.
 */
void menuClienteLogado(struct Cliente **arrayClientes, struct Encomenda **arrayEncomendas, struct Custo tabelaPreco,
        int *contadorClientes, int * contadorEncomendas, int posicao, int *tamanhoEncomendas, int *codigoEncomendas) {

    int opcao, opcaoRemove = 0, nif, mes, ano, mMes, mAno;
    nif = (*arrayClientes)[posicao].nif;

    time_t myTime = time(NULL);
    struct tm data; //esta estrutura já vem pré-definida na bibliotece time.h
    data = *localtime(&myTime);

    mes = (data.tm_mon) + 1;
    ano = (data.tm_year) + 1900;

    do {
        printf("------------------------------\n");
        printf("BEM-VINDO %s\n", (*arrayClientes)[posicao].nome);
        printf("------------------------------\n");
        printf("\n");
        printf("1  - Alterar Perfil\n");
        printf("2  - Remover Conta\n");
        printf("3  - Listar Tabela de Precos Transporte\n");
        printf("4  - Adicionar Encomenda\n");
        printf("5  - Listar Minhas Encomendas\n");
        printf("6  - Imprimir Fatura relativa a este mês\n");
        printf("7  - Imprimir Fatura relativa a um mês anterior\n");
        printf("8  - Visão Geral Gastos Mensais\n");
        printf("9  - Remover Encomenda\n");
        printf("10  - Alterar encomenda\n ");
        printf("11 - Obter custo de envio de uma encomenda\n ");
        printf("12 - Submeter comentário sobre uma encomenda\n");
        printf("13 - Sair\n");
        do {
            readInt(&opcao, 1, 13, "Insira a sua opção: ");
            switch (opcao) {
                case 1:
                    alterarDados(*arrayClientes, posicao);
                    break;
                case 2:
                    printf("Deseja remover a sua conta?\n\n");
                    printf("\n");
                    printf("0 - Não\n");
                    printf("1 - Sim\n");
                    readInt(&opcaoRemove, 0, 1, "Insira a sua opção: ");
                    if (opcaoRemove == 1) {
                        (*arrayClientes)[posicao].removido = 1;
                        return;
                    }
                    break;
                case 3:
                    listarTabelaPrecos(tabelaPreco);
                    break;
                case 4:
                    criarEncomenda(arrayEncomendas, contadorEncomendas, tamanhoEncomendas, nif, codigoEncomendas, tabelaPreco);
                    break;
                case 5:
                    listarEncomendas(*arrayEncomendas, *contadorEncomendas, nif);
                    break;
                case 6:
                    imprimirFatura(*arrayEncomendas, *contadorEncomendas, mes, ano, nif, tabelaPreco);
                    break;
                case 7:
                    readInt(&mMes, 1, 12, "Por favor introduza o mes: ");
                    readInt(&mAno, 2000, 2020, "Por favor introduza o ano: ");
                    imprimirFatura(*arrayEncomendas, *contadorEncomendas, mMes, mAno, nif, tabelaPreco);
                    break;
                case 8:
                    gastosCliente(*arrayEncomendas, *contadorEncomendas, nif);
                    break;
                case 9:
                    if (removerEncomenda(arrayEncomendas, contadorEncomendas, nif, codigoEncomendas))
                        printf("Encomenda removida com sucesso!\n ");
                    else 
                        printf("Não é permitido remover encomenda!\n ");
                    break;
                case 10:
                    if (alterarEncomenda(arrayEncomendas, *contadorEncomendas, tabelaPreco, nif))
                        printf("Dados alterados com sucesso!\n");
                    else
                        printf("Não foram efetuadas alterações!\n");
                    break;
                case 11:
                    orcamento(tabelaPreco);
                    break;
                case 12:
                    notas(*arrayEncomendas, *codigoEncomendas, *contadorEncomendas, nif);
                    break;
                case 13:
                    break;
            }

        } while (opcao < 1 || opcao > 13);

    } while (opcao != 13);

}

/**
 * 
 * Esta função serve para um determinado cliente alterar os seus dados.
 * 
 * @param arrayCliente este parâmetro é a lista de todos os clientes existentes.
 * @param posicao é a posição do cliente na lista de clientes.
 */
void alterarDados(struct Cliente *arrayCliente, int posicao) {
    pedirDados(arrayCliente, posicao, arrayCliente[posicao].nif);
}
/**
 * 
 * Esta função serve para apresnetar o sub-menu do diretor.
 * 
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param tabelaPreco este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 * @param tamanho é o tamanho de memoria alocada para a lista de clientes.
 * @param tamanhoEncomendas é o tamanho de memoria alocada para a lista de encomendas.
 */
void subMenuDiretor(struct Cliente **arrayClientes, struct Encomenda **arrayEncomendas, int *contadorEncomendas, struct Custo *tabelaPreco,
        int *contadorClientes, int *tamanho, int *tamanhoEncomendas) {

    int opcao;
    do {
        printf("------------------------------\n");
        printf("Menu Diretor\n");
        printf("------------------------------\n");
        printf(" 1-Listar Todos os Clientes\n");
        printf(" 2-Pesquisar Cliente por NIF\n");
        printf(" 3-Pesquisar Cliente por CC\n");
        printf(" 4-Ativar Cliente\n");
        printf(" 5-Listar Tabela Precos Transporte\n");
        printf(" 6-Alterar Tabela Precos Transporte\n");
        printf(" 7-Expedir Encomenda\n");
        printf(" 8-Listar Todas as Encomendas\n");
        printf(" 9-Relatório estatísticas das encomendas\n");
        printf(" 10-Dados Financeiros\n");
        printf(" 11-Consultar feedback clientes\n");
        printf(" 12-Sair\n");

        do {
            readInt(&opcao, 1, 12, "Insira a sua opção: ");

            switch (opcao) {
                case 1:
                    listarTodos(*arrayClientes, *contadorClientes);
                    break;
                case 2:
                    pesquisaNIF(*arrayClientes, *contadorClientes);
                    break;
                case 3:
                    pesquisaCC(*arrayClientes, *contadorClientes);
                    break;
                case 4:
                    ativarCliente(*arrayClientes, *contadorClientes);
                    break;
                case 5:
                    listarTabelaPrecos(*tabelaPreco);
                    break;
                case 6:
                    menuEditaTabelaPrecos(tabelaPreco, arrayClientes, *contadorClientes);
                    break;
                case 7:
                    expedirEncomenda(*arrayEncomendas, *contadorEncomendas, *arrayClientes, *contadorClientes);
                    break;
                case 8:
                    listarTodasEncomendas(*arrayEncomendas, *contadorEncomendas);
                    break;
                case 9:
                    relatorioMediaEncomendas(*arrayEncomendas, *contadorEncomendas);
                    break;
                case 10:
                    lucros(*arrayEncomendas, *contadorEncomendas);
                    break;
                case 11:
                    mostraNotas(*arrayEncomendas, *contadorEncomendas);
                    break;
                case 12:
                    break;
            }
        } while (opcao < 1 || opcao > 12);
    } while (opcao != 12);
}

/**
 * 
 * Esta função serve para o diretor ativar um cliente que tenha removido a sua conta.
 * 
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 */
void ativarCliente(struct Cliente *arrayClientes, int contadorClientes) {
    int nif, existe = -1;
    if (contadorClientes==0)
        printf("Não existem clientes registados!\n");
    else
    {
        readInt(&nif, 100000000, 999999999, "Insira o NIF do cliente que pretende ativar: ");
        existeNIF(arrayClientes, contadorClientes, &existe, nif);
        if (existe == -1) 
            printf("AVISO: Não existe nenhum cliente registado com esse NIF!\n");
         else 
         {
            if (arrayClientes[existe].removido == 0) 
                printf("O Cliente com o NIF: %d já se encontra ativo!\n", nif);
           else 
            {
                arrayClientes[existe].removido = 0;
                printf("Cliente ativado com sucesso!\n");
            }
        }
    }   
}

/**
 * 
 * Esta função serve para pesquisar um cliente atrav´ss do seu nif.
 * 
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 */
void pesquisaNIF(struct Cliente *arrayClientes, int contadorClientes) {
    int nif, i = 0;
    if (contadorClientes == 0)
        printf("Não existe Clientes na lista!\n");
    else {
        readInt(&nif, 100000000, 999999999, "Introduza o NIF: ");
        while (i < contadorClientes) {
            if (arrayClientes[i].nif == nif) {
                printf("Nome: %s\n", arrayClientes[i].nome);
                printf("NIF: %d\n", arrayClientes[i].nif);
                printf("Cartão de Cidadão: %d\n", arrayClientes[i].cc);
                printf("Morada:\n");
                printf("\tRua: %s\n", arrayClientes[i].morada.rua);
                printf("\tLocalidade: %s\n", arrayClientes[i].morada.localidade);
                printf("\tNúmero da Porta: %d\n", arrayClientes[i].morada.numero);
                printf("\tCódigo Postal: %d\n", arrayClientes[i].morada.codigoPostal);
                printf("\tPaís: %s\n", arrayClientes[i].morada.pais);
                break;
            }
            i++;
        }
        if (i == contadorClientes)
            printf("Não existe nenhum Cliente registado com esse NIF!\n");
    }
}

/**
 * 
 * Esta função serve para um determinado cliente pedir um orçamento para uma possivel encomenda.
 * 
 * @param tabela este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 */
void orcamento(struct Custo tabela) {
    int codPostalOrigem, codPostalDestino, tipoEntrega, numeroArtigos, i, tratamentoEspecial;
    float precoTotal = 0, pesoTotal = 0, volumeTotal = 0, peso, volume, numKM;

    readInt(&codPostalOrigem, 1000000, 9999999, "Por favor introduza o código postal de origem: (ex:9999999): ");
    readInt(&codPostalDestino, 1000000, 9999999, "Por favor introduza o código postal de destino: (ex:9999999): ");
    codPostalOrigem = (int) (codPostalOrigem / 1000000);
    codPostalDestino = (int) (codPostalDestino / 1000000);
    readFloat(&numKM, 1, 700, "Introduza os quilómetros entre a origem e o destino: ");
    readInt(&tipoEntrega, 0, 1, "Tipo de entrega!\n0-Regular\n1-Urgente\nEscolha a sua opção: ");

    readInt(&numeroArtigos, 1, 100, "Numero de artigos que pretende enviar: ");
    while (i < numeroArtigos) {
        printf("\n\n Peso do %dº Artigo (Kg): ", i + 1);
        readFloat(&peso, 0, 20, "");
        pesoTotal += peso;
        printf("\n Volume do %d º Artigo (m3) :", i + 1);
        readFloat(&volume, 0, 5, "");
        volumeTotal += volume;

        i++;
    }
    readInt(&tratamentoEspecial, 0, 1,
            "Necessita de tratamento especial?\n0-Não\n1-Sim\nEscolha a sua opção: ");

    printf("\n\n");

    precoTotal += tabela.custoPorQuilometro*numKM;
    printf("Custo relativo distância em km's :\t(+) %.2f EUR\n", (tabela.custoPorQuilometro * numKM));
    if (tipoEntrega == 0) {
        precoTotal += tabela.custoRegular;
        printf("Custo encomenda regular :\t\t(+) %.2f EUR\n", tabela.custoRegular);
    } else {
        precoTotal += tabela.custoUrgente;
        printf("Custo encomenda urgente :\t\t(+) %.2f EUR\n", tabela.custoUrgente);
    }

    if (pesoTotal > 20) {
        precoTotal += tabela.custoPesado;
        printf("Custo encomenda pesada(+20kgs)  :\t(+) %.2f EUR \n", tabela.custoPesado);
    }

    if (volumeTotal > 0.125) {
        precoTotal += tabela.custoVolumoso;
        printf("Custo encomenda volumosa(+0.125) :\t(+) %.2f EUR\n", tabela.custoVolumoso);
    }
    if (tratamentoEspecial == 1) {
        precoTotal += tabela.custoFragil;
        printf("Custo encomenda com conteúdo frágil :\t(+) %.2f EUR\n", tabela.custoFragil);
    }

    precoTotal = precoTotal * (tabela.custoCodigoPostal[codPostalOrigem][codPostalDestino]);
    printf("Custo fator código postal :\t \t(*) %.2f EUR\n", tabela.custoCodigoPostal[codPostalOrigem][codPostalDestino]);

    printf("TOTAL=\t\t\t%.2f EUR\n", precoTotal);

}
/**
 * 
 * Esta função serve para pesquisar um cliente atraés do seu cc.
 * 
 * @param lista este parâmetro é a lista de todos os clientes existentes.
 * @param nClientes este parâmetro é o numero de clientes existentes (contador).
 */
void pesquisaCC(struct Cliente *lista, int nClientes) {
    int i = 0, cc;

    if (nClientes==0)
        printf("Não existem clientes na base de dados!\n");
    else
    {
    readInt(&cc, 10000000, 99999999, "Introduza o nº do cartão de cidadão: ");

    while (i < nClientes && lista[i].cc != cc)
        i++;

    if (i == nClientes)
        printf("Não existe nenhum número de CC na base de dados!\n");
    else {
        printf("Nome: %s\n", lista[i].nome);
        printf("NIF: %d\n", lista[i].nif);
        printf("Cartão de Cidadão: %d\n", lista[i].cc);
        printf("Morada:\n");
        printf("\tRua: %s\n", lista[i].morada.rua);
        printf("\tLocalidade: %s\n", lista[i].morada.localidade);
        printf("\tNúmero da Porta: %d\n", lista[i].morada.numero);
        printf("\tCódigo Postal: %d\n", lista[i].morada.codigoPostal);
        printf("\tPaís: %s\n", lista[i].morada.pais);
    }
}
}


/**
 * 
 * Esta função serve para o cliente enviar o seu feedback do transpor ao diretor.
 * 
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param codigoEncomenda este parâmetro é o codigo da encomenda relativa ao feedback.
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param nif este parâmetro é o nif do cliente que envia o feedback.
 */
void notas(struct Encomenda *arrayEncomendas, int codigoEncomenda, int contadorEncomendas, int nif) {
    int res, i, encontrado = 0;
    if (contadorEncomendas==0)
        printf("Não existem encomendas registadas no sistema!");
    else
    {
    readInt(&res, 1000, codigoEncomenda - 1, "(Atenção! Apenas pode submeter notas de encomendas já expedidas!)\n "
            "Introduza o número da encomenda:");

    while (i < contadorEncomendas && encontrado == 0) {
        if (arrayEncomendas[i].codigo == res && arrayEncomendas[i].nifCliente == nif &&
                arrayEncomendas[i].expedida == 1) {
            if (arrayEncomendas[i].notas.recebida == 1)
                printf("A sua mensagem já foi enviada e recebida pelo diretor!\n");
            else if (arrayEncomendas[i].notas.enviada == 1)
                printf("Já foi enviada uma sugestão/reclamação do processo de envio da encomenda!\n");
            else {
                readString(arrayEncomendas[i].notas.texto, 150, "Escreva a sugestão/reclamação "
                        "relativamente ao processo de envio da encomenda:");
                printf("Agradecemos o seu feedback! Obrigado.\n");
                arrayEncomendas[i].notas.enviada = 1;
                encontrado = 1;
            }
        }
        i++;
    }
    if (encontrado == 0)
        printf("Não tem permissões para comentar a encomenda!\n");
}
}

/**
 * 
 * Esta função serve para o diretor ver todo o feedback existente às encomendas.
 * 
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 */
void mostraNotas(struct Encomenda *arrayEncomendas, int contadorEncomendas) {

    int i = 0, cont = 0, res, alterado = 0;
    while (i < contadorEncomendas) {
        if (arrayEncomendas[i].expedida == 1 && arrayEncomendas[i].notas.enviada == 1
                && arrayEncomendas[i].notas.recebida == 0) {
            cont++;
            printf("-----Mensagem %d-----", cont);
            printf("Código da encomenda: %d \n", arrayEncomendas[i].codigo);
            printf("NIF do cliente: %d \n", arrayEncomendas[i].nifCliente);
            printf("Mensagem: \n %s \n\n", arrayEncomendas[i].notas.texto);

        }
        i++;
    }
    if (cont == 0)
        printf("Não existem mensagens novas de clientes!\n ");
    else {
        readInt(&i, 0, 1, "Quer marcar alguma mensagem como lida? (1-Sim 0-Não): ");
        if (i == 1) {
            readInt(&res, 1000, 100000, "Introduza o código da encomenda?");
            i = 0;
            while (i < contadorEncomendas) {
                if (arrayEncomendas[i].codigo == res && arrayEncomendas[i].expedida == 1
                        && arrayEncomendas[i].notas.enviada == 1
                        && arrayEncomendas[i].notas.recebida == 0) {
                    arrayEncomendas[i].notas.recebida = 1;
                    alterado = 1;
                }
                i++;
            }
            if (alterado == 0)
                printf("Não é possível marcar a mensagem como lida.Verifique o código da encomenda!\n");
            else
                printf("Marcada como lida!\n");
        }
    }
}

/**
 * 
 * Esta função serve para carregar os dados da base de dados ou entao carregar o seedData.
 * 
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 * @param tabelaPreco este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 * @param tamanho é o tamanho de memoria alocada para a lista de clientes.
 * @param tamanhoEncomendas é o tamanho de memoria alocada para a lista de encomendas.
 * @param codigoEncomenda este parâmetro é o último código existente na lista encomendas.
 */
void chamarDados(struct Encomenda **arrayEncomendas, int * contadorEncomendas, struct Cliente **arrayClientes,
        int *contadorClientes, struct Custo *tabelaPrecos, int *tamanho, int *tamanhoEncomendas, int *codigoEncomenda) {

    int i = 0, escolha;

    if (carregarInformacao("basededados.dat", arrayEncomendas, contadorEncomendas,
            arrayClientes, contadorClientes, tabelaPrecos, tamanho, tamanhoEncomendas)) {

        printf("Dados carregados da base de dados com sucesso!\n");
        if ((*contadorEncomendas) == 0)
            (*codigoEncomenda) = 1000;
        else 
            (*codigoEncomenda) = (*arrayEncomendas)[*contadorEncomendas - 1].codigo + 1;       
    } else {
        (*codigoEncomenda) = 1000;
        printf("Erro no carregamento da informação da base de dados\n");
        (*arrayClientes) = (struct Cliente *) malloc(sizeof (struct Cliente)*TAMANHO_ARRAY_INICIAL);
        (*tamanho) = TAMANHO_ARRAY_INICIAL;
        if ((*arrayClientes) == NULL)
            printf("Erro ao alocar memoria!Vai sair do programa!\n");
        else {
            readInt(&escolha, 0, 1, "Deseja carregar o seedData?\n0-Não\n1-Sim\n Escolha a sua opção: ");
            if (escolha == 1) {
                seedDataClientes(arrayClientes, contadorClientes);
                (*arrayEncomendas) = (struct Encomenda *) malloc(sizeof (struct Encomenda)*TAMANHO_ARRAY_INICIAL);
                (*tamanhoEncomendas) = TAMANHO_ARRAY_INICIAL;
                if ((*arrayEncomendas) == NULL) {
                    printf("Erro ao alocar memoria!Vai sair do programa!\n");
                    free(*arrayClientes);
                } else {
                    seedDataTabela(tabelaPrecos);

                }
            }
        }
    }
}

/**
 * 
 * Esta função serve para gerar dados de clientes, caso não haja dados na base de dados.
 * 
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 */
void seedDataClientes(struct Cliente **arrayClientes, int *contadorClientes) {
    (*arrayClientes)[*contadorClientes].nif = 111111111;
    (*arrayClientes)[*contadorClientes].cc = 11111111;
    strcpy((*arrayClientes)[*contadorClientes].nome, "Leandro");
    strcpy((*arrayClientes)[*contadorClientes].password, "ronaldo");
    (*arrayClientes)[*contadorClientes].removido = 0;
    (*arrayClientes)[*contadorClientes].morada.codigoPostal = 1234567;
    (*arrayClientes)[*contadorClientes].morada.numero = 205;
    strcpy((*arrayClientes)[*contadorClientes].morada.localidade, "Porto");
    strcpy((*arrayClientes)[*contadorClientes].morada.rua, "Rua Verde");
    strcpy((*arrayClientes)[*contadorClientes].morada.pais, "Portugal");
    (*contadorClientes)++;

    (*arrayClientes)[*contadorClientes].nif = 222222222;
    (*arrayClientes)[*contadorClientes].cc = 11111111;
    strcpy((*arrayClientes)[*contadorClientes].nome, "Diogo");
    strcpy((*arrayClientes)[*contadorClientes].password, "ronaldo");
    (*arrayClientes)[*contadorClientes].removido = 0;
    (*arrayClientes)[*contadorClientes].morada.codigoPostal = 1234567;
    (*arrayClientes)[*contadorClientes].morada.numero = 205;
    strcpy((*arrayClientes)[*contadorClientes].morada.localidade, "Porto");
    strcpy((*arrayClientes)[*contadorClientes].morada.rua, "Rua Verde");
    strcpy((*arrayClientes)[*contadorClientes].morada.pais, "Portugal");
    (*contadorClientes)++;

    (*arrayClientes)[*contadorClientes].nif = 333333333;
    (*arrayClientes)[*contadorClientes].cc = 11111111;
    strcpy((*arrayClientes)[*contadorClientes].nome, "Pedro");
    strcpy((*arrayClientes)[*contadorClientes].password, "ronaldo");
    (*arrayClientes)[*contadorClientes].removido = 0;
    (*arrayClientes)[*contadorClientes].morada.codigoPostal = 1234567;
    (*arrayClientes)[*contadorClientes].morada.numero = 205;
    strcpy((*arrayClientes)[*contadorClientes].morada.localidade, "Porto");
    strcpy((*arrayClientes)[*contadorClientes].morada.rua, "Rua Verde");
    strcpy((*arrayClientes)[*contadorClientes].morada.pais, "Portugal");
    (*contadorClientes)++;

    (*arrayClientes)[*contadorClientes].nif = 444444444;
    (*arrayClientes)[*contadorClientes].cc = 11111111;
    strcpy((*arrayClientes)[*contadorClientes].nome, "Duarte");
    strcpy((*arrayClientes)[*contadorClientes].password, "ronaldo");
    (*arrayClientes)[*contadorClientes].removido = 0;
    (*arrayClientes)[*contadorClientes].morada.codigoPostal = 1234567;
    (*arrayClientes)[*contadorClientes].morada.numero = 205;
    strcpy((*arrayClientes)[*contadorClientes].morada.localidade, "Porto");
    strcpy((*arrayClientes)[*contadorClientes].morada.rua, "Rua Verde");
    strcpy((*arrayClientes)[*contadorClientes].morada.pais, "Portugal");
    (*contadorClientes)++;

    (*arrayClientes)[*contadorClientes].nif = 555555555;
    (*arrayClientes)[*contadorClientes].cc = 11111111;
    strcpy((*arrayClientes)[*contadorClientes].nome, "Alice");
    strcpy((*arrayClientes)[*contadorClientes].password, "ronaldo");
    (*arrayClientes)[*contadorClientes].removido = 0;
    (*arrayClientes)[*contadorClientes].morada.codigoPostal = 1234567;
    (*arrayClientes)[*contadorClientes].morada.numero = 205;
    strcpy((*arrayClientes)[*contadorClientes].morada.localidade, "Porto");
    strcpy((*arrayClientes)[*contadorClientes].morada.rua, "Rua Verde");
    strcpy((*arrayClientes)[*contadorClientes].morada.pais, "Portugal");
    (*contadorClientes)++;


}


/**
 * 
 * Esta função serve para gerar dados da tabeal de custos, caso não haja na base de dados.
 * 
 * @param tabelaPrecos este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 */
void seedDataTabela(struct Custo * tabelaPrecos) {
    (*tabelaPrecos).custoCodigoPostal[0][0] = 1;
    (*tabelaPrecos).custoCodigoPostal[0][1] = 1;
    (*tabelaPrecos).custoCodigoPostal[0][2] = 1;
    (*tabelaPrecos).custoCodigoPostal[0][3] = 1;
    (*tabelaPrecos).custoCodigoPostal[0][4] = 1;
    (*tabelaPrecos).custoCodigoPostal[0][5] = 1;
    (*tabelaPrecos).custoCodigoPostal[0][6] = 1;
    (*tabelaPrecos).custoCodigoPostal[0][7] = 1;
    (*tabelaPrecos).custoCodigoPostal[0][8] = 1;

    (*tabelaPrecos).custoCodigoPostal[1][0] = 1;
    (*tabelaPrecos).custoCodigoPostal[1][1] = 1;
    (*tabelaPrecos).custoCodigoPostal[1][2] = 1;
    (*tabelaPrecos).custoCodigoPostal[1][3] = 1;
    (*tabelaPrecos).custoCodigoPostal[1][4] = 1;
    (*tabelaPrecos).custoCodigoPostal[1][5] = 1;
    (*tabelaPrecos).custoCodigoPostal[1][6] = 1;
    (*tabelaPrecos).custoCodigoPostal[1][7] = 1;
    (*tabelaPrecos).custoCodigoPostal[1][8] = 1;

    (*tabelaPrecos).custoCodigoPostal[2][0] = 1;
    (*tabelaPrecos).custoCodigoPostal[2][1] = 1;
    (*tabelaPrecos).custoCodigoPostal[2][2] = 1;
    (*tabelaPrecos).custoCodigoPostal[2][3] = 1;
    (*tabelaPrecos).custoCodigoPostal[2][4] = 1;
    (*tabelaPrecos).custoCodigoPostal[2][5] = 1;
    (*tabelaPrecos).custoCodigoPostal[2][6] = 1;
    (*tabelaPrecos).custoCodigoPostal[2][7] = 1;
    (*tabelaPrecos).custoCodigoPostal[2][8] = 1;

    (*tabelaPrecos).custoCodigoPostal[3][0] = 1;
    (*tabelaPrecos).custoCodigoPostal[3][1] = 1;
    (*tabelaPrecos).custoCodigoPostal[3][2] = 1;
    (*tabelaPrecos).custoCodigoPostal[3][3] = 1;
    (*tabelaPrecos).custoCodigoPostal[3][4] = 1;
    (*tabelaPrecos).custoCodigoPostal[3][5] = 1;
    (*tabelaPrecos).custoCodigoPostal[3][6] = 1;
    (*tabelaPrecos).custoCodigoPostal[3][7] = 1;
    (*tabelaPrecos).custoCodigoPostal[3][8] = 1;

    (*tabelaPrecos).custoCodigoPostal[4][0] = 1;
    (*tabelaPrecos).custoCodigoPostal[4][1] = 1;
    (*tabelaPrecos).custoCodigoPostal[4][2] = 1;
    (*tabelaPrecos).custoCodigoPostal[4][3] = 1;
    (*tabelaPrecos).custoCodigoPostal[4][4] = 1;
    (*tabelaPrecos).custoCodigoPostal[4][5] = 1;
    (*tabelaPrecos).custoCodigoPostal[4][6] = 1;
    (*tabelaPrecos).custoCodigoPostal[4][7] = 1;
    (*tabelaPrecos).custoCodigoPostal[4][8] = 1;

    (*tabelaPrecos).custoCodigoPostal[5][0] = 1;
    (*tabelaPrecos).custoCodigoPostal[5][1] = 1;
    (*tabelaPrecos).custoCodigoPostal[5][2] = 1;
    (*tabelaPrecos).custoCodigoPostal[5][3] = 1;
    (*tabelaPrecos).custoCodigoPostal[5][4] = 1;
    (*tabelaPrecos).custoCodigoPostal[5][5] = 1;
    (*tabelaPrecos).custoCodigoPostal[5][6] = 1;
    (*tabelaPrecos).custoCodigoPostal[5][7] = 1;
    (*tabelaPrecos).custoCodigoPostal[5][8] = 1;

    (*tabelaPrecos).custoCodigoPostal[6][0] = 1;
    (*tabelaPrecos).custoCodigoPostal[6][1] = 1;
    (*tabelaPrecos).custoCodigoPostal[6][2] = 1;
    (*tabelaPrecos).custoCodigoPostal[6][3] = 1;
    (*tabelaPrecos).custoCodigoPostal[6][4] = 1;
    (*tabelaPrecos).custoCodigoPostal[6][5] = 1;
    (*tabelaPrecos).custoCodigoPostal[6][6] = 1;
    (*tabelaPrecos).custoCodigoPostal[6][7] = 1;
    (*tabelaPrecos).custoCodigoPostal[6][8] = 1;

    (*tabelaPrecos).custoCodigoPostal[7][0] = 1;
    (*tabelaPrecos).custoCodigoPostal[7][1] = 1;
    (*tabelaPrecos).custoCodigoPostal[7][2] = 1;
    (*tabelaPrecos).custoCodigoPostal[7][3] = 1;
    (*tabelaPrecos).custoCodigoPostal[7][4] = 1;
    (*tabelaPrecos).custoCodigoPostal[7][5] = 1;
    (*tabelaPrecos).custoCodigoPostal[7][6] = 1;
    (*tabelaPrecos).custoCodigoPostal[7][7] = 1;
    (*tabelaPrecos).custoCodigoPostal[7][8] = 1;

    (*tabelaPrecos).custoCodigoPostal[8][0] = 1;
    (*tabelaPrecos).custoCodigoPostal[8][1] = 1;
    (*tabelaPrecos).custoCodigoPostal[8][2] = 1;
    (*tabelaPrecos).custoCodigoPostal[8][3] = 1;
    (*tabelaPrecos).custoCodigoPostal[8][4] = 1;
    (*tabelaPrecos).custoCodigoPostal[8][5] = 1;
    (*tabelaPrecos).custoCodigoPostal[8][6] = 1;
    (*tabelaPrecos).custoCodigoPostal[8][7] = 1;
    (*tabelaPrecos).custoCodigoPostal[8][8] = 1;

    (*tabelaPrecos).custoFragil = 2;
    (*tabelaPrecos).custoRegular = 2;
    (*tabelaPrecos).custoUrgente = 2;
    (*tabelaPrecos).custoVolumoso = 2;
    (*tabelaPrecos).custoPesado = 2;
    (*tabelaPrecos).custoPorQuilometro = 0.47;
}








