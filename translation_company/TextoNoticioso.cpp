//
//  TextoNoticioso.cpp
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - First Project
//

#include "TextoNoticioso.h"

TextoNoticioso::TextoNoticioso(unsigned int id, std::string lingua, std::string conteudo, std::string assunto, tipo_jornal tipo) : Texto(id, lingua, conteudo) {
    _assunto = assunto;
    _tipo = tipo;
}

TextoNoticioso::TextoNoticioso(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo, std::string assunto, tipo_jornal tipo) : Texto(id, lingua, palavras, conteudo) {
    _assunto = assunto;
    _tipo = tipo;
}

std::string TextoNoticioso::get_assunto() {
    return _assunto;
}

tipo_jornal TextoNoticioso::get_tipo_jornal() {
    return _tipo;
}

unsigned int TextoNoticioso::get_complexidade() {
    return Texto::get_complexidade() * 2;
}