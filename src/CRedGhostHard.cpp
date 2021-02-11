/*
 * @author Šimon Matouš (matousi1)
 * on 17.06.2020
 */
#include "CRedGhostHard.h"

void CRedGhostHard::Stun()
{
    m_roundsLeftStunned = 10;
}

void CRedGhostHard::AddWait()
{
    m_waitTillSpawn = 8;
}

char CRedGhostHard::Strategy(const char &/* dir */, std::map<std::pair<size_t, size_t>, char> &m_Content,const size_t & x,const size_t & y)
{
    m_speed/=2;  /* Blinky goes into Elroy phase right away */
    if (  m_speedIterator == m_speed ) {
        if ( m_roundsLeftStunned > 0 )
            m_roundsLeftStunned--;
        m_speedIterator = 0;
        return ScatterChase(1, 2, 3, 4, m_Content, x, y);
    }
    else {
        m_speedIterator++;
        return 'D';
    }
}
