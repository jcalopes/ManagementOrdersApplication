/** 
 * @file
 * @author Leandro
 *
 * @brief Biblioteca com funções para gestão de encomendas.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


#include "API_Leitura.h"
#include "API_Utils.h"
#include "FuncoesGerais.h"

#include "GestaoEncomendas.h"

#define TAMANHO_AUMENTA_REALLOC 20
#define TAMANHO_STRINGS 20

/**
 * 
 * Esta função serve para o cliente criar/registar uma encomenda.
 * 
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param tamanhoEncomendas este parâmetro é o tamanho da memória disponível para as encomendas.
 * @param nif este parâmetro  é o nif do cliente que vai realizar a encomenda. 
 * @param codigoEncomenda este parâmetro é o próximo código disponível da encomenda a ser criada.
 * @param tabelaPrecos este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 */
void criarEncomenda(struct Encomenda **arrayEncomendas, int *contadorEncomendas, 
        int *tamanhoEncomendas, int nif, int *codigoEncomenda,struct Custo tabelaPrecos) {
    struct Encomenda *apontador_temporario;
    int i = 0;

    if (*contadorEncomendas == *tamanhoEncomendas) {
        apontador_temporario = (struct Encomenda *) realloc(*arrayEncomendas, 
                sizeof (struct Encomenda)* ((*tamanhoEncomendas) + TAMANHO_AUMENTA_REALLOC));
        if (apontador_temporario != NULL) {
            *tamanhoEncomendas += TAMANHO_AUMENTA_REALLOC;
            (*arrayEncomendas) = apontador_temporario;
            printf("Foi realocada memória!\n");
            
        } else 
            printf("Erro de memória!Não é possível criar uma encomenda.\n");
    } 
    
    pedirDadosEncomenda(arrayEncomendas, contadorEncomendas, tamanhoEncomendas, nif, codigoEncomenda, tabelaPrecos);
    
}

/**
 * 
 * Esta função serve para o cliente listar todas as suas encomendas.
 * 
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param nif  este parâmetro  é o nif do cliente que requer a listagem das encomendas.
 */
void listarEncomendas(struct Encomenda* arrayEncomendas, int contadorEncomendas, int nif) {
    int i = 0, j = 0, contadorMinhasEncomendas = 0;
    if (contadorEncomendas == 0) {
        printf("Não tem encomendas efetuadas!\n");
    } else {
        printf("------------------------------------\n");
        printf("SUAS ENCOMENDAS\n");
        printf("------------------------------------\n");
        while (i < contadorEncomendas) {
            if (arrayEncomendas[i].nifCliente == nif) {
                printf("\n-------Encomenda número %d-------\n", arrayEncomendas[i].codigo);

                printf("\nExistem %d artigos: \n", arrayEncomendas[i].contadorArtigos);
                while (j < arrayEncomendas[i].contadorArtigos) {

                    printf("\tNome artigo: %s\n", arrayEncomendas[i].artigos[j].nome);
                    printf("\tPeso artigo: %0.3f\n", arrayEncomendas[i].artigos[j].peso);
                    printf("\tVolume artigo: %0.3f\n", arrayEncomendas[i].artigos[j].volume);
                    if (arrayEncomendas[i].artigos[j].tratamentoEspecial == 0) {
                        printf("\tFrágil: Não\n");
                    } else {
                        printf("\tFrági: Sim\n");
                    }
                    printf("\n");
                    j++;
                }
                j = 0;

                printf("\n");
                printf("Código Postal Origem: %d\n", arrayEncomendas[i].origem);
                printf("Código Postal Destino: %d\n", arrayEncomendas[i].destino);
                printf("Peso Total Encomenda: %.2f Kg\n", arrayEncomendas[i].peso);
                printf("Volume Total Encomenda: %.2f m3\n", arrayEncomendas[i].volume);

                if (arrayEncomendas[i].contemFragil == 0) 
                    printf("Tratamento Especial: Não necessita\n");
                else 
                    printf("Tratamento Especial: Frágil\n");
                

                if (arrayEncomendas[i].tipoEntrega == 0) {
                    printf("Tipo de Transporte: Regular\n");
                } else {
                    printf("Tipo de Transporte: Urgente\n");
                }
                printf("\nEncomenda efetuada no dia %d-%d-%d, às %d:%dh\n", arrayEncomendas[i].dataEncomendaEfetuada.dia,
                        arrayEncomendas[i].dataEncomendaEfetuada.mes, arrayEncomendas[i].dataEncomendaEfetuada.ano,
                        arrayEncomendas[i].dataEncomendaEfetuada.hora, arrayEncomendas[i].dataEncomendaEfetuada.minutos);
                contadorMinhasEncomendas++;

                if (arrayEncomendas[i].expedida == 0) {
                    printf("\n[AVISO] Encomenda ainda não expedida!\n");
                } else {
                    printf("\nEncomenda expedida no dia %d-%d-%d, às %d:%dh\n", arrayEncomendas[i].dataEncomendaExpedida.dia,
                            arrayEncomendas[i].dataEncomendaExpedida.mes, arrayEncomendas[i].dataEncomendaExpedida.ano,
                            arrayEncomendas[i].dataEncomendaExpedida.hora, arrayEncomendas[i].dataEncomendaExpedida.minutos);
                }

            }
            i++;
        }
        if (contadorMinhasEncomendas == 0) {
            printf("Não tem encomendas efetuadas!\n");
        }
    }
}

