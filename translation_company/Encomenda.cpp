//
//  Encomenda.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "Encomenda.h"

Encomenda::Encomenda(Texto *texto, std::string lingua_destino, unsigned int duracao_max_dias) {
    _texto = texto;
    _lingua_destino = lingua_destino;
    _duracao_max_dias = duracao_max_dias;
}

Texto *Encomenda::get_texto() {
    return _texto;
}

std::string Encomenda::get_lingua_destino() {
    return _lingua_destino;
}

unsigned int Encomenda::get_duracao_max_dias() {
    return _duracao_max_dias;
}