/*
 * @author Šimon Matouš (matousi1)
 * on 20.05.2020
 */

#pragma once

#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>

#include "CSession.h"

class CApplication
{
public:
    /** all other methods are called from the constructor  */
           CApplication  ()                                                ;
           ~CApplication () = default                                      ;
    /** Csession is called from here
     * enables to restart the game after it ends */
    void   RunApplication()                                                ;
    /** registers the difficulty setting it was given */
    void   RegisterInput ()                                                ;
    /** checks if the difficulity setting is legit */
    void   LoadConfig    (const std::string & config, bool & loadingFailed);
private:
    std::string m_playAgain;
    size_t      m_timer    ;
    size_t      m_diff     ;
    size_t      m_speed    ;
    size_t      m_fruit    ;
};

