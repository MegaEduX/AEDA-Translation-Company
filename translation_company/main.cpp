//
//  main.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include <iostream>

#include "DatabaseManager.h"

int main(int argc, const char * argv[])
{
    DatabaseManager dbman = DatabaseManager("test.db");
    
    std::vector<std::string> linguas;
    
    linguas.push_back("Portugues");
    linguas.push_back("Ingles");
    
    Tradutor *trad = new Tradutor(0, "Eduardo Almeida", 10, linguas);
    
    dbman.create_update_record(trad);
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

