//
//  TextoTecnico.h
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - Second Project
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
    /**
     *  Class Constructor.
     *  @param id The object ID.
     *  @param lingua The language the text is written in.
     *  @param conteudo The plain text contents of the text.
     *  @param dominio_especialidade The domain of the contents of the text.
     */
    
    TextoTecnico(unsigned int id, std::string lingua, std::string conteudo, std::string dominio_especialidade);
    
    /**
     *  Class Constructor.
     *  @param id The object ID.
     *  @param lingua The language the text is written in.
     *  @param palavras The word coint of conteudo.
     *  @param conteudo The plain text contents of the text.
     *  @param dominio_especialidade The domain of the contents of the text.
     */
    
    TextoTecnico(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo, std::string dominio_especialidade);
    
    /**
     *  Getter for the text domain.
     *  @return The domain of the text.
     */
    
    std::string get_dominio_especialidade();
    
    /**
     *  Setter for the text domain.
     *  @param dominio The domain of the text.
     */
    
    void set_dominio_especialidade(std::string dominio);
    
    /**
     *  Calculates the complexity of the text.
     *  @return Complexity value.
     */
    
    unsigned int complexidade();
};

#endif /* defined(__translation_company__TextoTecnico__) */
