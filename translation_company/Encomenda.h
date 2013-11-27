//
//  Encomenda.h
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - Second Project
//

#ifndef __translation_company__Encomenda__
#define __translation_company__Encomenda__

#include <iostream>

#include "Tradutor.h"

class Texto;

/**
 *  Encomenda class.
 *  This class packages the details about an order and provides some functionality on them.
 */

class Encomenda {
    unsigned int _id;
    unsigned int _duracao_max_dias;
    
    uint64_t _timestamp_entrega;
    
    static unsigned int _maior_id_encomenda;
    
    Texto *_texto;
    Tradutor *_tradutor;
    
    std::string _lingua_destino;
    
public:
    /**
     *  Class Constructor.
     *  @param id The object ID.
     *  @param texto The text associated with the order.
     *  @param lingua_destino The language "texto" should be translated to.
     *  @param duracao_max_dias The maximum number of days the order should be fullfilled in. Should be at least 1.
     */
    
    Encomenda(unsigned int id, Texto *texto, std::string lingua_destino, unsigned int duracao_max_dias);
    
    /**
     *  Class Constructor.
     *  @param id The object ID.
     *  @param texto The text associated with the order.
     *  @param lingua_destino The language "texto" should be translated to.
     *  @param duracao_max_dias The maximum number of days the order should be fullfilled in. Should be at least 1.
     *  @param tradutor The translator associated with the order.
     *  @param timestamp_entrega The date, refered to as a timestamp, when the order will be fullfilled.
     */
    
    Encomenda(unsigned int id, Texto *texto, std::string lingua_destino, unsigned int duracao_max_dias, Tradutor *tradutor, uint64_t timestamp_entrega);
    
    /**
     *  Getter for the biggest order ID.
     *  @return The biggest order ID.
     */
    
    static unsigned int get_maior_id();
    
    /**
     *  Getter for the order ID
     *  @return The order ID.
     */
    
    unsigned int get_id() const;
    
    /**
     *  Getter for the maximum order duration.
     *  @return The maximum number of days the order should be fullfilled in.
     */
    
    unsigned int get_duracao_max_dias() const;
    
    /**
     *  Setter for the maximum order duration.
     *  @param dias The maximum number of days the order should be fullfilled in.
     */
    
    void set_duracao_max_dias(unsigned int dias);
    
    /**
     *  Getter for the text associated with the order.
     *  @return The text associated with the order.
     */
    
    Texto *get_texto() const;
    
    /**
     *  Setter for the text associated with the order.
     *  @param texto The text to be associated with the order.
     */
    
    void set_texto(Texto *texto);
    
    /**
     *  Getter for the translator assigned with the order.
     *  @return The translator assigned with the order.
     */
    
    Tradutor *get_tradutor() const;
    
    /**
     *  Setter for the translator assigned with the order.
     *  @param tradutor The translator to be assigned with the order.
     */
    
    void set_tradutor(Tradutor *tradutor);
    
    /**
     *  Getter for the language the order text should be translated to.
     *  @return The language the order text should be translated to.
     */
    
    std::string get_lingua_destino() const;
    
    /**
     *  Setter for the language the order text should be translated to.
     *  @param lingua The language the order text should be translated to.
     */
    
    void set_lingua_destino(std::string lingua);
    
    /**
     *  Getter for the date, refered to as a timestamp, when the order will be fullfilled.
     *  @return The date, refered to as a timestamp, when the order will be fullfilled.
     */
    
    uint64_t get_timestamp_entrega() const;
    
    /**
     *  Setter for the date, refered to as a timestamp, when the order will be fullfilled.
     *  This is only a setter, so no calculations are done. Please do the calculations before passing this value to avoid unexpected results.
     *  @param timestamp_entrega The date, refered to as a timestamp, when the order will be fullfilled.
     */
    
    void set_timestamp_entrega(uint64_t timestamp_entrega);
    
    /**
     *  Helper function, returns whether the order is fulfilled or not.
     *  @return true or false, depending if the order is, or not, fulfilled.
     */
    
    bool is_fulfilled() const;
};

#endif /* defined(__translation_company__Encomenda__) */
