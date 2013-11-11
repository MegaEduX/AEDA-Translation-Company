//
//  Test.cpp
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - First Project
//

#include "cute.h"

#include "ide_listener.h"
#include "cute_runner.h"

#include "Encomenda.h"

#include "Texto.h"
#include "TextoLiterario.h"

#include "DatabaseManager.h"

void test_0_wordcount() {
    TextoLiterario *txt = new TextoLiterario(Texto::get_maior_id(), "Latim", "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", "Lorem Ipsum", "Cicero");
    
    ASSERT_EQUAL(69, txt->get_palavras());
}

void test_1_create() {
    DatabaseManager dbman = DatabaseManager(db_path);
    
    unsigned int texts = (unsigned int)dbman.get_textos().size();
    
    TextoLiterario *txt = new TextoLiterario(Texto::get_maior_id() + 1, "Latin", "Lorem ipsum dolor sit amet.", "Lorem Ipsum", "Cicero");
    
    dbman.create_update_record(txt);
    
    ASSERT_EQUAL(texts + 1, dbman.get_textos().size());
}

void test_2_load() {
    DatabaseManager dbman = DatabaseManager(db_path);
    
    unsigned int target_id = Texto::get_maior_id() + 1;
    
    TextoLiterario *txt = new TextoLiterario(target_id, "Latin", "Lorem ipsum dolor sit amet. Ha!", "Lorem Ipsum", "Cicero");
    
    dbman.create_update_record(txt);
    
    std::vector<Texto *> textos = dbman.get_textos();
    
    Texto *loaded_txt = nullptr;
    
    for (unsigned int i = 0; i < textos.size(); i++)
        if (textos[i]->get_id() == target_id) {
            loaded_txt = textos[i];
            
            break;
        }
    
    ASSERT(loaded_txt != nullptr);
    
    ASSERT(dynamic_cast<TextoLiterario *>(loaded_txt));
    
    if (dynamic_cast<TextoLiterario *>(loaded_txt))
        ASSERT_EQUAL(loaded_txt->get_conteudo(), "Lorem ipsum dolor sit amet. Ha!");
}

void test_3_update() {
    DatabaseManager dbman = DatabaseManager(db_path);
    
    unsigned int id = Texto::get_maior_id() + 1;
    
    TextoLiterario *txt = new TextoLiterario(id, "Latin", "Lorem ipsum dolor sit amet, for test 3!", "Lorem Ipsum", "Cicero");
    
    std::string curr_auth = txt->get_autor();
    
    dbman.create_update_record(txt);
    
    std::vector<Texto *> txtvec = dbman.get_textos();
    
    bool got_txt = false;
    
    for (int i = 0; i < txtvec.size(); i++)
        if (txtvec[i]->get_id() == id) {
            txt = (TextoLiterario *)txtvec[i];
            
            got_txt = true;
            
            break;
        }
    
    ASSERT(got_txt);
    
    txt->set_autor("Foo!");
    
    dbman.create_update_record(txt);
    
    txtvec = dbman.get_textos();
    
    got_txt = false;
    
    for (int i = 0; i < txtvec.size(); i++)
        if (txtvec[i]->get_id() == id) {
            txt = (TextoLiterario *)txtvec[i];
            
            got_txt = true;
            
            break;
        }
    
    ASSERT(got_txt);
    
    ASSERT_EQUAL("Foo!", txt->get_autor());
}

void run_test_suite(){
	cute::suite s;
    
    /*
     *  Clean Test Environment. :)
     */
    
    std::remove(db_path);
    
	s.push_back(CUTE(test_0_wordcount));
    s.push_back(CUTE(test_1_create));
    s.push_back(CUTE(test_2_load));
    s.push_back(CUTE(test_3_update));
    
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "Translation Company (AEDA Project #1) -> Test Suite");
}
