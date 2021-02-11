/*
 * @author Šimon Matouš (matousi1)
 * on 10.06.2020
 */
#include "CPinkGhostEasy.h"

void CPinkGhostEasy::Stun()
{
    m_roundsLeftStunned = 50;
}

void CPinkGhostEasy::AddWait()
{
    m_waitTillSpawn = 30;
}
