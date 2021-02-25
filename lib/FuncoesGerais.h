/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Utils.h
 * Author: Leandro
 *
 * Created on 11 de Dezembro de 2019, 9:47
 */

#include "Structs.h"
#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif
    
    
    int guardarInformacao(char* , struct Encomenda *, int,
        struct Cliente *, int , struct Custo,int , int);
    int carregarInformacao(char* , struct Encomenda **, int *,
        struct Cliente **, int *, struct Custo *,int *,int *);



#ifdef __cplusplus
}
#endif

#endif /* UTILS_H */

