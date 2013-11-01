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
    
    uint64_t _timestamp_entrega;
    
    static unsigned int _maior_id_encomenda;
    
    Texto *_texto;
    Tradutor *_tradutor;
    
    std::string _lingua_destino;
    
public:
    Encomenda(unsigned int id, Texto *texto, std::string lingua_destino, unsigned int duracao_max_dias);
    Encomenda(unsigned int id, Texto *texto, std::string lingua_destino, unsigned int duracao_max_dias, Tradutor *tradutor, uint64_t timestamp_entrega);
    
    static unsigned int get_maior_id();
    
    unsigned int get_id();
    
    unsigned int get_duracao_max_dias();
    void set_duracao_max_dias(unsigned int dias);
    
    Texto *get_texto() const;
    void set_texto(Texto *);
    
    Tradutor *get_tradutor() const;
    void set_tradutor(Tradutor *);
    
    std::string get_lingua_destino();
    void set_lingua_destino(std::string lingua);
    
    uint64_t get_timestamp_entrega();
    void set_timestamp_entrega(uint64_t timestamp_entrega);
};

#endif /* defined(__translation_company__Encomenda__) */
