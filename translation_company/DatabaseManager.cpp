//
//  DatabaseManager.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include <fstream>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "DatabaseManager.h"

#define init_db(var) database var(_dbfp.c_str())

#define delete_record_wild(__TABLE_NAME__, __OBJ_NAME__)    init_db(db); \
                                                            query qry(db, (std::string("SELECT * FROM `") + __TABLE_NAME__ + std::string("` WHERE id=") + boost::lexical_cast<std::string>(__OBJ_NAME__->get_id()) + " LIMIT 1").c_str());    \
                                                            bool exists = false;    \
                                                            for (query::iterator i = qry.begin(); i != qry.end(); ++i)  \
                                                                exists = !exists;   \
                                                            if (!exists)    \
                                                                return false;   \
                                                            command cmd(db, (std::string("DELETE FROM `") + __TABLE_NAME__ + std::string("` WHERE id=") + boost::lexical_cast<std::string>(__OBJ_NAME__->get_id())).c_str());    \
                                                            if (!cmd.execute()) \
                                                                return true;    \
                                                            return false;

using namespace sqlite3pp;

DatabaseManager::DatabaseManager(std::string filepath) {
    _dbfp = filepath;
    
    std::ifstream fs(_dbfp);
    
    bool file_exists = (fs ? true : false);
    
    fs.close();
    
    if (!file_exists)
        _prepare_database();
}

DatabaseManager::~DatabaseManager() {
    
}

bool DatabaseManager::_prepare_database() {
    init_db(db);
    
    int res = 0;
    
    res = db.execute("CREATE TABLE `textos` (\
                     id                 INT PRIMARY KEY         NOT NULL,   \
                     lingua             VARCHAR(64)             NOT NULL,   \
                     palavras           INT                     NOT NULL,   \
                     conteudo           TEXT                    NOT NULL,   \
                     tipo_obj           INT                     NOT NULL,   \
                     tipo_args          VARCHAR(256)            NOT NULL)");
    
    if (res)
        return false;
    
    res = db.execute("CREATE TABLE `tradutores` (\
                     id                 INT PRIMARY KEY         NOT NULL,   \
                     nome               VARCHAR(128)            NOT NULL,   \
                     anos_experiencia   INT                     NOT NULL,   \
                     linguas            VARCHAR(256)            NOT NULL)");
    
    if (res)
        return false;
    
    res = db.execute("CREATE TABLE `encomendas` (\
                     id                 INT PRIMARY KEY         NOT NULL,   \
                     texto_id           INT                     NOT NULL,   \
                     lingua_destino     VARCHAR(64)             NOT NULL,   \
                     duracao_max_dias   INT                     NOT NULL,   \
                     tradutor_id        INT                     NOT NULL,   \
                     competion_date     INT                     NOT NULL)");
    
    if (res)
        return false;
    
    return true;
}

Texto *DatabaseManager::_get_texto_with_id(unsigned int id) {
    init_db(db);
    
    std::string query_str = "SELECT * FROM `textos` WHERE id=" + boost::lexical_cast<std::string>(id) + " LIMIT 1";
    
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
        unsigned int id, tipo_obj;
        unsigned long palavras;
        std::string lingua, conteudo, tipo_args;
        
        boost::tie(id, lingua, palavras, conteudo, tipo_obj, tipo_args) = (*i).get_columns<int, std::string, double, std::string, int, std::string>(0, 1, 2, 3, 4, 5);
        
        switch (tipo_obj) {
            case kTextoTecnico: {
                TextoTecnico *texto = new TextoTecnico(id, lingua, palavras, conteudo, tipo_args);
                
                return_vec.push_back(texto);
                
                break;
            }
                
            case kTextoLiterario: {
                std::vector<std::string> args;
                
                boost::split(args, tipo_args, boost::is_any_of(","));
                
                TextoLiterario *texto = new TextoLiterario(id, lingua, palavras, conteudo, args[0], args[1]);
                
                return_vec.push_back(texto);
                
                break;
            }
            
            case kTextoNoticioso: {
                std::vector<std::string> args;
                
                boost::split(args, tipo_args, boost::is_any_of(","));
                
                TextoNoticioso *texto = new TextoNoticioso(id, lingua, palavras, conteudo, args[0], (tipo_jornal)boost::lexical_cast<int>(args[1]));
                
                return_vec.push_back(texto);
                
                break;
            }
                
            default: {
                throw "Unrecognized text type.";
                
                break;
            }
        }
        
        Texto *texto = new Texto(id, lingua, palavras, conteudo);
        
        return_vec.push_back(texto);
    }
    
    return return_vec;
}

