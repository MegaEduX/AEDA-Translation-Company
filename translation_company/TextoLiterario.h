//
//  TextoLiterario.h
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#ifndef __translation_company__TextoLiterario__
#define __translation_company__TextoLiterario__

#include <iostream>

#include "Texto.h"

class TextoLiterario : public Texto {
    std::string _titulo;
    std::string _autor;
    
public:
    std::string get_titulo();
    std::string get_autor();
};

#endif /* defined(__translation_company__TextoLiterario__) */
