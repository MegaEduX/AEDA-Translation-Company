//
//  TextoTecnico.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "TextoTecnico.h"

TextoTecnico::TextoTecnico(unsigned int id, std::string lingua, std::string conteudo, std::string dominio_especialidade) : Texto(id, lingua, conteudo) {
    _dominio = dominio_especialidade;
}

TextoTecnico::TextoTecnico(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo, std::string dominio_especialidade) : Texto(id, lingua, palavras, conteudo) {
    _dominio = dominio_especialidade;
}

std::string TextoTecnico::get_dominio_especialidade() {
    return _dominio;
}

unsigned int TextoTecnico::get_complexidade() {
    return Texto::get_complexidade() * 3;
}