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

/*
 *  We had no guidelines for these equations...
 *  So we made up our own!
 */

double Tradutor::custoTraducao(Texto *texto) {
    //  complexidade * anos de experiencia / 10
    
    return (int)(texto->get_complexidade() * _anos_experiencia / 10);
}

unsigned int Tradutor::tempoEstimado(Texto *texto) {
    //  complexidade * 20 / anos experiencia
    //  tempo retornado em segundos
    
    return (int)(texto->get_complexidade() * 20 / _anos_experiencia);
}