/**
 * 
 * Esta função serve para pedir os dados da encomenda a ser criada/registada(é chamada na funcão criarEncomenda).
 * 
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param tamanhoEncomendas este parâmetro é o tamanho da memória disponível para as encomendas.
 * @param nif este parâmetro  é o nif do cliente que vai realizar a encomenda. 
 * @param codigoEncomenda este parâmetro é o próximo código disponível da encomenda a ser criada.
 * @param tabelaPrecos este parâmetro é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 */
void pedirDadosEncomenda(struct Encomenda **arrayEncomendas, int *contadorEncomendas,
        int *tamanhoEncomendas, int nif, int *codigoEncomenda, struct Custo tabelaPrecos) {

    int numeroArtigos, contadorArtigos = 0, contadorFragil = 0, origem, destino;
    float precoTotal = 0;

    time_t myTime = time(NULL);
    struct tm data;
    data = *localtime(&myTime);
    
    (*arrayEncomendas)[*contadorEncomendas].dataEncomendaEfetuada.ano = (data.tm_year) + 1900;
    (*arrayEncomendas)[*contadorEncomendas].dataEncomendaEfetuada.mes = (data.tm_mon) + 1;
    (*arrayEncomendas)[*contadorEncomendas].dataEncomendaEfetuada.dia = (data.tm_mday);
    (*arrayEncomendas)[*contadorEncomendas].dataEncomendaEfetuada.hora = (data.tm_hour);
    (*arrayEncomendas)[*contadorEncomendas].dataEncomendaEfetuada.minutos = (data.tm_min);

    (*arrayEncomendas)[*contadorEncomendas].codigo = (*codigoEncomenda);
    (*arrayEncomendas)[*contadorEncomendas].nifCliente = nif;
    (*arrayEncomendas)[*contadorEncomendas].expedida = 0;

    readInt(&(*arrayEncomendas)[*contadorEncomendas].origem, 1000000, 9999999, "Por favor introduza o código postal de origem: (ex:9999999) ");
    readInt(&(*arrayEncomendas)[*contadorEncomendas].destino, 1000000, 9999999, "Por favor introduza o código postal de destino: (ex:9999999)");

    origem = (*arrayEncomendas)[*contadorEncomendas].origem / 1000000;
    destino = (*arrayEncomendas)[*contadorEncomendas].destino / 1000000;
    precoTotal += tabelaPrecos.custoCodigoPostal[origem - 1][origem - 1];

    readInt(&(*arrayEncomendas)[*contadorEncomendas].numKm, 1, 10000, "Por favor introduza o número de quilometros entre a origem e o destino: ");
    precoTotal += (*arrayEncomendas)[*contadorEncomendas].numKm * tabelaPrecos.custoPorQuilometro;

    readInt(&(*arrayEncomendas)[*contadorEncomendas].tipoEntrega, 0, 1, "Tipo de entrega!\n0-Regular\n1-Urgente\nEscolha a sua opção: ");
    if ((*arrayEncomendas)[*contadorEncomendas].tipoEntrega == 0) 
        precoTotal += tabelaPrecos.custoRegular;
    else 
        precoTotal += tabelaPrecos.custoUrgente;
    
    readInt(&numeroArtigos, 1, 100, "Numero de artigos que pretende enviar: ");
    (*arrayEncomendas)[*contadorEncomendas].contadorArtigos = numeroArtigos;
    
    (*arrayEncomendas)[*contadorEncomendas].artigos = (struct Artigo*) malloc(numeroArtigos * sizeof (struct Artigo));
    if ((*arrayEncomendas)[*contadorEncomendas].artigos == NULL) {
        printf("Erro ao alocar memoria!Não foi possivel criar a encomenda.\n");

    } else {
        while (contadorArtigos < numeroArtigos) {
            readString((*arrayEncomendas)[*contadorEncomendas].artigos[contadorArtigos].nome, TAMANHO_STRINGS, "Nome do Artigo: ");
            readFloat(&(*arrayEncomendas)[*contadorEncomendas].artigos[contadorArtigos].peso, 0, 100, "Peso do Artigo: ");
            readFloat(&(*arrayEncomendas)[*contadorEncomendas].artigos[contadorArtigos].volume, 0, 5, "Volume do Artigo: ");
            readInt(&(*arrayEncomendas)[*contadorEncomendas].artigos[contadorArtigos].tratamentoEspecial, 0, 1,
                    "Necessita de tratamento especial?\n0-Não\n1-Sim\nEscolha a sua opção: ");
            (*arrayEncomendas)[*contadorEncomendas].peso += (*arrayEncomendas)[*contadorEncomendas].artigos[contadorArtigos].peso;
            (*arrayEncomendas)[*contadorEncomendas].volume += (*arrayEncomendas)[*contadorEncomendas].artigos[contadorArtigos].volume;

            if ((*arrayEncomendas)[*contadorEncomendas].artigos[contadorArtigos].tratamentoEspecial == 1) {
                contadorFragil++;
            }
            contadorArtigos++;
        }
        if ((*arrayEncomendas)[*contadorEncomendas].peso > 20) {
            precoTotal += tabelaPrecos.custoPesado;
        }
        if ((*arrayEncomendas)[*contadorEncomendas].volume > 0.125) {
            precoTotal += tabelaPrecos.custoVolumoso;
        }
    }

    if (contadorFragil != 0) {
        (*arrayEncomendas)[*contadorEncomendas].contemFragil = 1;
        precoTotal += tabelaPrecos.custoFragil;
    }
    (*arrayEncomendas)[*contadorEncomendas].precoEncomenda = precoTotal;
    (*contadorEncomendas)++;
    (*codigoEncomenda)++;

    printf("Encomenda registada!\n");
}