void DatabaseManager::get_textos_by_type(std::vector<TextoTecnico *> &textos_tecnicos, std::vector<TextoLiterario *> &textos_literarios, std::vector<TextoNoticioso *> &textos_noticiosos) {
    std::vector<Texto *> textosRaw = this->get_textos();
    
    for (int i = 0; i < textosRaw.size(); i++) {
        if (dynamic_cast<TextoTecnico *>(textosRaw[i]))
            textos_tecnicos.push_back((TextoTecnico *)textosRaw[i]);
        else if (dynamic_cast<TextoLiterario *>(textosRaw[i]))
             textos_literarios.push_back((TextoLiterario *)textosRaw[i]);
        else if (dynamic_cast<TextoNoticioso *>(textosRaw[i]))
             textos_noticiosos.push_back((TextoNoticioso *)textosRaw[i]);
        else
            throw "Unrecognized text type.";
    }
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
        unsigned int id, texto_id, duracao_max_dias, trad_id;
        
        uint64_t timestamp_entrega;
        
        std::string lingua_destino;
        
        boost::tie(id, texto_id, lingua_destino, duracao_max_dias, trad_id, timestamp_entrega) = (*i).get_columns<int, int, std::string, int, int, long long>(0, 1, 2, 3, 4, 5);
        
        Texto *texto = _get_texto_with_id(texto_id);
        
        Tradutor *tradutor = nullptr;
        
        std::vector<Tradutor *> tradutores = get_tradutores();
        
        for (int i = 0; i < tradutores.size(); i++) {
            if (tradutores[i]->get_id() == trad_id) {
                tradutor = tradutores[i];
                
                break;
            }
        }
        
        Encomenda *encomenda = new Encomenda(id, texto, lingua_destino, duracao_max_dias, tradutor, timestamp_entrega);
        
        return_vec.push_back(encomenda);
    }
    
    return return_vec;
}

bool DatabaseManager::create_update_record(Texto *texto) {
    init_db(db);
    
    //  Check for record existance
    //      - Exists:   Update.
    //      - Else:     Create.
    
    std::string query_str = "SELECT * FROM `textos` WHERE id=" + boost::lexical_cast<std::string>(texto->get_id()) + " LIMIT 1";
    
    query qry(db, query_str.c_str());
    
    std::string query = "INSERT INTO `textos` (id, lingua, palavras, conteudo, tipo_obj, tipo_args) VALUES (:id, :lingua, :palavras, :conteudo, :tipo_obj, :tipo_args)";
    
    for (query::iterator i = qry.begin(); i != qry.end(); ++i)
        query = "UPDATE `textos` SET lingua=:lingua, palavras=:palavras, conteudo=:conteudo WHERE id=:id";
    
    command cmd(db, query.c_str());
    
    cmd.bind(":id", boost::lexical_cast<std::string>(texto->get_id()).c_str());
    cmd.bind(":lingua", texto->get_lingua().c_str());
    cmd.bind(":palavras", boost::lexical_cast<std::string>(texto->get_palavras()).c_str());
    cmd.bind(":conteudo", texto->get_conteudo().c_str());
    
    if (dynamic_cast<TextoTecnico *>(texto)) {
        cmd.bind(":tipo_obj", boost::lexical_cast<std::string>(kTextoTecnico).c_str());
        
        cmd.bind(":tipo_args", boost::lexical_cast<std::string>(((TextoTecnico *) texto)->get_dominio_especialidade()).c_str());
    } else if (dynamic_cast<TextoLiterario *>(texto)) {
        cmd.bind(":tipo_obj", boost::lexical_cast<std::string>(kTextoLiterario).c_str());
        
        cmd.bind(":tipo_args", (((TextoLiterario *) texto)->get_titulo() +
                                "," +
                                ((TextoLiterario *) texto)->get_autor()).c_str());
    } else if (dynamic_cast<TextoNoticioso *>(texto)) {
        cmd.bind(":tipo_obj", boost::lexical_cast<std::string>(kTextoNoticioso).c_str());
        
        cmd.bind(":tipo_args", (((TextoNoticioso *) texto)->get_assunto() +
                                "," +
                                boost::lexical_cast<std::string>(((TextoNoticioso *) texto)->get_tipo_jornal())).c_str());
    } else
        throw "Unrecognized text type.";
    
    if (!cmd.execute())
        return true;
    
    return false;
}

