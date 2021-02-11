/*
 * @author Šimon Matouš (matousi1)
 * on 10.06.2020
 */
#pragma once
#include <map>
#include "CGhost.h"

class CBlueGhostEasy
        :public CGhost
{
public:
    CBlueGhostEasy(const size_t & door_x , const size_t & door_y ,
                   const size_t & map_x  , const size_t & map_y  ,
                   const size_t & spawn_x, const size_t & spawn_y,
                   const size_t & speed ) :
                   CGhost(door_x, door_y, map_x, map_y, spawn_x, spawn_y, speed )
    {
        m_normal  = 'W'        ;
        m_spooked = 'w'        ;
        m_active  = false      ;
        m_roundsLeftStunned = 0;
        m_waitTillSpawn     = 0;

    }
    void Stun () override;
    void AddWait () override;
};
