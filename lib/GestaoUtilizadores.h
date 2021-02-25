/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GestaoUtilizadores.h
 * Author: Leandro
 *
 * Created on 10 de Dezembro de 2019, 14:50
 */

#ifndef GESTAOUTILIZADORES_H
#define GESTAOUTILIZADORES_H


#include "GestaoEncomendas.h"

#ifdef __cplusplus
extern "C" {
#endif
    
void subMenuCliente(struct Cliente **, struct Encomenda **,struct Custo ,
        int *,int *,int *,int *,int*);
    
void criar(struct Cliente** , int*,int*);

void login(struct Cliente **,struct Encomenda **,struct Custo,
        int *,int *,int *,int *);

void menu(struct Cliente **,struct Encomenda **,struct Custo *,
        int *,int *,int *,int * ,int*);

void existeNIF(struct Cliente*, int, int*, int);
void listarTodos(struct Cliente*, int);
void pedirDados(struct Cliente*, int,int);

void menuClienteLogado(struct Cliente **,struct Encomenda **, struct Custo,
        int *,int * , int posicao,int *,int *);

void alterarDados(struct Cliente*, int);

void subMenuDiretor(struct Cliente**,struct Encomenda**,int*,struct Custo *,int*,int *,int *);
void ativarCliente(struct Cliente*,int);
void pesquisaNIF(struct Cliente*,int);
void orcamento(struct Custo );
void pesquisaCC(struct Cliente *,int);
void notas(struct Encomenda *,int,int,int );
void mostraNotas(struct Encomenda *,int);
void chamarDados(struct Encomenda **, int * , struct Cliente **,
        int *, struct Custo *, int *, int *, int *);

void seedDataTabela(struct Custo *);
void seedDataClientes(struct Cliente **, int *);


#ifdef __cplusplus
}
#endif

#endif /* GESTAOUTILIZADORES_H */

