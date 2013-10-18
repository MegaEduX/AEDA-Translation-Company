//
//  TextoLiterario.h
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#ifndef __translation_company__TextoLiterario__
#define __translation_company__TextoLiterario__

#include <iostream>

#include "Texto.h"

class TextoLiterario : public Texto {
    typedef Texto super;
    
    std::string _titulo;
    std::string _autor;
    
public:
    TextoLiterario(unsigned int id, std::string lingua, std::string conteudo, std::string titulo, std::string autor);
    TextoLiterario(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo, std::string titulo, std::string autor);
    
    std::string get_titulo();
    std::string get_autor();
    
    unsigned int get_complexidade();
};

#endif /* defined(__translation_company__TextoLiterario__) */