/**
 * 
 * Esta função serve para imprimir a fatura mensal de um ano de um determinado cliente.
 * 
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param mes este parâmetro é o mês relativo à fatura.
 * @param ano este parâmetro é o ano relativo à fatura.
 * @param nif este parâmetro é o nif do cliente da fatura.
 * @param tabelaPrecos  é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 */
void imprimirFatura(struct Encomenda* arrayEncomendas, int contadorEncomendas, int mes, int ano, int nif, struct Custo tabelaPrecos) {
    int i = 0, j = 0, mostrarCabecalho = 1, contaEncomendaData = 0,cont=0;
    float precoTotal = 0;

    //nome ficheiro fatura
    char faturaMes[TAMANHO_STRINGS];
    char faturaAno[TAMANHO_STRINGS];
    char faturaNif[TAMANHO_STRINGS];
    sprintf(faturaMes, "%d", mes);
    strcat(faturaMes, "-");
    sprintf(faturaAno, "%d", ano);
    strcat(faturaMes, faturaAno);
    sprintf(faturaNif, "%d", nif);
    strcat(faturaMes, "-");
    strcat(faturaMes, faturaNif);
    strcat(faturaMes, ".txt");

    FILE *fp;

    if (contadorEncomendas != 0) {
        while (i < contadorEncomendas) {
            if (arrayEncomendas[i].nifCliente == nif) {
                if (arrayEncomendas[i].dataEncomendaEfetuada.mes == mes && arrayEncomendas[i].dataEncomendaEfetuada.ano == ano) {
                    cont++;
                    if (cont==1){//só abre ficheiro se houver 1 encomenda
                        if ((fp = fopen(faturaMes, "w")) == NULL)
                        {
                            printf("Erro de ficheiro,não foi possível gerar fatura\n");
                            return;
                        }
                    }
                    contaEncomendaData++;
                    if (mostrarCabecalho == 1) {

                        fprintf(fp, "------------------------------------\n");
                        printf("------------------------------------\n");
                        fprintf(fp, "FATURA RELATIVA AO MÊS %d DO ANO %d\n", mes, ano);
                        printf("FATURA RELATIVA AO MÊS %d DO ANO %d\n", mes, ano);
                        printf("------------------------------------\n");
                        fprintf(fp, "------------------------------------\n");
                        mostrarCabecalho = 0;
                    }

                    printf("-------Encomenda número: %d-------\n", arrayEncomendas[i].codigo);
                    fprintf(fp, "-------Encomenda número: %d-------\n", arrayEncomendas[i].codigo);
                    printf("NIF: %d\n", nif);
                    fprintf(fp, "NIF: %d\n", nif);
                    printf("Artigos:\n");
                    fprintf(fp, "Artigos:\n");

                    while (j < arrayEncomendas[i].contadorArtigos) {

                        printf("\tNome artigo: %s\n", arrayEncomendas[i].artigos[j].nome);
                        printf("\tPeso artigo: %0.3f\n", arrayEncomendas[i].artigos[j].peso);
                        printf("\tVolume artigo: %0.3f\n", arrayEncomendas[i].artigos[j].volume);

                        fprintf(fp, "\tNome artigo: %s\n", arrayEncomendas[i].artigos[j].nome);
                        fprintf(fp, "\tPeso artigo: %0.3f\n", arrayEncomendas[i].artigos[j].peso);
                        fprintf(fp, "\tVolume artigo: %0.3f\n", arrayEncomendas[i].artigos[j].volume);

                        if (arrayEncomendas[i].artigos[j].tratamentoEspecial == 0) {
                            printf("\tFrágil: Não\n");
                            fprintf(fp, "\tFrágil: Não\n");
                        } else {
                            printf("\tFrági: Sim\n");
                            fprintf(fp, "\tFrágil: Não\n");
                        }
                        printf("\n");
                        fprintf(fp, "\n");
                        j++;
                    }
                    j = 0;

                    printf("Código Postal Origem: %d\n", arrayEncomendas[i].origem);
                    printf("Código Postal Destino: %d\n", arrayEncomendas[i].destino);
                    printf("Peso Total Encomenda: %.3f Kg\n", arrayEncomendas[i].peso);
                    printf("Volume Encomenda: %.3f Kg\n", arrayEncomendas[i].volume);

                    fprintf(fp, "Código Postal Origem: %d\n", arrayEncomendas[i].origem);
                    fprintf(fp, "Código Postal Destino: %d\n", arrayEncomendas[i].destino);
                    fprintf(fp, "Peso Total Encomenda: %.3f Kg\n", arrayEncomendas[i].peso);
                    fprintf(fp, "Volume Encomenda: %.3f Kg\n", arrayEncomendas[i].volume);

                    if (arrayEncomendas[i].contemFragil == 0) {
                        printf("Tratamento Especial: Não necessita\n");
                        fprintf(fp, "Tratamento Especial: Não necessita\n");
                    } else {
                        printf("Tratamento Especial: Frágil\n");
                        fprintf(fp, "Tratamento Especial: Frágil\n");
                    }

                    if (arrayEncomendas[i].tipoEntrega == 0) {
                        printf("Tipo de Transporte: Regular\n");
                        fprintf(fp, "Tipo de Transporte: Regular\n");
                    } else {
                        printf("Tipo de Transporte: Urgente\n");
                        fprintf(fp, "Tipo de Transporte: Urgente\n");
                    }

                    printf("Distância de viagem: %d Km\n", arrayEncomendas[i].numKm);
                    fprintf(fp, "Distância de viagem: %d Km\n", arrayEncomendas[i].numKm);

                    printf("----------------------------------------------\n");
                    printf("SubTotal: \t\t\t\t %.2f\n", arrayEncomendas[i].precoEncomenda);
                    printf("[AVISO] Preços com base na tabela de preços definida no dia que a encomenda foi efetuada!\n");

                    fprintf(fp,"----------------------------------------------\n");
                    fprintf(fp,"SubTotal: \t\t\t\t %.2f\n", arrayEncomendas[i].precoEncomenda);
                    fprintf(fp,"\n");
                    precoTotal += arrayEncomendas[i].precoEncomenda;
                
                }
            }
            i++;
        }
        if (contaEncomendaData == 0) {
            printf("[AVISO] Não existe encomendas no mês %d do ano %d\n", mes, ano);
        } else {
            printf("Valor total da fatura relativa ao mês %d do ano %d: %.2f\n",
                    mes, ano, precoTotal);
            fprintf(fp,"Valor total da fatura relativa ao mês %d do ano %d: %.2f\n",
                    mes, ano, precoTotal);
        }
        fclose(fp);

    } else
        printf("[AVISO] Não existe encomendas no mês %d do ano %d\n", mes, ano);

}

