/*
 * @author Šimon Matouš (matousi1)
 * on 07.06.2020
 */
#include "CRedGhostMedium.h"

void CRedGhostMedium::Stun()
{
    m_roundsLeftStunned = 20;
}

void CRedGhostMedium::AddWait()
{
    m_waitTillSpawn = 15;
}

char CRedGhostMedium::Strategy(const char &/* dir */, std::map<std::pair<size_t, size_t>, char> &m_Content,const size_t & x,const size_t & y)
{
    if ( m_switchToChase > 3)/** after some time Blinky goes into Elroy phase */
        m_speed= m_speed/2;
    if (  m_speedIterator == m_speed  ) {
        char retVal;
        /** determines which mode is ghost in */
        if ((m_modeCounter >= 10 || m_switchToChase > 3) && m_roundsLeftStunned == 0)
            retVal = ScatterChase(1, 2, 3, 4, m_Content, x, y);
        else {
            size_t scatter_X = m_Content.rbegin()->first.second;
            retVal = ScatterChase(1, 2, 3, 4, m_Content, scatter_X, 0);
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
void CRedGhostMedium::ModeManager()
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