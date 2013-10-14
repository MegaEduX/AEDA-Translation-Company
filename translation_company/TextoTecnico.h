//
//  TextoTecnico.h
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#ifndef __translation_company__TextoTecnico__
#define __translation_company__TextoTecnico__

#include <iostream>

#include "Texto.h"

class TextoTecnico : public Texto {
    std::string _dominio;
    
public:
    std::string get_dominio_especialidade();
};

#endif /* defined(__translation_company__TextoTecnico__) */