/**
 * 
 * Esta função serve para o diretor expedir uma determinada encomenda de um determinado cliente e avisa-o.
 * 
 * @param arrayEncomenda este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomenda este parâmetro é o numero de encomendas existentes (contador).
 * @param arrayClientes este parâmetro é a lista de todos os clientes existentes.
 * @param contadorClientes este parâmetro é o numero de clientes existentes (contador).
 */
void expedirEncomenda(struct Encomenda *arrayEncomenda, int contadorEncomenda, struct Cliente *arrayClientes, int contadorClientes) {
    int codigoEncomenda, i = 0, j = 0, encontrou = 0, nif;
    time_t myTime = time(NULL);
    struct tm data; //esta estrutura já vem pré-definida na bibliotece time.h
    data = *localtime(&myTime);
    
    if (contadorEncomenda==0)
        printf("Não existem encomendas registadas!\n");
    else
    {
    readInt(&codigoEncomenda, 1000, 50000, "Insira código da encomenda que pretende expedir: ");
    while (i < contadorEncomenda) {
        if (arrayEncomenda[i].codigo == codigoEncomenda) {
            nif = arrayEncomenda[i].nifCliente;
            if (arrayEncomenda[i].expedida == 1) {
                printf("A encomenda ja se encontra expedida!\n");
                encontrou = 1;
            } else {
                arrayEncomenda[i].expedida = 1;
                arrayEncomenda[i].dataEncomendaExpedida.dia = (data.tm_mday);
                arrayEncomenda[i].dataEncomendaExpedida.ano = (data.tm_year) + 1900;
                arrayEncomenda[i].dataEncomendaExpedida.mes = (data.tm_mon) + 1;
                arrayEncomenda[i].dataEncomendaExpedida.hora = (data.tm_hour);
                arrayEncomenda[i].dataEncomendaExpedida.minutos = (data.tm_min);
                while (j < contadorClientes) {
                    if (arrayClientes[j].nif == nif) {
                        arrayClientes[j].avisoExpedicao = 1;
                        break;
                    }
                    j++;
                }
                printf("A encomenda foi expedida e o cliente foi informado!\n");
                arrayEncomenda[i].notas.enviada = 0;
                arrayEncomenda[i].notas.recebida = 0;
                encontrou = 1;
            }
        }
        i++;
    }
    if (encontrou == 0)
        printf("Não existe nenhuma encomenda com o código %d\n", codigoEncomenda);
}
}

