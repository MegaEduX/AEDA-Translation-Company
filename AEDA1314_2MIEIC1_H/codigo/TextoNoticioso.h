//
//  TextoNoticioso.h
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - First Project
//

#ifndef __translation_company__TextoNoticioso__
#define __translation_company__TextoNoticioso__

#include <iostream>

#include "Texto.h"

typedef enum {
    tipo_jornal_diario,
    tipo_jornal_semanario
} tipo_jornal;

/**
 *  Texto Noticioso class.
 *  Subclass of Texto, this handles a specific type of Text (News Text).
 */

class TextoNoticioso : public Texto {
    std::string _assunto;
    
    tipo_jornal _tipo;
    
public:
    /**
     *  Class Constructor.
     *  @param id The object ID.
     *  @param lingua The language the text is written in.
     *  @param conteudo The plain text contents of the text.
     *  @param tipo The type of news text, as defined in the tipo_jornal struct.
     */
    
    TextoNoticioso(unsigned int id, std::string lingua, std::string conteudo, std::string assunto, tipo_jornal tipo);
    
    /**
     *  Class Constructor.
     *  @param id The object ID.
     *  @param lingua The language the text is written in.
     *  @param palavras The word coint of conteudo.
     *  @param conteudo The plain text contents of the text.
     *  @param assunto The title of the news text.
     *  @param tipo The type of the publication the text was posted in.
     */
    
    TextoNoticioso(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo, std::string assunto, tipo_jornal tipo);
    
    /**
     *  Getter for the title of the news.
     *  @return Title of the news.
     */
    
    std::string get_assunto();
    
    /**
     *  Getter for the type of the publication the text was posted in.
     *  @return Type of publication.
     */
    
    tipo_jornal get_tipo_jornal();
    
    /**
     *  Calculates the complexity of the text.
     *  @return Complexity value.
     */
    
    unsigned int complexidade();
};

#endif /* defined(__translation_company__TextoNoticioso__) */
