/*
 * @author Šimon Matouš (matousi1)
 * on 25.05.2020
 */


#include "COrangeGhostEasy.h"


void COrangeGhostEasy::Stun() {
    m_roundsLeftStunned = 50;
}

void COrangeGhostEasy::AddWait() {
    m_waitTillSpawn = 30;
}
