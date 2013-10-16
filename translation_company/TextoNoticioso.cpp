//
//  TextoNoticioso.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
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