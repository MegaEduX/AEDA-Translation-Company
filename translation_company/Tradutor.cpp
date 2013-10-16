//
//  Tradutor.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "Tradutor.h"

unsigned int Tradutor::_maior_id_tradutor = 0;

Tradutor::Tradutor(unsigned int id, std::string nome, unsigned int anos_experiencia, std::vector<std::string> linguas) {
    _id = id;
    _nome = nome;
    _anos_experiencia = anos_experiencia;
    _linguas = linguas;
    
    if (id > _maior_id_tradutor)
        _maior_id_tradutor = id;
}

unsigned int Tradutor::get_maior_id() {
    return _maior_id_tradutor;
}

unsigned int Tradutor::get_id() {
    return _id;
}

std::string Tradutor::get_nome() {
    return _nome;
}

unsigned int Tradutor::get_anos_experiencia() {
    return _anos_experiencia;
}

std::vector<std::string> Tradutor::get_linguas() {
    return _linguas;
}

int Tradutor::custoTraducao(Texto *texto) {
    //  To Be Implemented
    
    return -1;
}

int Tradutor::tempoEstimado(Texto *texto) {
    //  To Be Implemented
    
    return -1;
}