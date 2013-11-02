//
//  TextoLiterario.h
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - First Project
//

#ifndef __translation_company__TextoLiterario__
#define __translation_company__TextoLiterario__

#include <iostream>

#include "Texto.h"

/**
 *  Texto Literario class.
 *  Subclass of Texto, this handles a specific type of Text (Literary Text).
 */

class TextoLiterario : public Texto {
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
