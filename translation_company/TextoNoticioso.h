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
    TextoNoticioso(unsigned int id, std::string lingua, std::string conteudo, std::string assunto, tipo_jornal tipo);
    TextoNoticioso(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo, std::string assunto, tipo_jornal tipo);
    
    std::string get_assunto();
    
    tipo_jornal get_tipo_jornal();
    
    unsigned int get_complexidade();
};

#endif /* defined(__translation_company__TextoNoticioso__) */
