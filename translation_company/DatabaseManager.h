//
//  DatabaseManager.h
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#ifndef __translation_company__DatabaseManager__
#define __translation_company__DatabaseManager__

#include <iostream>
#include <vector>

#include "sqlite3pp.h"

#include "Texto.h"

#include "TextoTecnico.h"
#include "TextoLiterario.h"
#include "TextoNoticioso.h"

#include "Tradutor.h"
#include "Encomenda.h"

typedef enum {
    kTextoBase,
    kTextoTecnico,
    kTextoLiterario,
    kTextoNoticioso
} kTexto;

class DatabaseManager {
    std::string _dbfp;
    
    Texto *_get_texto_with_id(unsigned int id);
    
    bool _prepare_database();
    
public:
    DatabaseManager(std::string filepath);
    ~DatabaseManager();
    
    std::vector<Texto *> get_textos();
    void get_textos_by_type(std::vector<TextoTecnico *> &textos_tecnicos, std::vector<TextoLiterario *> &textos_literarios, std::vector<TextoNoticioso *> &textos_noticiosos);
    
    std::vector<Tradutor *> get_tradutores();
    std::vector<Encomenda *> get_encomendas();
    
    bool create_update_record(Texto *texto);
    bool delete_record(Texto *texto);
    
    bool create_update_record(Tradutor *tradutor);
    bool delete_record(Tradutor *tradutor);
    
    bool create_update_record(Encomenda *encomenda);
    bool delete_record(Encomenda *encomenda);
};

#endif /* defined(__translation_company__DatabaseManager__) */