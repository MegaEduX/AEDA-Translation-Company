//
//  Additions.h
//
//  Originally Created By:
//  T3G12 - MIEIC 2012/2013
//  Eduardo Almeida, Joao Almeida and Joao Ramos
//
//  This namespace contains functions used on various parts of the program.
//

#ifndef AdditionsHeader
#define AdditionsHeader

#include <iostream>
#include <sstream>
#include <fstream>
#include <cerrno>
#include <vector>

#ifndef WIN32

/**
 *  Replacement _getch() for POSIX systems.
 *  @return The pressed key.
 */

int _getch();

#endif

static const std::string esc = "__\\esc_key_pressed\\__";	// I seriously doubt that anyone will type this into a field.

/**
 *  Additions namespace.
 *  Contains a lot of useful functions, in C and C++.
 *  This file was initially created for use on EIC0012 (PROG).
 */

namespace Additions {
    /**
     *  Converts a demlimiter-separated string into a vector.
     *  @param delimiter The delimiter.
     *  @param str The string to work with.
     *  @return An array with the "exploded" string.
     */
    
    std::vector<std::string> explode(const std::string &delimiter, const std::string &str);
    
    /**
     *  Reads the content of a given file.
     *  @param filename The path to the file.
     *  @return The file contents..
     */
    
    std::string get_file_contents(const char *filename);
    
    /**
     *  Reads the input from the standard input.
     *  @return The input, as a string.
     */
    
    std::string getline();
    
    /**
     *  Checks if a given string consists of numeric characters only.
     *  @param str The string to test against.
     *  @return true or false, depending on the result.
     */
    
    bool checkForOnlyNumeric(std::string str);
    
    /**
     *  Checks if the ESC key was pressed during a getline() input.
     *  @param str The getline() input result.
     *  @return true or false, depending on the result.
     */
    
    bool gotESC(std::string str);
    
    /**
     *  Clears the console.
     */
    
    void clearConsole();
    
    /**
     *  Waits until the return key is pressed.
     */
    
    void waitForReturn();
    
    /**
     *  Returns the current UNIX timestamp.
     *  @return The UNIX timestamp.
     */
    
    unsigned int currentTimestamp();
    
    /**
     *  Converts an UNIX timestamp to an user-readable string.
     *  @param timestamp An UNIX timestamp.
     *  @return An user-readable string representation.
     */
    
    std::string timestampToString(const long timestamp);
}

#endif
