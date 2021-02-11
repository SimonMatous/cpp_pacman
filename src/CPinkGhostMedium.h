/*
 * @author Šimon Matouš (matousi1)
 * on 13.06.2020
 */
#pragma once
#include <map>
#include "CGhost.h"

class CPinkGhostMedium
        :public CGhost
{
public:
    CPinkGhostMedium(const size_t & door_x , const size_t & door_y ,
                     const size_t & map_x  , const size_t & map_y  ,
                     const size_t & spawn_x, const size_t & spawn_y,
                     const size_t & speed ) :
            CGhost(door_x, door_y, map_x, map_y, spawn_x, spawn_y, speed )
    {
        m_reverseDir = 'r'     ;
        m_normal     = 'P'     ;
        m_spooked    = 'p'     ;
        m_active     = false   ;
        m_roundsLeftStunned = 0;
        m_waitTillSpawn     = 0;
        m_modeCounter       = 0;
        m_switchToChase     = 0;


    }
    void Stun        ()                                                                                                          override;
    void AddWait     ()                                                                                                          override;
    char Strategy    (const char &dir, std::map <std::pair<size_t,size_t>, char > & m_Content,const size_t & x,const size_t & y) override;
    /** manages changing modes */
    void ModeManager ()                                                                                                                  ;
private:
    size_t m_modeCounter      ;
    size_t m_switchToChase    ;
};
