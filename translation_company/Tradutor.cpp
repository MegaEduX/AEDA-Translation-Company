//
//  Tradutor.cpp
//  translation_company
//
//  Created by Eduardo Almeida on 14/10/13.
//  Copyright (c) 2013 Bitten Apps. All rights reserved.
//

#include "Tradutor.h"

#include "Encomenda.h"

#include "DatabaseManager.h"

#define days_to_seconds(days) days * 60 * 60 * 24

unsigned int Tradutor::_maior_id_tradutor = DatabaseManager(db_path).get_maior_id(kClassTradutor);

Tradutor::Tradutor(unsigned int id, std::string nome, unsigned int anos_experiencia, std::vector<std::string> linguas) {
    _id = id;
    _nome = nome;
    _anos_experiencia = anos_experiencia;
    _linguas = linguas;
    
    if (id > _maior_id_tradutor)
        _maior_id_tradutor = id;
}

unsigned int Tradutor::get_maior_id() {
    return _maior_id_tradutor;
}

unsigned int Tradutor::get_id() {
    return _id;
}

std::string Tradutor::get_nome() {
    return _nome;
}

unsigned int Tradutor::get_anos_experiencia() {
    return _anos_experiencia;
}

std::vector<std::string> Tradutor::get_linguas() {
    return _linguas;
}

unsigned int Tradutor::_get_tempo_ocupado() {
    DatabaseManager dbman = DatabaseManager(db_path);
    
    unsigned int tempo_ocupado = 0;
    
    std::vector<Encomenda *> all_enc = dbman.get_encomendas();
    
    for (int i = 0; i < all_enc.size(); i++)
        if (all_enc[i]->get_tradutor()->get_id() == _id) {
            tempo_ocupado += tempoEstimado(all_enc[i]->get_texto());
        }
    
    return tempo_ocupado;
}

/*
 *  We had no guidelines for these equations...
 *  So we made up our own!
 */

double Tradutor::custoTraducao(Texto *texto) {
    //  complexidade * anos de experiencia / 10
    
    return ((double)texto->get_complexidade() * (double)_anos_experiencia / 1000.0f);
}

unsigned int Tradutor::tempoEstimado(Texto *texto) {
    //  complexidade * 20 / anos experiencia
    //  tempo retornado em segundos
    
    if (texto && texto != nullptr)
        return (int)(texto->get_complexidade() * 20 / _anos_experiencia);
    
    return 0;
}

unsigned int Tradutor::tempoEstimado(Encomenda *encomenda) {
    Texto *enc_text = encomenda->get_texto();
    
    return (_get_tempo_ocupado() + tempoEstimado(enc_text)); /* (texto->get_complexidade() * 20 / _anos_experiencia) */
}

bool Tradutor::get_pode_satisfazer_encomenda(Encomenda *encomenda) {
    unsigned int te_est = tempoEstimado(encomenda);
    
    return (days_to_seconds(encomenda->get_duracao_max_dias()) > te_est);
}
