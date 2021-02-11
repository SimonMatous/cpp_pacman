/*
 * @author Šimon Matouš (matousi1)
 * on 13.06.2020
 */
#include "CPinkGhostMedium.h"

void CPinkGhostMedium::Stun()
{
    m_roundsLeftStunned = 20;
}

void CPinkGhostMedium::AddWait()
{
    m_waitTillSpawn = 15;
}

char CPinkGhostMedium::Strategy(const char &dir, std::map<std::pair<size_t, size_t>, char> &m_Content,const size_t & x,const size_t & y)
{
    if ( m_speedIterator == m_speed ) {
        char retVal;
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
        /** determines which mode is ghost in */
        if ((m_modeCounter >= 10 || m_switchToChase > 3) && m_roundsLeftStunned == 0) {
                retVal = ScatterChase(2, 4, 1, 3, m_Content, Target_X, Target_Y);
        } else
            retVal = ScatterChase(2, 4, 1, 3, m_Content, 0, 0);

        ModeManager();
        m_speedIterator = 0;
        return retVal;
    }
    else {
        m_speedIterator++;
        return 'D';
    }
}
void CPinkGhostMedium::ModeManager()
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