//
//  TextoTecnico.h
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - First Project
//

#ifndef __translation_company__TextoTecnico__
#define __translation_company__TextoTecnico__

#include <iostream>

#include "Texto.h"

/**
 *  Texto Tecnico class.
 *  Subclass of Texto, this handles a specific type of Text (Technical Text).
 */

class TextoTecnico : public Texto {
    std::string _dominio;
    
public:
    TextoTecnico(unsigned int id, std::string lingua, std::string conteudo, std::string dominio_especialidade);
    TextoTecnico(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo, std::string dominio_especialidade);
    
    std::string get_dominio_especialidade();
    
    void set_dominio_especialidade(std::string dominio);
    
    unsigned int get_complexidade();
};

#endif /* defined(__translation_company__TextoTecnico__) */
