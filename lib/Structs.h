/** 
 * @file
 * @author Leandro
 *
 * @brief Biblioteca com todas as estruturas necessárias.
 *
 */
#ifndef STRUCTS_H
#define STRUCTS_H
#define TAMANHOS_STRINGS 20
#define TAMANHO_ARRAY_ARTIGOS 20

struct Morada {
    char rua[TAMANHOS_STRINGS];
    int numero;
    char localidade[TAMANHOS_STRINGS];
    int codigoPostal;
    char pais[TAMANHOS_STRINGS];
};

struct Cliente {
    char nome[TAMANHOS_STRINGS];
    int nif;
    int cc;
    struct Morada morada;
    int removido;
    char password[TAMANHOS_STRINGS];
    int avisoExpedicao;
    int avisoAlteracaoTabelaPrecos;
};

struct Artigo {
    char nome[TAMANHOS_STRINGS];
    float peso;
    float volume;
    int tratamentoEspecial;
};
struct Data{
    int ano;
    int mes;
    int dia;
    int hora;
    int minutos;
};

struct Notas{
    int recebida;
    int enviada;
    char texto[150];
};

struct Encomenda {
    int codigo;
    int nifCliente;
    struct Artigo *artigos;
    int origem;
    int destino;
    float peso;
    int tipoEntrega;
    int contadorArtigos;
    int expedida;
    struct Data dataEncomendaEfetuada;
    struct Data dataEncomendaExpedida;
    int numKm;
    int contemFragil;
    float volume;
    float precoEncomenda;
    struct Notas notas;

};
struct Custo{
    float custoCodigoPostal[9][9];
    float custoRegular;
    float custoUrgente;
    float custoVolumoso;
    float custoFragil;
    float custoPesado;
    float custoPorQuilometro;
};

#endif	// STRUCTS_H