/**
 * 
 * Esta função serve para o diretor listar todas as encomendas, sejam elas, expedidas ou não expedidas.
 * 
 * @param arrayEncomenda este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomenda este parâmetro é o numero de encomendas existentes (contador).
 */
void listarTodasEncomendas(struct Encomenda* arrayEncomenda, int contadorEncomenda) {
    int i = 0, op, cont = 0;

    if (contadorEncomenda==0)
        printf("Não existem encomendas registadas!\n");
    else
    {
    printf("1-Encomendas Expedidas \n2-Encomendas Não Expedidas");
    readInt(&op, 1, 2, "Escolha a opcao:");
    if (contadorEncomenda != 0) {
        if (op == 1) {
            while (i < contadorEncomenda) {
                if (arrayEncomenda[i].expedida == 1) {
                    printf("----------------------------------\n");
                    printf("Encomenda número: %d\n", arrayEncomenda[i].codigo);
                    printf("NIF Cliende: %d\n", arrayEncomenda[i].nifCliente);
                    printf("Estado: Expedida no dia %d-%d-%d, às %d:%dh\n", 
                            arrayEncomenda[i].dataEncomendaExpedida.dia,
                            arrayEncomenda[i].dataEncomendaExpedida.mes, 
                            arrayEncomenda[i].dataEncomendaExpedida.ano,
                            arrayEncomenda[i].dataEncomendaExpedida.hora, 
                            arrayEncomenda[i].dataEncomendaExpedida.minutos);
                    cont++;
                }
                i++;
            }
            if (cont == 0)
                printf("Não existem encomendas expedidas!\n");
        } else {
            while (i < contadorEncomenda) {
                if (arrayEncomenda[i].expedida == 0) {
                    printf("----------------------------------\n");
                    printf("Encomenda número: %d\n", arrayEncomenda[i].codigo);
                    printf("NIF Cliende: %d\n", arrayEncomenda[i].nifCliente);
                    printf("Estado: Não expedida!Encomenda efetuada no dia %d-%d-%d, às %d:%dh\n",
                            arrayEncomenda[i].dataEncomendaEfetuada.dia,
                            arrayEncomenda[i].dataEncomendaEfetuada.mes, 
                            arrayEncomenda[i].dataEncomendaEfetuada.ano,
                            arrayEncomenda[i].dataEncomendaEfetuada.hora, 
                            arrayEncomenda[i].dataEncomendaEfetuada.minutos);
                    cont++;
                }
                i++;
            }
            if (cont == 0)
                printf("Não existem encomendas não expedidas!\n");
        }
    } else
        printf("Não existem encomendas registadas no sistema!\n");
}
}

/**
 * 
 * Esta função serve para o cliente remover uma encomenda sua que ainda não se encontre expedida.
 * 
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param nif este parâmetro  é o nif do cliente que vai remover a encomenda. 
 * @param codigoEncomenda este parâmetro é o código da encomenda a ser removida.
 * @return returna 1 ou 0 variante o contador de encomendas.
 */
