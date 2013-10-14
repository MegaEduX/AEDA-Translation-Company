//
//  Tradutor.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "Tradutor.h"

Tradutor::Tradutor(unsigned int id, std::string nome, int anos_experiencia, std::vector<std::string> linguas) {
    _id = id;
    _nome = nome;
    _anos_experiencia = anos_experiencia;
    _linguas = linguas;
}

int Tradutor::custoTraducao(Texto *texto) {
    
    
    return -1;
}

int Tradutor::tempoEstimado(Texto *texto) {
    
    return -1;
}