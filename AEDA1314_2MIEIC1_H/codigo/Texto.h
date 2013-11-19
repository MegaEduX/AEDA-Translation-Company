//
//  Texto.h
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - First Project
//

#ifndef __translation_company__Texto__
#define __translation_company__Texto__

#include <iostream>

/**
 *  Texto class.
 *  You should not use this class directly. 
 *  Please use one of the subclasses (TextoTecnico, TextoLiterario or TextoNoticioso).
 */

class Texto {
    unsigned int _id;
    unsigned long _palavras;
    
    std::string _lingua;
    std::string _conteudo;
    
    static unsigned int _maior_id_texto;
    
public:
    /**
     *  Class Constructor.
     *  @param id The object ID.
     *  @param lingua The language the text is written in.
     *  @param conteudo The plain text contents of the text.
     */
    
    Texto(unsigned int id, std::string lingua, std::string conteudo);
    
    /**
     *  Class Constructor.
     *  @param id The object ID.
     *  @param lingua The language the text is written in.
     *  @param palavras The word count of conteudo.
     *  @param conteudo The plain text contents of the text.
     */
    
    Texto(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo);
    
    /**
     *  Getter for the biggest ID of the known text objects.
     *  @return The biggest known ID.
     */
    
    static unsigned int get_maior_id();
    
    /**
     *  Getter for the ID of the text.
     *  @return The ID.
     */
    
    unsigned int get_id();
    
    /**
     *  Getter for the word count of the text content.
     *  @return Word Count of the text content.
     */
    
    unsigned long get_palavras();
    
    /**
     *  Getter for the language of the text.
     *  @return Language of the text.
     */
    
    std::string get_lingua();
    
    /**
     *  Setter for the language of the text.
     *  @param lingua Language of the text.
     */
    
    void set_lingua(std::string lingua);
    
    /**
     *  Getter for the text content.
     *  @return Text Content (in plain text).
     */
    
    std::string get_conteudo();
    
    /**
     *  Setter for the text content.
     *  @return Text Content (in plain text).
     */
    
    void set_conteudo(std::string conteudo);
    
    /**
     *  Calculates the complexity of the text.
     *  @return Complexity value.
     */
    
    virtual unsigned int complexidade();
};

#endif /* defined(__translation_company__Texto__) */
