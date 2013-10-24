//
//  main.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include <iostream>

#ifdef RUN_TEST_CODE

#include "TextoTecnico.h"
#include "TextoLiterario.h"

#endif

#include "DatabaseManager.h"

#include "Additions.h"

using namespace std;

static string db_path = "translation_company_data.db";

//  Comment the following line of code to run the app.

//  #define RUN_TEST_CODE

int main(int argc, const char * argv[]) {
    
#ifdef RUN_TEST_CODE
    
    DatabaseManager dbman = DatabaseManager("test.db");
    
    std::vector<std::string> linguas;
    
    linguas.push_back("Portugues");
    linguas.push_back("Ingles");
    
    Tradutor *trad = new Tradutor(0, "Eduardo Almeida", 10, linguas);

    dbman.create_update_record(trad);
    dbman.delete_record(trad);
    
#else
    
    // Application Code Comes Here!
    
    cout << "  /////////////////////////////" << endl;
    cout << " //   Translation Company   //" << endl;
    cout << "/////////////////////////////" << endl;
    
    cout << endl;
    cout << endl;
    
    bool db_existed;
    
    DatabaseManager(db_path, db_existed);
    
    if (!db_existed) {
        cout << "This appears to be your first time running \"Translation Company\"." << endl;
        cout << "A new blank, clean database has been automatically created for you." << endl;
    }
    
    cout << "-> Main Menu" << endl;
    
    cout << endl;
    
    cout << "1. Order a Translation" << endl;
    cout << "2. Query the Database" << endl;
    cout << "0. Exit" << endl;
    
    cout << endl;
    
    _getch();
    
#endif
    
    return 0;
}

