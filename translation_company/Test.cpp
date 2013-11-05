//
//  Test.cpp
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - First Project
//

#include "cute.h"

#include "Encomenda.h"

#include "Texto.h"
#include "TextoLiterario.h"

void test_0_wordcount() {
    TextoLiterario *txt = new TextoLiterario(Texto::get_maior_id(), "Latim", "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", "Lorem Ipsum", "Cicero");
    
    ASSERT_EQUAL(txt.get_palavras(), 69);
}