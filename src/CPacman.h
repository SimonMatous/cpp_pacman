/*
 * @author Šimon Matouš (matousi1)
 * on 23.05.2020
 */

#pragma once

#include <string>
#include <cstring>
#include <iostream>
#include <map>

class CPacman
{
public:
    CPacman        () = default                                                                                                 ;
    CPacman        (const size_t & x, const size_t & y, const size_t & collectibles, const size_t & map_X, const size_t & map_Y);
    void RespawnPac(std::map <std::pair<size_t,size_t>, char > & m_Content)                                                     ;
    /** Move(Up/Down/Left/Right) moves Pacman by one space
     *  @returns 'w'/'q'/'p'/'r' if Player steps on a stunned ghost
     *  @returns 'l' if player steps on a not stunned ghost
     *  @returns 'U'/'D'/'L'/'R' (direction which is Pacman pointing) if Player doesn't step on a ghost
     *  @returns 'v' when player loots the last collectible */
    char MoveUp    (std::map <std::pair<size_t,size_t>, char > & m_Content, bool & stun)                                        ;
    char MoveDown  (std::map <std::pair<size_t,size_t>, char > & m_Content, bool & stun)                                        ;
    char MoveLeft  (std::map <std::pair<size_t,size_t>, char > & m_Content, bool & stun)                                        ;
    char MoveRight (std::map <std::pair<size_t,size_t>, char > & m_Content, bool & stun)                                        ;
    void decColl   ()                                                                                                           ;
    void incScore  (const size_t & incr )                                                                                       ;
    size_t GetScore()                                                                                                      const;
    size_t GetColl ()                                                                                                      const;
    size_t GetX    ()                                                                                                      const;
    size_t GetY    ()                                                                                                      const;

private:
    size_t m_X             ;
    size_t m_Y             ;
    size_t m_score         ;
    size_t m_collectibles  ;
    const size_t m_map_X   ;
    const size_t m_map_Y   ;
    const size_t m_spawn_X ;
    const size_t m_spawn_Y ;
};