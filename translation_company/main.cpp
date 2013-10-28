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

static DatabaseManager dbman = DatabaseManager(db_path);

void main_menu();

void order_translation();
void query_database();

void search_translators();
void search_orders();

void search_translators_step2(int search_type);

void display_translator_info(Tradutor *trad);

void manage_translators();

//  Comment the following line of code to run the app.

//  #define RUN_TEST_CODE

int main(int argc, const char * argv[]) {
    
#ifdef RUN_TEST_CODE
    
    std::vector<std::string> linguas;
    
    linguas.push_back("Portugues");
    linguas.push_back("Ingles");
    
    Tradutor *trad = new Tradutor(0, "Eduardo Almeida", 10, linguas);
    Tradutor *trad2 = new Tradutor(1, "Pedro Santiago", 2, linguas);

    dbman.create_update_record(trad);
    dbman.create_update_record(trad2);
    
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
    cout << "3. Manage Translators" << endl;
    
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
                cout << "3. Manage Translators" << endl;
                
                cout << endl;
                
                cout << "0. Exit" << endl;
                
                cout << endl;
                
                cout << "Please press the key corresponding to your new choice. ";
                
                break;
        }
    }
}

void order_translation() {
    Additions::clearConsole();
    
    cout << "-> Order a Translation" << endl;
    cout << "(You may cancel this at any time by pressing ESC)" << endl;
    
    cout << endl;
    
    cout << "Text to Translate: ";
    
    string text = Additions::getline();
    
    if (Additions::gotESC(text)) {
        Additions::clearConsole();
        
        main_menu();
    }
    
    cout << endl << "Source Language: ";
    
    string src_lang = Additions::getline();
    
    if (Additions::gotESC(src_lang)) {
        Additions::clearConsole();
        
        main_menu();
    }
    
    cout << endl << "Destination Language: ";
    
    string dst_lang = Additions::getline();
    
    if (Additions::gotESC(dst_lang)) {
        Additions::clearConsole();
        
        main_menu();
    }
    
    if (!src_lang.compare(dst_lang)) {
        cout << endl << endl << "I see what you did there..." << endl;
        cout << endl << "Press any key to go back to the main menu.";
        
        _getch();
        
        Additions::clearConsole();
        main_menu();
    }
    
    std::vector<Tradutor *> translators = dbman.get_tradutores();
    
    std::vector<Tradutor *> possible_translators;
    
    int found = 0;
    
    for (unsigned int i = 0; i < translators.size(); i++) {
        found = 0;
        
        for (unsigned int j = 0; j < translators[i]->get_linguas().size(); j++)
            if (!src_lang.compare(translators[i]->get_linguas()[j]) || !dst_lang.compare(translators[i]->get_linguas()[j]))
                found++;
        
        if (found == 2)
            possible_translators.push_back(translators[i]);
    }
    
    if (found < 2) {
        cout << endl << endl << "We don't currently have any translator that can do the requested translation job.";
        cout << endl << "Press any key to go back to the main menu.";
        
        _getch();
        
        Additions::clearConsole();
        main_menu();
    }
    
    cout << endl << "Deadline (in days): ";
    
    string deadline_str = Additions::getline();
    
    while (!Additions::checkForOnlyNumeric(deadline_str)) {
        if (Additions::gotESC(deadline_str)) {
            Additions::clearConsole();
            
            main_menu();
        }
        
        cout << endl << "Answer needs to be numeric only." << endl;
        cout << endl << "Deadline (in days): ";
        
        deadline_str = Additions::getline();
    }
    
    cout << endl << endl << "Processing your request... ";
    
    unsigned int deadline = boost::lexical_cast<int>(deadline_str);
    
    Encomenda *enc = new Encomenda(Encomenda::get_maior_id() + 1, new Texto(Texto::get_maior_id() + 1, src_lang, text), dst_lang, deadline);
    
    unsigned int least_time = 0xB4DF00D; // And this is why you should not code... while hungry.
    Tradutor *best_translator = nullptr;
    
    for (unsigned int i = 0; i < possible_translators.size(); i++)
        if (possible_translators[i]->get_pode_satisfazer_encomenda(enc)) {
            unsigned int te = possible_translators[i]->tempoEstimado(enc);
            
            if (least_time > te || &best_translator == nullptr) {
                least_time = te;
                best_translator = possible_translators[i];
            }
        }
    
    cout << endl << endl;
    
    if (best_translator != nullptr) {
        //  Found a translator.
        
        enc->set_tradutor(best_translator);
        
        cout << "We have found a translator suitable for your order." << endl;
        
        cout << endl;
        
        cout << "Estimated Time: " << best_translator->tempoEstimado(enc) << endl;
        cout << "Price: " << best_translator->custoTraducao(enc->get_texto()) << endl;
        
        cout << endl;
        
        cout << "Do you agree to these terms? (y/n) ";
        
        bool should_loop = true;
        
        while (should_loop) {
            should_loop = false;
            
            switch (_getch()) {
                case 89:    //  Y
                case 121:   //  y
                    
                    dbman.create_update_record(enc);
                    
                    cout << endl << endl << "The record was created.";
                    
                    break;
                    
                case 78:    //  N
                case 110:   //  n
                    
                    cout << endl << endl << "The operation was canceled.";
                    
                    break;
                    
                default:
                    cout << endl << "Invalid Choice. Do you agree to these terms? (y/n) ";
                    
                    should_loop = true;
                    
                    break;
            }
        }
    } else {
        cout << endl << endl << "No viable candidate translator was found.";
    }
    
    cout << endl << endl << "Please press any key to go back to the Main Menu. ";
    
    _getch();
    
    Additions::clearConsole();
    
    main_menu();
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
                
                Additions::clearConsole();
                
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
    
    cout << endl << endl;
    
    std::vector<Tradutor *> translators = dbman.get_tradutores();
    
    bool found = false;
    
    for (int i = 0; i < translators.size(); i++) {
        Tradutor *ct = translators[i];
        
        switch (search_type) {
            case 1: {
                int in_intval = boost::lexical_cast<int>(str_in);
                
                if (ct->get_id() == in_intval) {
                    display_translator_info(ct);
                    
                    found = !found;
                }
                
                break;
            }
            
            case 2: {
                if (!(ct->get_nome().compare(str_in))) {
                    display_translator_info(ct);
                    
                    found = !found;
                }
                
                break;
            }
            
            case 3: {
                int in_intval = boost::lexical_cast<int>(str_in);
                
                if (ct->get_anos_experiencia() == in_intval) {
                    display_translator_info(ct);
                    
                    found = !found;
                }
                
                break;
            }
                
            case 4: {
                std::vector<std::string> languages = ct->get_linguas();
                
                for (int j = 0; j < languages.size(); j++) {
                    if (!(ct->get_linguas()[j].compare(str_in))) {
                        display_translator_info(ct);
                        
                        found = !found;
                        
                        break;
                    }
                }
                
                break;
            }
            
            default:
                
                break;
        }
    }
    
    cout << "End of listing." << endl;
    
    cout << endl;
    
    cout << "Press any key to go back to the Translator Search. ";
    
    _getch();
    
    search_translators();
}

void display_translator_info(Tradutor *trad) {
    cout << "Translator Information (ID: " << trad->get_id() << ")" << endl;
    
    cout << endl;
    
    cout << "Name: " << trad->get_nome() << endl;
    cout << "Years of Experience: " << trad->get_anos_experiencia() << endl;
    
    std::stringstream ss;
    
    for (size_t i = 0; i < trad->get_linguas().size(); ++i) {
        if (i != 0)
            ss << ", ";
        ss << trad->get_linguas()[i];
    }
    
    cout << "Languages: " << ss.str() << endl;
    
    cout << endl;
}

void search_orders() {
    Additions::clearConsole();
    
    cout << "-> Order Search" << endl;
    
    cout << endl;
    
    cout << "Search by..." << endl;
    
    cout << "1. ID" << endl;
    cout << "2. Source Language" << endl;
    cout << "3. Destination Language" << endl;
    cout << "4. Translator" << endl;
    
    cout << endl;
    
    cout << "0. Go Back" << endl;
    
    cout << endl;
    
    cout << "Please press the key corresponding to your choice. ";
    
    /*  
     *  TBD
     */
    
    _getch();
}

void manage_translators() {
    
}
