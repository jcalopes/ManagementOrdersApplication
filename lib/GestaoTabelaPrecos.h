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

#ifndef GESTAOTABELAPRECOS_H
#define GESTAOTABELAPRECOS_H
#include "Structs.h"


#ifdef __cplusplus
extern "C" {
#endif
    
    void listarTabelaPrecos(struct Custo);
    void menuEditaTabelaPrecos(struct Custo* ,struct Cliente **,int );
    void editaPrecoCodigoPostal(struct Custo*);
    void editaTabelaPrecos(struct Custo*);
    void avisaClientes(struct Cliente *,int);




#ifdef __cplusplus
}
#endif

#endif /* GESTAOTABELAPRECOS_H */

