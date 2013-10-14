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

#include "Texto.h"

class Encomenda {
    unsigned int _id;
    Texto *_texto;
    std::string _lingua_destino;
    unsigned int _duracao_max_dias;
    
public:
    Encomenda(unsigned int id, Texto *texto, std::string lingua_destino, unsigned int duracao_max_dias);
    
    unsigned int get_id();
    
    Texto *get_texto();
    std::string get_lingua_destino();
    unsigned int get_duracao_max_dias();
};

#endif /* defined(__translation_company__Encomenda__) */
