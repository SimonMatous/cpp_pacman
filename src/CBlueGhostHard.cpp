/*
 * @author Šimon Matouš (matousi1)
 * on 17.06.2020
 */
#include "CBlueGhostHard.h"

void CBlueGhostHard::Stun()
{
    m_roundsLeftStunned = 10;
}

void CBlueGhostHard::AddWait()
{
    m_waitTillSpawn = 8;
}

char CBlueGhostHard::Strategy(const char &dir, std::map<std::pair<size_t, size_t>, char> &m_Content,const size_t & x,const size_t & y)
{
    /** finds the target block based on Pacmans direction, Pacmans location and his own location */
    if ( m_speedIterator == m_speed ) {
        size_t Target_X = x, Target_Y = y;
        if ( dir == 'L') {
            Target_X -= 3;
            if ( y > m_Y )
                Target_Y += 3;
            else if ( y < m_Y )
                Target_Y -=3;
        }
        else if ( dir == 'R') {
            Target_X += 3;
            if ( y > m_Y )
                Target_Y += 3;
            else if ( y < m_Y )
                Target_Y -=3;
        }
        else if ( dir == 'U') {
            Target_Y -= 3;
            if ( x > m_X )
                Target_X += 3;
            else if ( x < m_X )
                Target_X -=3;
        }
        else{
            Target_Y += 3;
            if ( x > m_X )
                Target_X += 3;
            else if ( x < m_X )
                Target_X -=3;
        }
        if ( m_roundsLeftStunned > 0 )
            m_roundsLeftStunned--;
        m_speedIterator = 0;
        return ScatterChase(3, 2, 4, 1, m_Content, Target_X, Target_Y);
    }
    else {
        m_speedIterator++;
        return 'D';
    }
}
