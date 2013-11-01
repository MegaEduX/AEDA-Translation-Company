//
//  Tradutor.h
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#ifndef __translation_company__Tradutor__
#define __translation_company__Tradutor__

#include <iostream>
#include <vector>

#include "Texto.h"

class Encomenda;

class Tradutor {
    static unsigned int _maior_id_tradutor;
    
    unsigned int _id;
    unsigned int _anos_experiencia;
    
    std::string _nome;
    
    std::vector<std::string> _linguas;
    
    unsigned int _get_tempo_ocupado();
    
public:
    Tradutor(unsigned int id, std::string nome, unsigned int anos_experiencia, std::vector<std::string> linguas);
    
    double custoTraducao(Texto *);
    
    unsigned int tempoEstimado(Texto *);
    unsigned int tempoEstimado(Encomenda *encomenda);
    
    unsigned int get_id();
    
    unsigned int get_anos_experiencia();
    void set_anos_experiencia(unsigned int anos_exp);
    
    static unsigned int get_maior_id();
    
    bool podeSatisfazerEncomenda(Encomenda *encomenda);
    
    std::string get_nome();
    void set_nome(std::string nome);
    
    std::vector<std::string> get_linguas();
    void set_linguas(std::vector<std::string> linguas);
};

#endif /* defined(__translation_company__Tradutor__) */
