//
//  TextoNoticioso.h
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#ifndef __translation_company__TextoNoticioso__
#define __translation_company__TextoNoticioso__

#include <iostream>

#include "Texto.h"

typedef enum {
    tipo_jornal_diario,
    tipo_jornal_semanario
} tipo_jornal;

class TextoNoticioso : public Texto {
    typedef Texto super;
    
    std::string _assunto;
    
    tipo_jornal _tipo;
    
public:
    TextoNoticioso(unsigned int id, std::string lingua, std::string conteudo, std::string assunto, tipo_jornal tipo);
    TextoNoticioso(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo, std::string assunto, tipo_jornal tipo);
    
    std::string get_assunto();
    
    tipo_jornal get_tipo_jornal();
    
    unsigned int get_complexidade();
};

#endif /* defined(__translation_company__TextoNoticioso__) */