int removerEncomenda(struct Encomenda** arrayEncomenda, int *contadorEncomendas, int nif, int *codigoEncomenda) {
    int codigoRemover, i = 0, j, k = 0;

    if ((*contadorEncomendas)==0)
    {
        printf("Não existem encomendas registadas no sistema!\n");
        return 0;
    }
    
    else
    {
    readInt(&codigoRemover, 1000, (*codigoEncomenda) - 1, "Introduza o código a remover: ");

    while (i<*contadorEncomendas) 
    {
        if ((*arrayEncomenda)[i].nifCliente == nif && (*arrayEncomenda)[i].codigo == codigoRemover 
        && (*arrayEncomenda)[i].expedida == 0)
            {
                j = i;
                while (j < (*contadorEncomendas - 1)) {
                    (*arrayEncomenda)[j].codigo = (*arrayEncomenda)[j + 1].codigo;
                    (*arrayEncomenda)[j].contadorArtigos = (*arrayEncomenda)[j + 1].contadorArtigos;
                    (*arrayEncomenda)[j].contemFragil = (*arrayEncomenda)[j + 1].contemFragil;
                    (*arrayEncomenda)[j].dataEncomendaEfetuada = (*arrayEncomenda)[j + 1].dataEncomendaEfetuada;
                    (*arrayEncomenda)[j].destino = (*arrayEncomenda)[j + 1].destino;
                    (*arrayEncomenda)[j].expedida = (*arrayEncomenda)[j + 1].expedida;
                    (*arrayEncomenda)[j].nifCliente = (*arrayEncomenda)[j + 1].nifCliente;
                    (*arrayEncomenda)[j].numKm = (*arrayEncomenda)[j + 1].numKm;
                    (*arrayEncomenda)[j].origem = (*arrayEncomenda)[j + 1].origem;
                    (*arrayEncomenda)[j].peso = (*arrayEncomenda)[j + 1].peso;
                    (*arrayEncomenda)[j].precoEncomenda = (*arrayEncomenda)[j + 1].precoEncomenda;
                    (*arrayEncomenda)[j].tipoEntrega = (*arrayEncomenda)[j + 1].tipoEntrega;
                    (*arrayEncomenda)[j].volume = (*arrayEncomenda)[j + 1].volume;

                    (*arrayEncomenda)[j].artigos = (struct Artigo*) realloc((*arrayEncomenda)[j].artigos,
                            (*arrayEncomenda)[j + 1].contadorArtigos * sizeof (struct Artigo));

                    if ((*arrayEncomenda)[j].artigos == NULL) {
                        printf("Erro de memória.Não foi possível remover a encomenda!\n");
                        return 0;
                    } else {
                        while (k < ((*arrayEncomenda)[j].contadorArtigos) - 1) {
                            strcpy((*arrayEncomenda)[j].artigos[k].nome, (*arrayEncomenda)[j + 1].artigos[k].nome);
                            (*arrayEncomenda)[j].artigos[k].peso = (*arrayEncomenda)[j + 1].artigos[k].peso;
                            (*arrayEncomenda)[j].artigos[k].tratamentoEspecial = 
                                    (*arrayEncomenda)[j + 1].artigos[k].tratamentoEspecial;
                            (*arrayEncomenda)[j].artigos[k].volume = (*arrayEncomenda)[j + 1].artigos[k].volume;
                            k++;
                        }
                    }
                    j++;
                }  
               (*contadorEncomendas)--;
               return 1; 
            }
        i++;
    }
    if (i==(*contadorEncomendas))
        return 0;
}
}

/**
 * 
 * Esta função serve para fazer uma relatorio mensal do peso e volume das encomendas(média/maior/menor).
 * 
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 */
void relatorioMediaEncomendas(struct Encomenda* arrayEncomendas, int contadorEncomendas) {
    int i = 0, cont = 0, res;
    float maiorPeso = 0, menorPeso, pesoTotal = 0, volumeTotal = 0, numKm = 0;
    struct tm data;
    time_t tempo = time(NULL);
    data = *localtime(&tempo);

    readInt(&res, 2019, data.tm_year + 1900, "Introduza o ano pretendido: ");
    menorPeso = arrayEncomendas[0].peso;
    if (contadorEncomendas != 0) {
        while (i < contadorEncomendas) {
            if (arrayEncomendas[i].expedida == 1 && arrayEncomendas[i].dataEncomendaExpedida.ano == res) {
                pesoTotal += arrayEncomendas[i].peso;
                volumeTotal += arrayEncomendas[i].volume;
                numKm += arrayEncomendas[i].numKm;
                if (arrayEncomendas[i].peso > maiorPeso) {
                    maiorPeso = arrayEncomendas[i].peso;
                }
                if (arrayEncomendas[i].peso < menorPeso) {
                    menorPeso = arrayEncomendas[i].peso;
                }
                cont++;
            }
            i++;
        }
        if (cont != 0) {
            printf("-------Estatísticas Encomendas já expedidas do ano de %d-------\n", res);
            printf("Maior Peso de uma encomenda expedida: %.3f Kg\n", maiorPeso);
            printf("Menor Peso de uma encomenda expedida: %.3f Kg\n", menorPeso);
            printf("Média de peso por encomenda: %.3f Kg\n", pesoTotal / cont);
            printf("Média de volume por encomenda: %.3f m3\n", volumeTotal / cont);
            printf("Média da distância percorridas por encomenda: %.3f Kms\n", numKm / cont);
        } else
            printf("Nenhuma encomenda expedida no ano de %d!\n", res);
    }
    else
        printf("Não existem encomendas registadas no sistema!\n");
}

