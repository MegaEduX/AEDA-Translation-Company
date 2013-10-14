//
//  main.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include <iostream>

#include "sqlite3pp.h"

int main(int argc, const char * argv[])
{
    sqlite3pp::database db("test_db.db");
    
    db.execute("CREATE TABLE `test` (\
               ID INT PRIMARY   KEY     NOT NULL,\
               NAME             TEXT    NOT NULL)");
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

