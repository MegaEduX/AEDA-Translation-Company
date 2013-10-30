//
//  main.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

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

void search_translators_step2(unsigned int search_type);
void search_orders_step2(unsigned int search_type);

void display_info(Tradutor *trad);
void display_info(Encomenda *enc);

void manage_database();

void add_record();
void edit_record();

void edit_record_step2(unsigned int obj_type);

void edit_record_step3(Tradutor *obj);

template <class T>
void delete_record_step3(T *obj);

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
    
    Additions::clearConsole();
    
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
    cout << "3. Manage the Database" << endl;
    
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
                
            case baseASCIINumber + 3:
                manage_database();
                
                break;
                
            default:
                cout << endl << "Invalid choice." << endl << endl;
                
                cout << "1. Order a Translation" << endl;
                cout << "2. Query the Database" << endl;
                cout << "3. Manage the Database" << endl;
                
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
    
    cout << "Available Text Types:" << endl << " (1) - Technical Text" <<  endl << " (2) - Literary Text" << endl << " (3) - News Article Text" << endl << " (0) - Go Back" << endl;
    
    cout << endl;
    
    cout << "Source Text Type: ";
    
    kTexto text_type = kTextoBase;
    
    while (true) {
        bool acceptable_answer = false;
        
        int ch = _getch();
        
        switch (ch) {
            case baseASCIINumber:
                
                Additions::clearConsole();
                
                main_menu();
                
                break;
                
            case baseASCIINumber + 1:
                
                text_type = kTextoTecnico;
                
                acceptable_answer = true;
                
                break;
                
            case baseASCIINumber + 2:
                
                text_type = kTextoLiterario;
                
                acceptable_answer = true;
                
                break;
            
            case baseASCIINumber + 3:
                text_type = kTextoNoticioso;
                
                acceptable_answer = true;
                
                break;
                
            default:
                
                cout << endl << "Invalid choice. Please try again. " << endl;
                
                break;
        }
        
        if (acceptable_answer)
            break;
    }
    
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
    
    cout << endl;
    
    cout << endl << "== Text Type - Specific Questions ==" << endl;
    
    cout << endl;
    
    string arg1;
    string arg2;
    
    switch (text_type) {
        case kTextoTecnico: {
            cout << "Dominio de Especialidade: ";
            
            arg1 = Additions::getline();
            
            break;
        }
            
        case kTextoLiterario: {
            cout << "Titulo: ";
            
            arg1 = Additions::getline();
            
            if (Additions::gotESC(arg1)) {
                Additions::clearConsole();
                
                main_menu();
            }
            
            cout << endl << "Autor: ";
            
            arg2 = Additions::getline();
            
            if (Additions::gotESC(arg2)) {
                Additions::clearConsole();
                
                main_menu();
            }
            
            break;
        }
            
        case kTextoNoticioso: {
            cout << "Assunto: ";
            
            arg1 = Additions::getline();
            
            if (Additions::gotESC(arg1)) {
                Additions::clearConsole();
                
                main_menu();
            }
            
            cout << endl;
            
            cout << endl << "Tipos de Jornal: (1) - Diario, (2) - Semanario" << endl;
            
            cout << endl << "Tipo de Jornal: ";
            
            while (true) {
                bool can_break = false;
                
                switch (_getch()) {
                    case baseASCIINumber + 1:
                        
                        arg2 = boost::lexical_cast<string>(0);
                        
                        can_break = true;
                        
                        break;
                        
                    case baseASCIINumber + 2:
                        
                        arg2 = boost::lexical_cast<string>(1);
                        
                        can_break = true;
                        
                        break;
                        
                    default:
                        
                        cout << endl << "Invalid choice. Please retry: ";
                        
                        break;
                }
                
                if (can_break)
                    break;
            }
            
            break;
        }
            
        default: {
            throw "Unrecognized text type.";
            
            break;
        }
    }
    
    cout << endl << endl << "Processing your request... ";
    
    unsigned int deadline = boost::lexical_cast<int>(deadline_str);
    
    Texto *txt; /* = new Texto(Texto::get_maior_id() + 1, src_lang, text)*/
    
    switch (text_type) {
        case kTextoTecnico:
            
            txt = new TextoTecnico(Texto::get_maior_id() + 1, src_lang, text, arg1);
            
            break;
            
        case kTextoLiterario:
            
            txt = new TextoLiterario(Texto::get_maior_id() + 1, src_lang, text, arg1, arg2);
            
            break;
            
        case kTextoNoticioso:
            
            txt = new TextoNoticioso(Texto::get_maior_id() + 1, src_lang, text, arg1, (tipo_jornal)boost::lexical_cast<int>(arg2));
            
            break;
            
        default:
            throw "Hue Hue Hue...";
            
            break;
    }
    
    Encomenda *enc = new Encomenda(Encomenda::get_maior_id() + 1, txt, dst_lang, deadline);
    
    unsigned int least_time = 0xDEADBEEF; // And this is why you should not code... while hungry.
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
        enc->set_timestamp_entrega(time(NULL) + best_translator->tempoEstimado(enc));
        
        cout << "We have found a translator suitable for your order." << endl;
        
        cout << endl;
        
        cout << "Translator Name: " << best_translator->get_nome() << endl;
        cout << "Estimated Time: " << best_translator->tempoEstimado(enc) << " seconds" << endl;
        cout << "Estimated Date: " << Additions::timestampToString(enc->get_timestamp_entrega()) << endl;
        cout << "Price: € " << best_translator->custoTraducao(enc->get_texto()) << endl;
        
        cout << endl;
        
        cout << "Do you agree to these terms? (y/n) ";
        
        bool should_loop = true;
        
        while (should_loop) {
            should_loop = false;
            
            switch (_getch()) {
                case 89:    //  Y
                case 121:   //  y
                    
                    dbman.create_update_record(enc);
                    dbman.create_update_record(txt);
                    
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
    cout << "3. Search for Texts" << endl; //   TBD
    
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
                
            case baseASCIINumber + 3:
                
                //  TBD
                
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
    
    cout << "5. List All Translators" << endl;
    
    cout << endl;
    
    cout << "0. Go Back" << endl;
    
    cout << endl;
    
    cout << "Please press the key corresponding to your choice. ";
    
    int ch = _getch();
    
    while (ch < baseASCIINumber || ch > baseASCIINumber + 5) {
        cout << endl << "Invalid choice." << endl;
        
        cout << endl;
        
        cout << "1. ID" << endl;
        cout << "2. Name" << endl;
        cout << "3. Years of Experience" << endl;
        cout << "4. Language" << endl;
        
        cout << endl;
        
        cout << "5. List All Translators" << endl;
        
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

void search_translators_step2(unsigned int search_type) {
    cout << endl;
    
    string str_in;
    
    if (search_type != 5) {
        cout << "Query: ";
        
        str_in = Additions::getline();
        
        if (Additions::gotESC(str_in)) {
            Additions::clearConsole();
            
            query_database();
            
            return;
        }
        
        cout << endl;
    }
    
    cout << endl;
    
    std::vector<Tradutor *> translators = dbman.get_tradutores();
    
    bool found = false;
    
    for (int i = 0; i < translators.size(); i++) {
        Tradutor *ct = translators[i];
        
        switch (search_type) {
            case 1: {
                int in_intval = boost::lexical_cast<int>(str_in);
                
                if (ct->get_id() == in_intval) {
                    display_info(ct);
                    
                    found = true;
                }
                
                break;
            }
            
            case 2: {
                if (!(ct->get_nome().compare(str_in))) {
                    display_info(ct);
                    
                    found = true;
                }
                
                break;
            }
            
            case 3: {
                int in_intval = boost::lexical_cast<int>(str_in);
                
                if (ct->get_anos_experiencia() == in_intval) {
                    display_info(ct);
                    
                    found = true;
                }
                
                break;
            }
                
            case 4: {
                std::vector<std::string> languages = ct->get_linguas();
                
                for (int j = 0; j < languages.size(); j++) {
                    if (!(ct->get_linguas()[j].compare(str_in))) {
                        display_info(ct);
                        
                        found = true;
                        
                        break;
                    }
                }
                
                break;
            }
                
            case 5: {
                display_info(ct);
                
                found = true;
                
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

void display_info(Tradutor *trad) {
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
    cout << "4. Translator ID" << endl;
    
    cout << endl;
    
    cout << "5. List All Orders" << endl;
    
    cout << endl;
    
    cout << "0. Go Back" << endl;
    
    cout << endl;
    
    cout << "Please press the key corresponding to your choice. ";
    
    int ch = _getch();
    
    while (ch < baseASCIINumber || ch > baseASCIINumber + 5) {
        cout << endl << "Invalid choice." << endl;
        
        cout << endl;
        
        cout << "1. ID" << endl;
        cout << "2. Source Language" << endl;
        cout << "3. Destination Language" << endl;
        cout << "4. Translator ID" << endl;
        
        cout << endl;
        
        cout << "5. List All Orders" << endl;
        
        cout << endl;
        
        cout << "0. Go Back" << endl;
        
        cout << endl;
        
        cout << "Please press the key corresponding to your new choice. ";
    }
    
    if (ch == baseASCIINumber) {
        Additions::clearConsole();
        
        main_menu();
        
        return;
    }
    
    int search_type = ch - baseASCIINumber;
    
    search_orders_step2(search_type);
}

void search_orders_step2(unsigned int search_type) {
    cout << endl;
    
    string str_in;
    
    if (search_type != 5) {
        cout << "Query: ";
        
        str_in = Additions::getline();
        
        if (Additions::gotESC(str_in)) {
            Additions::clearConsole();
            
            main_menu();
        }
        
        cout << endl;
        
        if (search_type == 1 || search_type == 4) {
            while (!Additions::checkForOnlyNumeric(str_in)) {
                cout << endl << "This option requires a numeric query. Please retry.";
                cout << endl << "You may also go back to the previous screen by using the ESC key.";
                cout << endl << endl << "Query: ";
                
                if (Additions::gotESC(str_in)) {
                    Additions::clearConsole();
                    
                    search_orders();
                }
            }
        }
    }
    
    cout << endl;
    
    std::vector<Encomenda *> orders = dbman.get_encomendas();
    
    bool found = false;
    
    for (int i = 0; i < orders.size(); i++) {
        Encomenda *enc = orders[i];
        
        switch (search_type) {
            case 1: {
                int in_intval = boost::lexical_cast<int>(str_in);
                
                if (enc->get_id() == in_intval) {
                    display_info(enc);
                    
                    found = true;
                }
                
                break;
            }
                
            case 2: {
                if (!(enc->get_texto()->get_lingua().compare(str_in))) {
                    display_info(enc);
                    
                    found = true;
                }
                
                break;
            }
                
            case 3: {
                if (!(enc->get_lingua_destino().compare(str_in))) {
                    display_info(enc);
                    
                    found = true;
                }
                
                break;
            }
                
            case 4: {
                int in_intval = boost::lexical_cast<int>(str_in);
                
                if (enc->get_tradutor()->get_id() == in_intval) {
                    display_info(enc);
                    
                    found = true;
                }
                
                break;
            }
                
            case 5:
                
                display_info(enc);
                
                found = true;
                
                break;
                
            default:
                
                break;
        }
    }
    
    cout << "End of listing." << endl;
    
    cout << endl;
    
    cout << "Press any key to go back to the Translator Search. ";
    
    _getch();
    
    search_orders();
}

void display_info(Encomenda *enc) {
    cout << "Order Information (ID: " << enc->get_id() << ")" << endl;
    
    cout << endl;
    
    cout << "Source Language: " << enc->get_texto()->get_lingua() << endl;
    cout << "Destination Language: " << enc->get_lingua_destino() << endl;
    cout << "Text Size (in words): " << enc->get_texto()->get_palavras() << endl;
    cout << "Date of Delivery: " << Additions::timestampToString(enc->get_timestamp_entrega()) << endl;
    cout << "Deliveried? " << (time(NULL) > enc->get_timestamp_entrega() ? "Yes" : "No") << "." << endl;
    
    cout << endl;
}

void manage_database() {
    Additions::clearConsole();
    
    cout << "-> Manage Database" << endl;
    
    cout << endl;
    
    cout << "1. Add a Record" << endl;
    cout << "2. Edit (or Delete) a Record" << endl;
    
    cout << endl;
    
    cout << "0. Go Back" << endl;
    
    /*cout << "1. Search for Translators" << endl;
    cout << "2. Search for Orders" << endl;
    cout << "3. Search for Texts" << endl; //   TBD
    
    cout << endl;
    
    cout << "0. Go Back" << endl;
    
    cout << endl;*/
    
    cout << endl << "Please press the key corresponding to your choice. ";
    
    while (true) {
        int ch = _getch();
        
        switch (ch) {
            case baseASCIINumber:
                
                Additions::clearConsole();
                
                main_menu();
                
                break;
                
            case baseASCIINumber + 1:
                
                add_record();
                
                break;
                
            case baseASCIINumber + 2:
                
                edit_record();
                
                break;
                
            default:
                
                cout << endl << "Invalid choice." << endl;
                
                cout << endl;
                
                cout << "1. Add a Record" << endl;
                cout << "2. Edit (or Delete) a Record" << endl;
                
                cout << endl;
                
                cout << "0. Go Back" << endl;
                
                cout << endl << "Please press the key corresponding to your new choice. ";
                
                break;
        }
    }
}

void add_record() {
    Additions::clearConsole();
    
    cout << "-> Add a Record" << endl;
    
    cout << endl;
    
    cout << "Only translator records can be created manually." << endl;
    cout << "The rest of the records are created through the \"Order Translation\" interface." << endl;
    
    cout << endl;
    
    cout << "Press any key to continue (or 0 to go back to the previous menu). ";
    
    int ch = _getch();
    
    if (ch == baseASCIINumber) {
        Additions::clearConsole();
        
        manage_database();
    }
    
    cout << endl << endl;
    
    cout << "Name: ";
    
    string tr_name = Additions::getline();
    
    if (Additions::gotESC(tr_name)) {
        Additions::clearConsole();
        
        manage_database();
    }
    
    cout << endl << "Years of Experience: ";
    
    string tr_expy_str = Additions::getline();
    
    if (Additions::gotESC(tr_expy_str)) {
        Additions::clearConsole();
        
        manage_database();
    }
    
    while (!Additions::checkForOnlyNumeric(tr_expy_str)) {
        cout << endl << endl<< "This field requires a numeric-only value. Please try again." << endl << endl;
        
        cout << "Years of Experience: ";
        
        tr_expy_str = Additions::getline();
        
        if (Additions::gotESC(tr_name)) {
            Additions::clearConsole();
            
            manage_database();
        }
    }
    
    int tr_expy = boost::lexical_cast<int>(tr_expy_str);
    
    cout << endl << "Languages (separated by return, blank input to terminate): ";
    
    vector<string> languages;
    
    string lang = Additions::getline();
    
    if (Additions::gotESC(lang)) {
        Additions::clearConsole();
        
        manage_database();
    }
    
    while (lang.size() && lang != "") {
        languages.push_back(lang);
        
        cout << endl;
        
        lang = Additions::getline();
    }
    
    cout << endl << "Language Count: " << languages.size() << endl;
    
    Tradutor *trad = new Tradutor(Tradutor::get_maior_id() + 1, tr_name, tr_expy, languages);
    
    dbman.create_update_record(trad);
    
    cout << endl << "Record successfully created! Press any key to continue... ";
    
    _getch();
    
    manage_database();
}

void edit_record() {
    Additions::clearConsole();
    
    cout << "-> Modify / Delete a Record" << endl;
    
    cout << endl;
    
    cout << "1. Edit a Translator" << endl;
    cout << "2. Edit an Order" << endl;
    cout << "3. Edit a Text" << endl;
    
    cout << endl;
    
    cout << "0. Go Back" << endl;
    
    cout << endl << "Please press the key corresponding to your choice. ";
    
    while (true) {
        int ch = _getch();
        
        switch (ch) {
            case baseASCIINumber:
                
                Additions::clearConsole();
                
                manage_database();
                
                break;
                
            case baseASCIINumber + 1:
            case baseASCIINumber + 2:
            case baseASCIINumber + 3:
                
                edit_record_step2(ch - baseASCIINumber);
                
                break;
                
            default:
                
                cout << endl << "Invalid choice." << endl;
                
                cout << endl;
                
                cout << "1. Edit a Translator" << endl;
                cout << "2. Edit an Order" << endl;
                cout << "3. Edit a Text" << endl;
                
                cout << endl;
                
                cout << "0. Go Back" << endl;
                
                cout << endl << "Please press the key corresponding to your new choice. ";
                
                break;
        }
    }
}

void edit_record_step2(unsigned int obj_type) {
    cout << endl;
    
    cout << "Object ID: ";
    
    string str_in = Additions::getline();
    
    while (!Additions::checkForOnlyNumeric(str_in)) {
        if (Additions::gotESC(str_in)) {
            Additions::clearConsole();
            
            edit_record();
            
            return;
        }
        
        cout << endl << "The ID must not contain non-numeric characters." << endl << endl;
        cout << "Object ID: ";
        
        str_in = Additions::getline();
    }
    
    int in_intval = boost::lexical_cast<int>(str_in);
    
    cout << endl << endl;
    
    switch (obj_type) {
        case 1: {
            vector<Tradutor *> trad = dbman.get_tradutores();
            
            for (int i = 0; i < trad.size(); i++)
                if (trad[i]->get_id() == in_intval) {
                    edit_record_step3(trad[i]);
                    
                    return;
                }
            
            break;
        }
            
        case 2: {
            vector<Encomenda *> ord = dbman.get_encomendas();
            
            for (int i = 0; i < ord.size(); i++)
                if (ord[i]->get_id() == in_intval) {
                    delete_record_step3(ord[i]);
                    
                    return;
                }
            
            break;
        }
            
        case 3: {
            vector<Texto *> txt = dbman.get_textos();
            
            for (int i = 0; i < txt.size(); i++)
                if (txt[i]->get_id() == in_intval) {
                    delete_record_step3(txt[i]);
                    
                    return;
                }
            
            break;
        }
            
        default:
            
            break;
    }
    
    cout << "No result matched your search." << endl;
    
    cout << endl;
    
    cout << "Press any key to go back to the Database Management menu. ";
    
    _getch();
    
    manage_database();
}

void edit_record_step3(Tradutor *obj) {
    cout << "-> Translator Editor (ID: " << obj->get_id() << ")" << endl;
    
    cout << endl;
    
    cout << "1. Edit Record" << endl;
    cout << "2. Delete Record" << endl;
    
    cout << endl;
    
    cout << "0. Go Back";
    
    cout << endl;
    
    cout << endl << "Please press the key corresponding to your new choice. ";
    
    int ch = _getch();
    
    switch (ch) {
        case baseASCIINumber:
            
            Additions::clearConsole();
            
            edit_record();
            
            break;
            
        case baseASCIINumber + 1: {
            cout << endl << endl;
            
            cout << "Name [" << obj->get_nome() << "] : ";
            
            string new_name = Additions::getline();
            
            if (new_name.size() || new_name != "")
                obj->set_nome(new_name);
            
            while (true) {
                cout << endl << "Years of Experience [" << obj->get_anos_experiencia() << "] : ";
                
                string new_yexp_str = Additions::getline();
                
                if (new_name.size() || new_name != "") {
                    if (Additions::checkForOnlyNumeric(new_yexp_str)) {
                        int new_yexp = boost::lexical_cast<int>(new_yexp_str);
                        
                        obj->set_anos_experiencia(new_yexp);
                        
                        break;
                    } else
                        cout << endl << "Years of Experience must be an integer. Please retry." << endl;
                } else {
                    break;
                }
            }
            
            vector<string> langs = obj->get_linguas();
            
            string imploded = boost::algorithm::join(langs, ", ");
            
            cout << endl << "Languages [" << imploded << "] " << endl;
            cout << endl << "Press Return with a blank input to end." << endl;
            
            vector<string> new_langs;
            
            for (unsigned int lg_count = 1; ; lg_count++) {
                cout << endl << "Language " << lg_count << ": ";
                
                string lang = Additions::getline();
                
                if (!lang.size() || lang == "")
                    break;
                
                new_langs.push_back(lang);
            }
            
            if (new_langs.size())
                obj->set_linguas(new_langs);
            
            dbman.create_update_record(obj);
            
            cout << endl << endl << "The operation was successful.";
            cout << endl << "Press any key to continue.";
            
            _getch();
            
            Additions::clearConsole();
            
            edit_record();
            
            return;
            
            break;
        }
            
        case baseASCIINumber + 2: {
            dbman.delete_record(obj);
            
            cout << endl << endl << "The operation was successful.";
            cout << endl << "Press any key to continue.";
            
            _getch();
            
            Additions::clearConsole();
            
            edit_record();
            
            return;
            
            break;
        }
            
        default:
            
            cout << endl << "Invalid choice." << endl;
            
            cout << endl;
            
            cout << "1. Edit Record";
            cout << "2. Delete Record";
            
            cout << endl;
            
            cout << "0. Go Back" << endl;
            
            cout << endl << "Please press the key corresponding to your new choice. ";
            
            break;
    }
}

template <class T>
void delete_record_step3(T *obj) {
    cout << "-> Order Editor (ID: " << obj->get_id() << ")" << endl;
    
    cout << endl;
    
    cout << "Due to the nature of this record, it must not be edited." << endl;
    cout << endl << "1. Delete Record" << endl;
    
    cout << endl;
    
    cout << "0. Go Back";
    
    cout << endl;
    
    cout << endl << "Please press the key corresponding to your new choice. ";
    
    int ch = _getch();
    
    switch (ch) {
        case baseASCIINumber:
            
            Additions::clearConsole();
            
            edit_record();
            
            break;
            
        case baseASCIINumber + 1: {
            dbman.delete_record(obj);
            
            cout << endl << endl << "The operation was successful.";
            cout << endl << "Press any key to continue.";
            
            _getch();
            
            Additions::clearConsole();
            
            edit_record();
            
            return;
            
            break;
        }
            
        default:
            
            cout << endl << "Invalid choice." << endl;
            
            cout << endl;
            
            cout << "1. Delete Record";
            
            cout << endl;
            
            cout << "0. Go Back" << endl;
            
            cout << endl << "Please press the key corresponding to your new choice. ";
            
            break;
    }
}
