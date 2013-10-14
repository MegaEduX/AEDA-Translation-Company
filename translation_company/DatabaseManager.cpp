//
//  DatabaseManager.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "DatabaseManager.h"

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#define init_db(var) database var(_dbfp.c_str())

#define delete_record_wild(__TABLE_NAME__, __OBJ_NAME__)    init_db(db); \
                                                            query qry(db, ("SELECT * FROM `__TABLE_NAME__` WHERE id=" + boost::lexical_cast<std::string>(__OBJ_NAME__->get_id()) + "LIMIT 1").c_str());    \
                                                            bool exists = false;    \
                                                            for (query::iterator i = qry.begin(); i != qry.end(); ++i)  \
                                                                exists = !exists;   \
                                                            if (!exists)    \
                                                                return false;   \
                                                            command cmd(db, ("DELETE FROM `__TABLE_NAME__` WHERE id=" + boost::lexical_cast<std::string>(__OBJ_NAME__->get_id())).c_str());    \
                                                            if (!cmd.execute()) \
                                                                return true;    \
                                                            return false;

using namespace sqlite3pp;

DatabaseManager::DatabaseManager(std::string filepath) {
    _dbfp = filepath;
}

Texto *DatabaseManager::_get_texto_with_id(unsigned int id) {
    init_db(db);
    
    std::string query_str = "SELECT * FROM `textos` WHERE id=" + boost::lexical_cast<std::string>(id) + "LIMIT 1";
    
    query qry(db, query_str.c_str());
    
    for (query::iterator i = qry.begin(); i != qry.end(); ++i) {
        unsigned int id;
        unsigned long palavras;
        std::string lingua, conteudo;
        
        boost::tie(id, lingua, palavras, conteudo) = (*i).get_columns<int, std::string, double, std::string>(0, 1, 2, 3);
        
        Texto *texto = new Texto(id, lingua, palavras, conteudo);
        
        return texto;
    }
    
    return NULL;
}

std::vector<Texto *> DatabaseManager::get_textos() {
    std::vector<Texto *> return_vec;
    
    init_db(db);
    
    query qry(db, "SELECT * FROM `textos`");
    
    for (query::iterator i = qry.begin(); i != qry.end(); ++i) {
        unsigned int id;
        unsigned long palavras;
        std::string lingua, conteudo;
        
        boost::tie(id, lingua, palavras, conteudo) = (*i).get_columns<int, std::string, double, std::string>(0, 1, 2, 3);
        
        Texto *texto = new Texto(id, lingua, palavras, conteudo);
        
        return_vec.push_back(texto);
    }
    
    return return_vec;
}

std::vector<Tradutor *> DatabaseManager::get_tradutores() {
    std::vector<Tradutor *> return_vec;
    
    init_db(db);
    
    query qry(db, "SELECT * FROM `tradutores`");
    
    for (query::iterator i = qry.begin(); i != qry.end(); ++i) {
        unsigned int id, anos_experiencia;
        
        std::string nome, linguas;
        
        boost::tie(id, nome, anos_experiencia, linguas) = (*i).get_columns<int, std::string, int, std::string>(0, 1, 2, 3);
        
        std::vector<std::string> linguas_vec;
        
        boost::split(linguas_vec, linguas, boost::is_any_of(","));
        
        Tradutor *tradutor = new Tradutor(id, nome, anos_experiencia, linguas_vec);
        
        return_vec.push_back(tradutor);
    }
    
    return return_vec;
}

std::vector<Encomenda *> DatabaseManager::get_encomendas() {
    std::vector<Encomenda *> return_vec;
    
    init_db(db);
    
    query qry(db, "SELECT * FROM `encomendas`");
    
    for (query::iterator i = qry.begin(); i != qry.end(); ++i) {
        unsigned int id, texto_id, duracao_max_dias;
        
        std::string lingua_destino;
        
        boost::tie(id, texto_id, lingua_destino, duracao_max_dias) = (*i).get_columns<int, int, std::string, int>(0, 1, 2, 3);
        
        Texto *texto = _get_texto_with_id(texto_id);
        
        Encomenda *encomenda = new Encomenda(id, texto, lingua_destino, duracao_max_dias);
        
        return_vec.push_back(encomenda);
    }
    
    return return_vec;
}

bool DatabaseManager::create_update_record(Texto *texto) {
    init_db(db);
    
    //  Check for record existance
    //      - Exists:   Update.
    //      - Else:     Create.
    
    std::string query_str = "SELECT * FROM `textos` WHERE id=" + boost::lexical_cast<std::string>(texto->get_id()) + "LIMIT 1";
    
    query qry(db, query_str.c_str());
    
    std::string query = "INSERT INTO `textos` (id, lingua, palavras, conteudo) VALUES (:id, :lingua, :palavras, :conteudo)";
    
    for (query::iterator i = qry.begin(); i != qry.end(); ++i)
        query = "UPDATE `textos` SET lingua=:lingua, palavras=:palavras, conteudo=:conteudo WHERE id=:id";
    
    command cmd(db, query.c_str());
    
    cmd.bind(":id", boost::lexical_cast<std::string>(texto->get_id()).c_str());
    cmd.bind(":lingua", texto->get_lingua().c_str());
    cmd.bind(":palavras", boost::lexical_cast<std::string>(texto->get_palavras()).c_str());
    cmd.bind(":conteudo", texto->get_conteudo().c_str());
    
    if (!cmd.execute())
        return true;
    
    return false;
}

bool DatabaseManager::delete_record(Texto *texto) {
    delete_record_wild("textos", texto);
}

bool DatabaseManager::delete_record(Tradutor *tradutor) {
    delete_record_wild("tradutores", tradutor);
}

bool DatabaseManager::delete_record(Encomenda *encomenda) {
    delete_record_wild("encomendas", encomenda);
}