bool DatabaseManager::create_update_record(Tradutor *tradutor) {
    init_db(db);
    
    //  Check for record existance
    //      - Exists:   Update.
    //      - Else:     Create.
    
    std::string query_str = "SELECT * FROM `tradutores` WHERE id=" + boost::lexical_cast<std::string>(tradutor->get_id()) + " LIMIT 1";
    
    query qry(db, query_str.c_str());
    
    std::string query = "INSERT INTO `tradutores` (id, nome, anos_experiencia, linguas) VALUES (:id, :nome, :anos_experiencia, :linguas)";
    
    for (query::iterator i = qry.begin(); i != qry.end(); ++i)
        query = "UPDATE `tradutores` SET nome=:nome, anos_experiencia=:anos_experiencia, linguas=:linguas WHERE id=:id";
    
    std::stringstream ss;
    
    for (size_t i = 0; i < tradutor->get_linguas().size(); ++i) {
        if (i != 0)
            ss << ",";
        ss << tradutor->get_linguas()[i];
    }
    
    command cmd(db, query.c_str());
    
    cmd.bind(":id", boost::lexical_cast<std::string>(tradutor->get_id()).c_str());
    cmd.bind(":nome", tradutor->get_nome().c_str());
    cmd.bind(":anos_experiencia", boost::lexical_cast<std::string>(tradutor->get_anos_experiencia()).c_str());
    cmd.bind(":linguas", ss.str().c_str());
    
    if (!cmd.execute())
        return true;
    
    return false;
}

bool DatabaseManager::create_update_record(Encomenda *encomenda) {
    init_db(db);
    
    //  Check for record existance
    //      - Exists:   Update.
    //      - Else:     Create.
    
    std::string query_str = "SELECT * FROM `encomendas` WHERE id=" + boost::lexical_cast<std::string>(encomenda->get_id()) + " LIMIT 1";
    
    query qry(db, query_str.c_str());
    
    std::string query = "INSERT INTO `encomendas` (id, texto_id, lingua_destino, duracao_max_dias, tradutor_id, timestamp_entrega) VALUES (:id, :texto_id, :lingua_destino, :duracao_max_dias, :tradutor_id, :timestamp_entrega)";
    
    for (query::iterator i = qry.begin(); i != qry.end(); ++i)
        query = "UPDATE `encomendas` SET texto_id=:texto_id, lingua_destino=:lingua_destino, duracao_max_dias=:duracao_max_dias, tradutor_id=:tradutor_id, timestamp_entrega=:timestamp_entrega WHERE id=:id";
    
    command cmd(db, query.c_str());
    
    cmd.bind(":id", boost::lexical_cast<std::string>(encomenda->get_id()).c_str());
    cmd.bind(":texto_id", boost::lexical_cast<std::string>(encomenda->get_texto()->get_id()).c_str());
    cmd.bind(":lingua_destino", encomenda->get_lingua_destino().c_str());
    cmd.bind(":duracao_max_dias", boost::lexical_cast<std::string>(encomenda->get_duracao_max_dias()).c_str());
    cmd.bind(":tradutor_id", boost::lexical_cast<std::string>(encomenda->get_tradutor()->get_id()).c_str());
    cmd.bind(":timestamp_entrega", boost::lexical_cast<std::string>(encomenda->get_timestamp_entrega()).c_str());
    
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

unsigned int DatabaseManager::get_maior_id(kClass asker) {
    init_db(db);
    
    std::string query_str = std::string("SELECT * FROM `") + std::string(asker == kClassEncomenda ? "encomendas" : (asker == kClassTexto ? "textos" : "tradutores")) + std::string("` SORT BY `id` DESC LIMIT 1");
    
    query qry(db, query_str.c_str());
    
    for (query::iterator i = qry.begin(); i != qry.end(); ++i) {
        unsigned int id;
        
        boost::tie(id) = (*i).get_columns<int>(0);
        
        return id;
    }
    
    return 0;
}