/**
 * 
 * Esta função serve para o cliente fazer uma alteração numa encomenda sua que ainda não tenha sido expedida.
 * 
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param tabela  é uma estrutura "Custo" onde estão guardados todos os custos de transporte.
 * @param nif este parâmetro  é o nif do cliente que vai alterar a encomenda. 
 * @return returna 0 se algum caso especifico acontecer.
 */
int alterarEncomenda(struct Encomenda **arrayEncomendas, int contadorEncomendas, struct Custo tabela, int nif) {
    int codEncomenda, i = 0, numArtigos, j = 0, codOrigem, codDestino;
    float precoTotal = 0;
    struct tm data;
    time_t myTime = time(NULL);
    data = *localtime(&myTime);

    if (contadorEncomendas == 0) {
        printf("Não existem encomendas na base de dados!\n");
        return 0;
    } else {
        readInt(&codEncomenda, 1000, 100000, "Introduza o código relativo à encomenda a alterar: ");

        while (i < contadorEncomendas) {
            if ((*arrayEncomendas)[i].codigo == codEncomenda && (*arrayEncomendas)[i].nifCliente == nif) {
                if ((*arrayEncomendas)[i].expedida == 0) {
                    readInt(&numArtigos, 0, 100, "Introduza a quantidade de artigos da encomenda: ");
                    (*arrayEncomendas)[i].contadorArtigos = numArtigos;
                    (*arrayEncomendas)[i].artigos = (struct Artigo*) 
                            realloc((*arrayEncomendas)[i].artigos, numArtigos * sizeof (struct Artigo));
                    if ((*arrayEncomendas)[i].artigos == NULL) {
                        printf("Não foi possível alterar dados da encomenda.Erro de memória!\n");
                        return 0;
                    } else {
                        (*arrayEncomendas)[i].peso = 0;
                        (*arrayEncomendas)[i].volume = 0;
                        while (j < numArtigos) {
                            readString((*arrayEncomendas)[i].artigos[j].nome, TAMANHO_STRINGS, "Nome do Artigo: ");

                            readFloat(&(*arrayEncomendas)[i].artigos[j].peso, 0, 100, "Peso do Artigo: ");
                            (*arrayEncomendas)[i].peso += (*arrayEncomendas)[i].artigos[j].peso;

                            readFloat(&(*arrayEncomendas)[i].artigos[j].volume, 0, 5, "Volume do Artigo: ");
                            (*arrayEncomendas)[i].volume += (*arrayEncomendas)[i].artigos[j].volume;

                            readInt(&(*arrayEncomendas)[i].artigos[j].tratamentoEspecial, 0, 1,
                                    "Necessita de tratamento especial?\n0-Não\n1-Sim\nEscolha a sua opção: ");
                            if ((*arrayEncomendas)[i].artigos[j].tratamentoEspecial == 1)
                                (*arrayEncomendas)[i].contemFragil = 1;
                            j++;
                        }

                        (*arrayEncomendas)[i].dataEncomendaEfetuada.ano = data.tm_year + 1900;
                        (*arrayEncomendas)[i].dataEncomendaEfetuada.mes = data.tm_mon + 1;
                        (*arrayEncomendas)[i].dataEncomendaEfetuada.dia = data.tm_mday;
                        (*arrayEncomendas)[i].dataEncomendaEfetuada.hora = data.tm_hour;
                        (*arrayEncomendas)[i].dataEncomendaEfetuada.minutos = data.tm_min;

                        readInt(&(*arrayEncomendas)[i].origem, 1000000, 9999999, "Introduza o código postal de origem: ");
                        codOrigem = (*arrayEncomendas)[i].origem / 1000000;
                        readInt(&(*arrayEncomendas)[i].destino, 1000000, 9999999, "Introduza o código postal de destino: ");
                        codDestino = (*arrayEncomendas)[i].destino / 1000000;

                        precoTotal += tabela.custoCodigoPostal[codOrigem - 1][codDestino - 1];

                        readInt(&(*arrayEncomendas)[i].numKm, 0, 1000, "Introduza o número de quilómetros entre a origem e o destino: ");
                        precoTotal += (*arrayEncomendas)[i].numKm * tabela.custoPorQuilometro;

                        readInt(&(*arrayEncomendas)[i].tipoEntrega, 0, 1,
                                "Tipo de entrega!\n0-Regular\n1-Urgente\nEscolha a sua opção: ");

                        if ((*arrayEncomendas)[i].tipoEntrega == 1)
                            precoTotal += tabela.custoUrgente;
                        else
                            precoTotal += tabela.custoRegular;

                        if ((*arrayEncomendas)[i].peso > 20)
                            precoTotal += tabela.custoPesado;

                        if ((*arrayEncomendas)[i].volume > 0.125)
                            precoTotal += tabela.custoVolumoso;

                        if ((*arrayEncomendas)[i].contemFragil == 1)
                            precoTotal += tabela.custoFragil;
                    }

                    (*arrayEncomendas)[i].precoEncomenda = precoTotal;
                    return 1;
                } else {
                    printf("A encomenda já foi expedida!\n");
                    return 0;
                }
            }
            i++;
        }
        printf("O código da encomenda não consta na base de dados!\n");
        return 0;
    }
}

