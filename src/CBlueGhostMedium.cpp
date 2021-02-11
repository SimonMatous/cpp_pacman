/*
 * @author Šimon Matouš (matousi1)
 * on 13.06.2020
 */
#include "CBlueGhostMedium.h"

void CBlueGhostMedium::Stun()
{
    m_roundsLeftStunned = 20;
}

void CBlueGhostMedium::AddWait()
{
    m_waitTillSpawn = 15;
}

char CBlueGhostMedium::Strategy(const char &dir, std::map<std::pair<size_t, size_t>, char> &m_Content,const size_t & x,const size_t & y)
{
    /** finds the target block based on Pacmans direction, Pacmans location and his own location */
    if ( m_speedIterator == m_speed ) {
        char retVal;
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
        /** determines which mode is ghost in */
        if ((m_modeCounter >= 10 || m_switchToChase > 3) && m_roundsLeftStunned == 0) {
            retVal = ScatterChase(3, 2, 4, 1, m_Content, Target_X, Target_Y);
        } else{
            size_t scatter_Y = m_Content.rbegin()->first.first;
            size_t scatter_X = m_Content.rbegin()->first.second;
            retVal = ScatterChase(3, 2, 4, 1, m_Content, scatter_X, scatter_Y);
        }

        ModeManager();
        m_speedIterator = 0;
        return retVal;
    }
    else {
        m_speedIterator++;
        return 'D';
    }
}
void CBlueGhostMedium::ModeManager()
{
    if ( m_roundsLeftStunned > 0 )
        m_roundsLeftStunned--;
    else {
        if (m_modeCounter == 10)
            ChangeDir();
        if (m_modeCounter == 30) {
            m_modeCounter = 0;
            m_switchToChase++;
            ChangeDir();
        } else
            m_modeCounter++;
    }
}