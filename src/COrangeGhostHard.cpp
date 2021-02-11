/*
 * @author Šimon Matouš (matousi1)
 * on 17.06.2020
 */
#include "COrangeGhostHard.h"

void COrangeGhostHard::Stun()
{
    m_roundsLeftStunned = 10;
}

void COrangeGhostHard::AddWait()
{
    m_waitTillSpawn = 8;
}

char COrangeGhostHard::Strategy(const char & /* dir */, std::map<std::pair<size_t, size_t>, char> &m_Content,const size_t & x,const size_t & y)
{
    if ( m_speedIterator == m_speed ) {
        int holder;
        char retVal;
        holder = Convertor(m_X, m_Y, x, y);
        if (holder < 12)
            retVal = ScatterChase(4, 3, 2, 1, m_Content, x, y);
        else {
            size_t scatter_Y = m_Content.rbegin()->first.first;
            retVal = ScatterChase(4, 3, 2, 1, m_Content, 0, scatter_Y);
        }
        if ( m_roundsLeftStunned > 0 )
            m_roundsLeftStunned--;
        m_speedIterator = 0;
        return retVal;
    }
    else {
        m_speedIterator++;
        return 'D';
    }
}
