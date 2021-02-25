/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GestaoTabelaPrecos.h
 * Author: Leandro
 *
 * Created on 16 de Dezembro de 2019, 14:08
 */

#ifndef GESTAOENCOMENDAS_H
#define GESTAOENCOMENDAS_H

#include "Structs.h"

#include "GestaoTabelaPrecos.h"


#ifdef __cplusplus
extern "C" {
#endif

    void criarEncomenda(struct Encomenda **, int*, int *, int, int *, struct Custo);

    void listarEncomendas(struct Encomenda*, int, int);

    void pedirDadosEncomenda(struct Encomenda **, int *,
            int *, int, int *, struct Custo);

    void imprimirFatura(struct Encomenda*, int, int, int, int, struct Custo);

    void expedirEncomenda(struct Encomenda *, int,struct Cliente *,int);
    void listarTodasEncomendas(struct Encomenda*, int);
    
    int removerEncomenda(struct Encomenda** , int * , int ,int *);
    
    void relatorioMediaEncomendas(struct Encomenda* ,int);
    
    int alterarEncomenda(struct Encomenda **,int,struct Custo,int);
    
    void lucros(struct Encomenda *,int);
    
    void gastosCliente(struct Encomenda *,int,int);

#ifdef __cplusplus
}
#endif

#endif /* GESTAOENCOMENDAS_H */

