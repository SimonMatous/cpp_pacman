/*
 * @author Šimon Matouš (matousi1)
 * on 01.06.2020
 */
#include "CRedGhostEasy.h"


void CRedGhostEasy::Stun()
{
    m_roundsLeftStunned = 50;
}

void CRedGhostEasy::AddWait()
{
    m_waitTillSpawn = 30;
}
