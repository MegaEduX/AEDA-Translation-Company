//
//  Texto.h
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#ifndef __translation_company__Texto__
#define __translation_company__Texto__

#include <iostream>

class Texto {
    unsigned int _id;
    unsigned long _palavras;
    
    std::string _lingua;
    std::string _conteudo;
    
    static unsigned int _maior_id_texto;
    
public:
    Texto(unsigned int id, std::string lingua, std::string conteudo);
    Texto(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo);
    
    unsigned int get_maior_id();
    
    unsigned int get_id();
    unsigned long get_palavras();
    
    std::string get_lingua();
    std::string get_conteudo();
    
    virtual unsigned int get_complexidade();
};

#endif /* defined(__translation_company__Texto__) */
