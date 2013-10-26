//
//  main.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include <iostream>
#include <boost/lexical_cast.hpp>

#ifdef RUN_TEST_CODE

#include "TextoTecnico.h"
#include "TextoLiterario.h"

#endif

#include "DatabaseManager.h"

#include "Additions.h"

using namespace std;

static const int baseASCIINumber = 48;

static const int returnKeyPOSIX = 13;
static const int returnKeyWindows = 10;

static string db_path = "translation_company_data.db";

static DatabaseManager dbman = DatabaseManager(db_path);

void main_menu();

void order_translation();
void query_database();

void search_translators();
void search_orders();

void search_translators_step2(int search_type);

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
    
    main_menu();
    
#endif
    
    return 0;
}

void main_menu() {
    cout << "-> Main Menu" << endl;
    
    cout << endl;
    
    cout << "1. Order a Translation" << endl;
    cout << "2. Query the Database" << endl;
    
    cout << endl;
    
    cout << "0. Exit" << endl;
    
    cout << endl;
    
    cout << "Please press the key corresponding to your choice. ";
    
    while (true) {
        int ch = _getch();
        
        switch (ch) {
            case baseASCIINumber:
                exit(0);
                
                break;
                
            case baseASCIINumber + 1:
                order_translation();
                
                break;
                
            case baseASCIINumber + 2:
                query_database();
                
                break;
                
            default:
                cout << endl << "Invalid choice." << endl << endl;
                
                cout << "1. Order a Translation" << endl;
                cout << "2. Query the Database" << endl;
                
                cout << endl;
                
                cout << "0. Exit" << endl;
                
                cout << endl;
                
                cout << "Please press the key corresponding to your new choice. ";
                
                break;
        }
    }
}

void order_translation() {
    
}

void query_database() {
    Additions::clearConsole();
    
    cout << "-> Query Database" << endl;
    
    cout << endl;
    
    cout << "1. Search for Translators" << endl;
    cout << "2. Search for Orders" << endl;
    
    cout << endl;
    
    cout << "0. Go Back" << endl;
    
    cout << endl;
    
    cout << "Please press the key corresponding to your choice. ";
    
    while (true) {
        int ch = _getch();
        
        switch (ch) {
            case baseASCIINumber:
                
                main_menu();
                
                break;
                
            case baseASCIINumber + 1:
                
                search_translators();
                
                break;
            
            case baseASCIINumber + 2:
                
                search_orders();
                
                break;
                
            default:
                
                cout << endl << "Invalid choice." << endl;
                
                cout << endl;
                
                cout << "1. Search for Translators" << endl;
                cout << "2. Search for Orders" << endl;
                
                cout << endl;
                
                cout << "0. Go Back" << endl;
                
                cout << "Please press the key corresponding to your new choice. ";
                
                break;
        }
    }
}

void search_translators() {
    Additions::clearConsole();
    
    cout << "-> Translator Search" << endl;
    
    cout << endl;
    
    cout << "Search by..." << endl;
    
    cout << "1. ID" << endl;
    cout << "2. Name" << endl;
    cout << "3. Years of Experience" << endl;
    cout << "4. Language" << endl;
    
    cout << endl;
    
    cout << "0. Go Back" << endl;
    
    cout << endl;
    
    cout << "Please press the key corresponding to your choice. ";
    
    int ch = _getch();
    
    while (ch < baseASCIINumber || ch > baseASCIINumber + 4) {
        cout << endl << "Invalid choice." << endl;
        
        cout << endl;
        
        cout << "1. ID" << endl;
        cout << "2. Name" << endl;
        cout << "3. Years of Experience" << endl;
        cout << "4. Language" << endl;
        
        cout << endl;
        
        cout << "0. Go Back" << endl;
        
        cout << endl;
        
        cout << "Please press the key corresponding to your new choice. ";
    }
    
    if (ch == baseASCIINumber) {
        query_database();
        
        return;
    }
    
    int search_type = ch - baseASCIINumber;
    
    search_translators_step2(search_type);
}

void search_translators_step2(int search_type) {
    cout << endl;
    
    cout << "Query: ";
    
    string str_in = Additions::getline();
    
    std::vector<Tradutor *> translators = dbman.get_tradutores();
    
    for (int i = 0; i < translators.size(); i++) {
        Tradutor *ct = translators[i];
        
        switch (search_type) {
            case 1: {
                int in_intval = boost::lexical_cast<int>(str_in);
                
                if (ct->get_id() == in_intval) {
                    //  Found it. Do something.
                }
                
                break;
            }
            
            case 2: {
                if (!(ct->get_nome().compare(str_in))) {
                    //  Found it. Do something.
                }
                
                break;
            }
            
            case 3: {
                int in_intval = boost::lexical_cast<int>(str_in);
                
                if (ct->get_anos_experiencia() == in_intval) {
                    //  Found it. Do something.
                }
            }
                
            case 4: {
                std::vector<std::string> languages = ct->get_linguas();
                
                for (int j = 0; j < languages.size(); j++) {
                    if (!(ct->get_linguas()[j].compare(str_in))) {
                        //  Found it. Do something.
                    }
                }
            }
            
            default:
                break;
        }
    }
}

void search_orders() {
    
}


