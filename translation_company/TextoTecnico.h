//
//  TextoTecnico.h
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#ifndef __translation_company__TextoTecnico__
#define __translation_company__TextoTecnico__

#include <iostream>

#include "Texto.h"

class TextoTecnico : public Texto {
    std::string _dominio;
    
    typedef Texto super;
    
public:
    TextoTecnico(unsigned int id, std::string lingua, std::string conteudo, std::string dominio_especialidade);
    TextoTecnico(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo, std::string dominio_especialidade);
    
    std::string get_dominio_especialidade();
    
    unsigned int get_complexidade();
};

#endif /* defined(__translation_company__TextoTecnico__) */
