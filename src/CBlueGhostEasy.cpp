/*
 * @author Šimon Matouš (matousi1)
 * on 10.06.2020
 */
#include "CBlueGhostEasy.h"

void CBlueGhostEasy::Stun()
{
    m_roundsLeftStunned = 50;
}

void CBlueGhostEasy::AddWait()
{
    m_waitTillSpawn = 30;
}