//
//  TextoTecnico.cpp
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - First Project
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

void TextoTecnico::set_dominio_especialidade(std::string dominio) {
    _dominio = dominio;
}

unsigned int TextoTecnico::complexidade() {
    return Texto::complexidade() * 3;
}