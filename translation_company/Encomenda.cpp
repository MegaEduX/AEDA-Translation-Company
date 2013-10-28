//
//  Encomenda.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "Encomenda.h"

#include "Texto.h"

unsigned int Encomenda::_maior_id_encomenda = 0;

Encomenda::Encomenda(unsigned int id, Texto *texto, std::string lingua_destino, unsigned int duracao_max_dias) {
    _id = id;
    _texto = texto;
    _lingua_destino = lingua_destino;
    _duracao_max_dias = duracao_max_dias;
    _tradutor = nullptr;
    
    if (id > _maior_id_encomenda)
        _maior_id_encomenda = id;
}

Encomenda::Encomenda(unsigned int id, Texto *texto, std::string lingua_destino, unsigned int duracao_max_dias, Tradutor *tradutor) {
    _id = id;
    _texto = texto;
    _lingua_destino = lingua_destino;
    _duracao_max_dias = duracao_max_dias;
    _tradutor = tradutor;
    
    if (id > _maior_id_encomenda)
        _maior_id_encomenda = id;
}

unsigned int Encomenda::get_maior_id() {
    return _maior_id_encomenda;
}

unsigned int Encomenda::get_id() {
    return _id;
}

Texto *Encomenda::get_texto() const {
    return _texto;
}

Tradutor *Encomenda::get_tradutor() const {
    return _tradutor;
}

std::string Encomenda::get_lingua_destino() {
    return _lingua_destino;
}

unsigned int Encomenda::get_duracao_max_dias() {
    return _duracao_max_dias;
}

void Encomenda::set_tradutor(Tradutor *tradutor) {
    _tradutor = tradutor;
}