//
//  Texto.cpp
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - Second Project
//

#include <sstream>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "Texto.h"

#include "DatabaseManager.h"

#define WHITESPACE_ENDLINE_CHARS " \t\n\v\f\r"

unsigned int Texto::_maior_id_texto = DatabaseManager(db_path).get_maior_id(kClassTexto);

inline unsigned int _count_words(const std::string& s) {
    /*
     * Taken from http://www.cplusplus.com/forum/general/30929/
     */
    
    std::string x = s;
    std::replace_if(x.begin(), x.end(), std::ptr_fun <int, int>(std::isspace), ' ');
    x.erase(0, x.find_first_not_of( " " ));
    if (x.empty()) return 0;
    return (unsigned int)std::count(x.begin(), std::unique(x.begin(), x.end() ), ' ') + !std::isspace(*s.rbegin());
}

Texto::Texto(unsigned int id, std::string lingua, std::string conteudo) {
    _id = id;
    
    _lingua = lingua;
    _conteudo = conteudo;
    
    if (id > _maior_id_texto)
        _maior_id_texto = id;
    
    _palavras = _count_words(conteudo);
}

Texto::Texto(unsigned int id, std::string lingua, unsigned long palavras, std::string conteudo) {
    _id = id;
    
    _lingua = lingua;
    _conteudo = conteudo;
    
    if (id > _maior_id_texto)
        _maior_id_texto = id;
    
    _palavras = palavras;
}

unsigned int Texto::get_maior_id() {
    return _maior_id_texto;
}

unsigned int Texto::get_id() {
    return _id;
}

unsigned long Texto::get_palavras() const {
    return _palavras;
}

std::string Texto::get_lingua() {
    return _lingua;
}

void Texto::set_lingua(std::string lingua) {
    _lingua = lingua;
}

std::string Texto::get_conteudo() {
    return _conteudo;
}

void Texto::set_conteudo(std::string conteudo) {
    _conteudo = conteudo;
}

unsigned int Texto::complexidade() {
    return (unsigned int)(this->get_palavras() / 10);
}
