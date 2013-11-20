//
//  TextoLiterario.cpp
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - Second Project
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

void TextoLiterario::set_titulo(std::string titulo) {
    _titulo = titulo;
}

std::string TextoLiterario::get_autor() {
    return _autor;
}

void TextoLiterario::set_autor(std::string autor) {
    _autor = autor;
}

unsigned int TextoLiterario::complexidade() {
    return Texto::complexidade() * 2;
}