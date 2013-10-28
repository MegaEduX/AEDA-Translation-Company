//
//  Encomenda.h
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#ifndef __translation_company__Encomenda__
#define __translation_company__Encomenda__

#include <iostream>

#include "Tradutor.h"

class Texto;

class Encomenda {
    unsigned int _id;
    unsigned int _duracao_max_dias;
    
    static unsigned int _maior_id_encomenda;
    
    Texto *_texto;
    Tradutor *_tradutor;
    
    std::string _lingua_destino;
    
public:
    Encomenda(unsigned int id, Texto *texto, std::string lingua_destino, unsigned int duracao_max_dias);
    Encomenda(unsigned int id, Texto *texto, std::string lingua_destino, unsigned int duracao_max_dias, Tradutor *tradutor);
    
    static unsigned int get_maior_id();
    
    unsigned int get_id();
    unsigned int get_duracao_max_dias();
    
    Texto *get_texto() const;
    
    Tradutor *get_tradutor() const;
    void set_tradutor(Tradutor *);
    
    std::string get_lingua_destino();
};

#endif /* defined(__translation_company__Encomenda__) */
