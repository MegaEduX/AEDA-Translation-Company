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
    Texto(unsigned int id, std::string lingua, std::string conteudo);
    Texto(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo);
    
    static unsigned int get_maior_id();
    
    unsigned int get_id();
    
    unsigned long get_palavras();
    
    std::string get_lingua();
    
    void set_lingua(std::string lingua);
    
    std::string get_conteudo();
    
    void set_conteudo(std::string conteudo);
    
    virtual unsigned int get_complexidade();
};

#endif /* defined(__translation_company__Texto__) */