/**
 * 
 * Esta função serve para o diretor obter um relatorio de lucros de um determinado ano, sabendo qual mes lucrou mais,menos e a média.
 * 
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 */
void lucros(struct Encomenda *arrayEncomendas, int contadorEncomendas) {
    struct tm data;
    time_t tempo = time(NULL);
    data = *localtime(&tempo);

    int res, i, j, posMax = 0, posMin = 0, contEncExp = 0;
    float TotalMes, TotalAno = 0, max = 0, min = 10000;

    if (contadorEncomendas == 0)
        printf("Sem registos de encomendas!\n");
    else {
        readInt(&res, 2019, (data.tm_year) + 1900, "Introduza o ano a consultar: ");
        printf("------------------------------\n");
        printf("Ano %d\n", res);
        printf("------------------------------\n");
        for (i = 1; i < 13; i++)//meses do ano
        {
            TotalMes = 0;
            for (j = 0; j < contadorEncomendas; j++) {
                if (arrayEncomendas[j].expedida == 1 && arrayEncomendas[j].dataEncomendaExpedida.ano == res
                        && arrayEncomendas[j].dataEncomendaExpedida.mes == i) {
                    contEncExp++;
                    TotalMes += arrayEncomendas[j].precoEncomenda;
                }
            }
            TotalAno += TotalMes;
            if (TotalMes == 0)
                printf("No %d º mês de %d não tem encomendas expedidas!\n", i, res);
            else {
                printf("No %d º mês de %d facturou %.2f EUR.\n", i, res, TotalMes);
                if (TotalMes > max) {
                    max = TotalMes;
                    posMax = i;
                }

                if (TotalMes < min) {
                    min = TotalMes;
                    posMin = i;
                }
            }
        }

        if (TotalAno == 0)
            printf("Não foram efetuadas encomendas no ano de %d.\n\n", res);
        else {
            printf("- A faturação anual de %d é de %.2f EUR.\n", res, TotalAno);
            printf("- O %d º mês foi o mais lucrativo(%.2f EUR).\n - O %d º mês foi o menos lucrativo(%.2f EUR.)\n"
                    , posMax, max, posMin, min);
            printf("- A média mensal foi de %.2f EUR.\n", TotalAno / 12);
            printf("- No ano de %d, a empresa expediu,no total,%d encomendas.\n", res, contEncExp);
        }
    }

}

/**
 * 
 * Esta função serve par aum determinado cliente saber quais os seus gastos em transporte num determinadlo ano.
 * 
 * @param arrayEncomendas este parâmetro é a lista de todas as encomendas existentes.
 * @param contadorEncomendas este parâmetro é o numero de encomendas existentes (contador).
 * @param nif este parâmetro  é o nif do cliente que vai realizar a consulta de gastos. 
 */
void gastosCliente(struct Encomenda *arrayEncomendas, int contadorEncomendas, int nif) {
    struct tm data;
    time_t tempo = time(NULL);
    data = *localtime(&tempo);

    int res, i, j, contEncExp = 0;
    float TotalMes, TotalAno = 0;

    if (contadorEncomendas == 0)
        printf("Sem registos de encomendas!\n");
    else {
        readInt(&res, 2019, (data.tm_year) + 1900, "Introduza o ano a consultar: ");
        printf("------------------------------\n");
        printf("Ano %d\n", res);
        printf("------------------------------\n");
        for (i = 1; i < 13; i++)//meses do ano
        {
            TotalMes = 0;
            for (j = 0; j < contadorEncomendas; j++) {
                if (arrayEncomendas[j].nifCliente == nif && arrayEncomendas[j].expedida == 1
                        && arrayEncomendas[j].dataEncomendaExpedida.ano == res 
                        && arrayEncomendas[j].dataEncomendaExpedida.mes == i) {
                    contEncExp++;
                    TotalMes += arrayEncomendas[j].precoEncomenda;
                }

            }
            TotalAno += TotalMes;
            if (TotalMes == 0)
                printf("0.00 EUR \n");
            else
                printf("%d º mês gastou %.2f EUR.\n", i, TotalMes);
        }

        if (TotalAno == 0)
            printf("Nenhuma encomenda expedida em %d!\n\n", res);
        else
            printf("Gastos relativamente ao ano de %d são de %.2f EUR.\n", res, TotalAno);
    }
}



