/*
 * @author Šimon Matouš (matousi1)
 * on 20.05.2020
 */
#pragma once


#include <string>
#include <cstring>
#include <iostream>
#include <termios.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#include "CPacman.h"
#include "CMap.h"
#include "CGhost.h"

#include "COrangeGhostEasy.h"
#include "CRedGhostEasy.h"
#include "CPinkGhostEasy.h"
#include "CBlueGhostEasy.h"

#include "CRedGhostMedium.h"
#include "COrangeGhostMedium.h"
#include "CPinkGhostMedium.h"
#include "CBlueGhostMedium.h"

#include "CRedGhostHard.h"
#include "COrangeGhostHard.h"
#include "CPinkGhostHard.h"
#include "CBlueGhostHard.h"



class CSession
{
public:
    /** the session game is controlled from here */
    explicit CSession               (const size_t & diff      , const size_t & timer,
                                     const size_t & fruitTimer, const size_t & speed)                       ;
             ~CSession              ()                                                                      ;
    /** prints that the player won*/
    void     Won                    ()                                                                 const;
    /** prints that the player lost*/
    void     Lost                   ()                                                                 const;
    void     PrintSession           ()                                                                 const;
    /** creates ghosts with given difficulty and speed */
    void     CreateGhosts           (const size_t & diff)                                                   ;
    /** spawns for the first time or respawns ghost on their spawn point which is in front of the door*/
    void     SpawnGhosts            (CGhost & ghost, std::map <std::pair<size_t,size_t>, char > & m_Content);
    /** makes ghosts vurnerable after Player picks up a power up( = 'o') */
    void     Vulnerable             (const bool & vul )                                                     ;
    /** manages ghosts movement and spawning */
    void     GhostManager           (CGhost & ghost, const size_t & amt, char & result )                    ;
    /** spawns the fruit when a certain amount of collectibles is picked up */
    void     FruitManager           (bool & fruitManager)                                                   ;
    /** checks if PacMan was killed and if the game was ended (by time, picking up all collectibles or loosing all lives)
     *  @returns true if Pacman was killed
     *  @returns false when he wasn't */
    bool     EndingManager          (const char & result, char & PacMoving)                                 ;
    /** resets ghost and gives him cooldown */
    void     DeleteGhost            (CGhost & ghost)                                                        ;
    /** resets Pacman and all ghosts despawn and recieve cooldown before spawning again */
    void     RespawnPac             ()                                                                      ;
    /** moves Pacman based on input
     *  @returns m_pac.MoveLeft/Right/Up/Down(...) [commented in CPacman.h]*/
    size_t   PlayerMove             (const char & pacM, bool & vulnerable)                                  ;
    /** Turns players input into moving Pacman a certain direction*/
    char     Turn                   (bool & vulnerable, char & PacMoving)                                   ;
    /** these 3 methods are from https://gist.github.com/whyrusleeping/3983293
     *  used for non-blocking input */
    void     RestoreKeyboardBlocking(struct termios *initial_settings)                                      ;
    char     GetcharAlt             ()                                                                      ;
    void     SetKeyboardNonBlock    (struct termios *initial_settings)                                      ;
private:
    size_t  m_difficulity                        ;
    CMap    m_map                                ;
    CGhost *m_Inky, *m_Pinky, *m_Blinky, *m_Clyde;
    CPacman m_pac                                ;
    size_t  m_lives                              ;
    size_t  m_timer                              ;
    size_t  m_fruitTimer                         ;
    size_t  m_speed                              ;
};
