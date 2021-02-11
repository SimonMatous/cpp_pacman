/*
 * @author Šimon Matouš (matousi1)
 * on 17.06.2020
 */
#include "CPinkGhostHard.h"

void CPinkGhostHard::Stun()
{
    m_roundsLeftStunned = 10;
}

void CPinkGhostHard::AddWait()
{
    m_waitTillSpawn = 8;
}

char CPinkGhostHard::Strategy(const char &dir, std::map<std::pair<size_t, size_t>, char> &m_Content,const size_t & x,const size_t & y)
{
    if ( m_speedIterator == m_speed ) {
        size_t Target_X = x, Target_Y = y;
        if ( dir == 'L')
            Target_X -=3;
        else if ( dir == 'R')
            Target_X +=3;
        else if ( dir == 'U') {
            /** simulating overflow error that the original game has */
            Target_Y -= 4;
            Target_X -= 4;
        }
        else if ( dir == 'D')
            Target_Y +=3;

        if ( m_roundsLeftStunned > 0 )
            m_roundsLeftStunned--;
        m_speedIterator = 0;
        return ScatterChase(2, 4, 1, 3, m_Content, Target_X, Target_Y);
    }
    else {
        m_speedIterator++;
        return 'D';
    }
}
