//
//  TextoLiterario.h
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - Second Project
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
    /**
     *  Class Constructor.
     *  @param id The object ID.
     *  @param lingua The language the text is written in.
     *  @param conteudo The plain text contents of the text.
     *  @param titulo The title of the text.
     *  @param autor The author of the text.
     */
    
    TextoLiterario(unsigned int id, std::string lingua, std::string conteudo, std::string titulo, std::string autor);
    
    /**
     *  Class Constructor.
     *  @param id The object ID.
     *  @param lingua The language the text is written in.
     *  @param palavras The word coint of conteudo.
     *  @param conteudo The plain text contents of the text.
     *  @param titulo The title of the text.
     *  @param autor The author of the text.
     */
    
    TextoLiterario(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo, std::string titulo, std::string autor);
    
    /**
     *  Getter for the title of the text.
     *  @return The title of the text.
     */
    
    std::string get_titulo();
    
    /**
     *  Setter for the title of the text.
     *  @return The title of the text.
     */
    
    void set_titulo(std::string titulo);
    
    /**
     *  Getter for the author of the text.
     *  @return The author of the text.
     */
    
    std::string get_autor();
    
    /**
     *  Setter for the author of the text.
     *  @return The author of the text.
     */
    
    void set_autor(std::string autor);
    
    /**
     *  Calculates the complexity of the text.
     *  @return Complexity value.
     */
    
    unsigned int complexidade();
};

#endif /* defined(__translation_company__TextoLiterario__) */
