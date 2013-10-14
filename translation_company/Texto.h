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
    
public:
    Texto(unsigned int id, std::string lingua, std::string conteudo);
    
    unsigned int get_id();
    unsigned long get_palavras();
    
    std::string get_lingua();
    std::string get_conteudo();
    
    unsigned int complexidade();
};

#endif /* defined(__translation_company__Texto__) */
