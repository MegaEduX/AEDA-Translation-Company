//
//  Tradutor.h
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - Second Project
//

#ifndef __translation_company__Tradutor__
#define __translation_company__Tradutor__

#include <iostream>
#include <vector>

#include "Texto.h"

class Encomenda;

/**
 *  Tradutor class.
 *  This class packages the details about a translator and provides some functionality on them.
 */

class Tradutor {
    static unsigned int _maior_id_tradutor;
    
    bool _contratado;
    
    unsigned int _id;
    unsigned int _anos_experiencia;
    
    std::string _nome;
    
    std::vector<std::string> _linguas;
    
    unsigned int _get_tempo_ocupado();
    
public:
    /**
     *  Class Constructor.
     *  @param id The object ID.
     *  @param nome The name of the translator.
     *  @param anos_experiencia The experience of the translator, in years. Should be at least 1.
     *  @param linguas The maximum number of days the order should be fullfilled in.
     */
    
    Tradutor(unsigned int id, std::string nome, unsigned int anos_experiencia, std::vector<std::string> linguas);
    
    /**
     *  Class Constructor.
     *  @param id The object ID.
     *  @param nome The name of the translator.
     *  @param anos_experiencia The experience of the translator, in years. Should be at least 1.
     *  @param linguas The maximum number of days the order should be fullfilled in.
     *  @param contratado true if the translator is currently hired, false if not.
     */
    
    Tradutor(unsigned int id, std::string nome, unsigned int anos_experiencia, std::vector<std::string> linguas, bool contratado);
    
    /**
     *  Calculates the cost of a given translation.
     *  @param texto The text to translate.
     *  @return The cost (in euros).
     */
    
    double custoTraducao(Texto *texto);
    
    /**
     *  Calculates the time to fullfill a translation.
     *  Please note that this function does NOT take into account other work the translator may have.
     *  @param texto The text to translate.
     *  @return The time, in seconds.
     */
    
    unsigned int tempoEstimado(Texto *text);
    
    /**
     *  Calculates the time to fullfill a given order.
     *  @param texto The text to translate.
     *  @return The time, in seconds.
     */
    
    unsigned int tempoEstimado(Encomenda *encomenda);
    
    /**
     *  Getter for the ID of the translator.
     *  @return The ID of the order.
     */
    
    unsigned int get_id();
    
    /**
     *  Getter for the years of experience of the translator.
     *  @return The experience of the translator, in years.
     */
    
    unsigned int get_anos_experiencia();
    
    /**
     *  Setter for the years of experience of the translator.
     *  @param anos_exp The experience of the translator, in years.
     */
    
    void set_anos_experiencia(unsigned int anos_exp);
    
    /**
     *  Getter for the biggest translator ID (of all known translators).
     *  @return The biggest translator ID.
     */
    
    static unsigned int get_maior_id();
    
    /**
     *  Checks if the translator is able to fullfill a given translation.
     *  @param encomenda The order to check against.
     *  @return true or false, depending whether the order can be, or not, fullfilled.
     */
    
    bool podeSatisfazerEncomenda(Encomenda *encomenda);
    
    /**
     *  Getter for name of the translator.
     *  @return The name of the translator.
     */
    
    std::string get_nome() const;
    
    /**
     *  Setter for name of the translator.
     *  @param nome The name of the translator.
     */
    
    void set_nome(std::string nome);
    
    /**
     *  Getter for the languages known to the translator.
     *  @return A vector containing the languages known to the translator.
     */
    
    std::vector<std::string> get_linguas();
    
    /**
     *  Setter for the languages known to the translator.
     *  @param linguas A vector containing the languages known to the translator.
     */
    
    void set_linguas(std::vector<std::string> linguas);
    
    /**
     *  Getter for employment status of the translator.
     *  @return true if employed, false if not.
     */
    
    bool get_contratado();
    
    /**
     *  Setter for employment status of the translator.
     *  @param cont true if employed, false if not.
     */
    
    void set_contratado(bool cont);
    
    /**
     *  Overloaded comparision < operator.
     *  Compares the names of two translators.
     *  @param trad The translator to compare to.
     *  @result The comparision result.
     */
    
    bool inline operator<(const Tradutor &trad) const {
        return (_nome.compare(trad.get_nome()) < 0);
    }
};

#endif /* defined(__translation_company__Tradutor__) */
