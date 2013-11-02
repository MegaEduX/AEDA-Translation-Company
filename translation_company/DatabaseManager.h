//
//  DatabaseManager.h
//  translation_company
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/13.
//  AEDA (EIC0013) 2013/2014 - T1G04 - First Project
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

/**
 *  Text Types enum.
 *  Defines the types of the text class as a typedef.
 */

typedef enum {
    kTextoBase,         /**< Base Text. */
    kTextoTecnico,      /**< Technical Text. */
    kTextoLiterario,    /**< Literary Text. */
    kTextoNoticioso     /**< News Text. */
} kTexto;               /**< Text enum. */

/**
 *  Class enum.
 *  Defines the classes as a typedef (to avoid dirty workarounds).
 */

typedef enum {
    kClassTexto,        /**< Class Texto. */
    kClassTradutor,     /**< Class Translator. */
    kClassEncomenda     /**< Class Order. */
} kClass;               /**< Class Enum. */

/**
 *  Database Manager class.
 *  This class handles all the IO to the database (with some helper functions).
 */

class DatabaseManager {
    std::string _dbfp;
    
    Texto *_get_texto_with_id(unsigned int id);
    
    bool _prepare_database();
    
public:
    /**
     *  Class Constructor.
     *  @param filepath The path for the sqlite3 database file. If a file doesn't exist at target, a new one will be created and initialized.
     */
    
    DatabaseManager(std::string filepath);
    
    /**
     *  Class Destructor.
     */
    
    ~DatabaseManager();
    
    /**
     * The getter for the texts.
     * @return A vector with all the texts (as Texto object pointers).
     */
    
    std::vector<Texto *> get_textos();
    
    /**
     *  A getter for the texts, separated by type vectors.
     *  @param textos_tecnicos The variable that will hold the technical texts.
     *  @param textos_literarios The variable that will hold the literary texts.
     *  @param textos_noticiosos The variable that will hold the news texts.
     *  @see get_textos()
     */
    
    void get_textos_by_type(std::vector<TextoTecnico *> &textos_tecnicos, std::vector<TextoLiterario *> &textos_literarios, std::vector<TextoNoticioso *> &textos_noticiosos);
    
    /**
     * The getter for the translators.
     * @return A vector with all the translators. (as Tradutor object pointers).
     */
    
    std::vector<Tradutor *> get_tradutores();
    
    /**
     * The getter for the orders.
     * @return A vector with all the orders (as Encomenda object pointers).
     */
    
    std::vector<Encomenda *> get_encomendas();
    
    /**
     *  Creates a new record or updates an existing one.
     *  @param texto The text to be saved.
     *  @return true on success, false on error.
     */
    
    bool create_update_record(Texto *texto);
    
    /**
     *  Deletes an existing record.
     *  @param texto The text to be deleted.
     *  @return true on success, false on error.
     */
    
    bool delete_record(Texto *texto);
    
    /**
     *  Creates a new record or updates an existing one.
     *  @param tradutor The translator to be saved.
     *  @return true on success, false on error.
     */
    
    bool create_update_record(Tradutor *tradutor);
    
    /**
     *  Deletes an existing record.
     *  @param tradutor The translator to be deleted.
     *  @return true on success, false on error.
     */
    
    bool delete_record(Tradutor *tradutor);
    
    /**
     *  Creates a new record or updates an existing one.
     *  @param encomenda The order to be saved.
     *  @return true on success, false on error.
     */
    
    bool create_update_record(Encomenda *encomenda);
    
    /**
     *  Deletes an existing record.
     *  @param encomenda The order to be deleted.
     *  @return true on success, false on error.
     */
    
    bool delete_record(Encomenda *encomenda);
    
    /**
     *  Returns the biggest ID record for a class type.
     *  @param kClass The class as defined on the Class enum.
     *  @see Class enum
     *  @return The requested ID.
     */
    
    unsigned int get_maior_id(kClass asker);
};

#endif /* defined(__translation_company__DatabaseManager__) */
