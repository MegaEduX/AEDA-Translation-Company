//
//  TextoLiterario.cpp
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - First Project
//

#include "TextoLiterario.h"

TextoLiterario::TextoLiterario(unsigned int id, std::string lingua, std::string conteudo, std::string titulo, std::string autor) : Texto(id, lingua, conteudo) {
    _titulo = titulo;
    _autor = autor;
}

TextoLiterario::TextoLiterario(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo, std::string titulo, std::string autor) : Texto(id, lingua, palavras, conteudo) {
    _titulo = titulo;
    _autor = autor;
}

std::string TextoLiterario::get_titulo() {
    return _titulo;
}

std::string TextoLiterario::get_autor() {
    return _autor;
}

unsigned int TextoLiterario::get_complexidade() {
    return Texto::get_complexidade() * 2;
}