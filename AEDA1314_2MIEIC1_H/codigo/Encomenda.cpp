//
//  Encomenda.cpp
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - First Project
//

#include "Encomenda.h"

#include "Texto.h"

#include "DatabaseManager.h"

unsigned int Encomenda::_maior_id_encomenda = DatabaseManager(db_path).get_maior_id(kClassEncomenda);

Encomenda::Encomenda(unsigned int id, Texto *texto, std::string lingua_destino, unsigned int duracao_max_dias) {
    _id = id;
    _texto = texto;
    _lingua_destino = lingua_destino;
    _duracao_max_dias = duracao_max_dias;
    _tradutor = nullptr;
    
    if (id > _maior_id_encomenda)
        _maior_id_encomenda = id;
}

Encomenda::Encomenda(unsigned int id, Texto *texto, std::string lingua_destino, unsigned int duracao_max_dias, Tradutor *tradutor, uint64_t timestamp_entrega) {
    _id = id;
    _texto = texto;
    _lingua_destino = lingua_destino;
    _duracao_max_dias = duracao_max_dias;
    _tradutor = tradutor;
    _timestamp_entrega = timestamp_entrega;
    
    if (id > _maior_id_encomenda)
        _maior_id_encomenda = id;
}

unsigned int Encomenda::get_maior_id() {
    return _maior_id_encomenda;
}

unsigned int Encomenda::get_id() {
    return _id;
}

Texto *Encomenda::get_texto() const {
    return _texto;
}

void Encomenda::set_texto(Texto *texto) {
    _texto = texto;
}

Tradutor* Encomenda::get_tradutor() const {
    return _tradutor;
}

void Encomenda::set_tradutor(Tradutor *trad) {
    _tradutor = trad;
}

std::string Encomenda::get_lingua_destino() {
    return _lingua_destino;
}

unsigned int Encomenda::get_duracao_max_dias() {
    return _duracao_max_dias;
}

void Encomenda::set_duracao_max_dias(unsigned int dias) {
    _duracao_max_dias = dias;
}

uint64_t Encomenda::get_timestamp_entrega() {
    return _timestamp_entrega;
}

void Encomenda::set_timestamp_entrega(uint64_t timestamp_entrega) {
    _timestamp_entrega = timestamp_entrega;
}
