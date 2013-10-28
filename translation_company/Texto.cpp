//
//  Texto.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include <sstream>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "Texto.h"

#include "DatabaseManager.h"

#define WHITESPACE_ENDLINE_CHARS " \t\n\v\f\r"

unsigned int Texto::_maior_id_texto = DatabaseManager(db_path).get_maior_id(kClassTexto);

Texto::Texto(unsigned int id, std::string lingua, std::string conteudo) {
    _id = id;
    
    _lingua = lingua;
    _conteudo = conteudo;
    
    if (id > _maior_id_texto)
        _maior_id_texto = id;
    
    std::vector<std::string> result;
    
    boost::split(result, conteudo, boost::is_any_of(WHITESPACE_ENDLINE_CHARS), boost::token_compress_on);
    
    _palavras = result.size();
}

Texto::Texto(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo) {
    _id = id;
    
    _lingua = lingua;
    _conteudo = conteudo;
    
    if (id > _maior_id_texto)
        _maior_id_texto = id;
    
    _palavras = palavras;
}

unsigned int Texto::get_maior_id() {
    return _maior_id_texto;
}

unsigned int Texto::get_id() {
    return _id;
}

unsigned long Texto::get_palavras() {
    return _conteudo.length();
}

std::string Texto::get_lingua() {
    return _lingua;
}

std::string Texto::get_conteudo() {
    return _conteudo;
}

unsigned int Texto::get_complexidade() {
    return (unsigned int)(this->get_palavras() / 10);
}
