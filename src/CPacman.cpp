/*
 * @author Šimon Matouš (matousi1)
 * on 23.05.2020
 */
#include <string>
#include <cstring>
#include "CPacman.h"
#include "CSession.h"
CPacman::CPacman(const size_t & x, const size_t & y, const size_t & collectibles,const size_t & map_X, const size_t & map_Y)
    :m_X(x),m_Y(y),m_score(0), m_collectibles(collectibles), m_map_X(map_X), m_map_Y(map_Y), m_spawn_X(x), m_spawn_Y(y)
{}

char CPacman::MoveLeft(std::map <std::pair<size_t,size_t>, char > & m_Content, bool & stun)
{
    char  newPos = m_Content.at(std::make_pair(m_Y,m_X - 1 ));
    if ( newPos == '.' ){
        m_score+=10;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_X--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
        m_collectibles--;
    }
    else if ( newPos == ' ' ){
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_X--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    }
    else if ( newPos == 'o' ){
        m_score+=50;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_X--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
        m_collectibles--;
        stun = true;
    }
    else if ( newPos == 'T'){
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_X = m_map_X-3;
        if ( m_Content[std::make_pair(m_Y,m_X)] == '.' || m_Content[std::make_pair(m_Y,m_X)] == 'o')
            m_collectibles--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    }
    else if ( newPos == 'B' ){
        m_score+=100;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_X--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    }
    else if ( newPos == 'W' || newPos == 'Q' || newPos == 'R' || newPos == 'P' ) {
        m_Content[std::make_pair(m_Y, m_X)] = ' ';
        return 'l';
    }
    else if ( newPos == 'w' || newPos == 'q' || newPos == 'r' || newPos == 'p' ){
        m_score+=400;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_X--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
        switch (newPos) {
            case 'w' :
                return 'w';
            case 'q':
                return 'q';
            case 'r':
                return 'r';
            case 'p':
                return 'p';
        }
    }
    else
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    if ( m_collectibles == 0)
        return 'v';
    return 'L';
}

char CPacman::MoveRight(std::map <std::pair<size_t,size_t>, char > & m_Content, bool & stun)
{
    char  newPos = m_Content.at(std::make_pair(m_Y,m_X + 1 ));
    if ( newPos == '.' ){
        m_score+=10;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_X++;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
        m_collectibles--;
    }
    else if ( newPos == ' ' ){
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_X++;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    }
    else if ( newPos == 'o' ){
        m_score+=50;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_X++;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
        m_collectibles--;
        stun = true;
    }
    else if ( newPos == 'T'){
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_X = 2;
        if ( m_Content[std::make_pair(m_Y,m_X)] == '.' || m_Content[std::make_pair(m_Y,m_X)] == 'o')
            m_collectibles--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    }
    else if ( newPos == 'B' ){
        m_score+=100;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_X++;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    }
    else if ( newPos == 'W' || newPos == 'Q' || newPos == 'R' || newPos == 'P' ) {
        m_Content[std::make_pair(m_Y, m_X)] = ' ';
        return 'l';
    }
    else if ( newPos == 'w' || newPos == 'q' || newPos == 'r' || newPos == 'p' ){
        m_score+=400;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_X++;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
        switch (newPos) {
            case 'w' :
                return 'w';
            case 'q':
                return 'q';
            case 'r':
                return 'r';
            case 'p':
                return 'p';
        }
    }
    else
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    if ( m_collectibles == 0)
        return 'v';
    return 'R';
}

char CPacman::MoveUp(std::map <std::pair<size_t,size_t>, char > & m_Content, bool & stun)
{
    char  newPos = m_Content.at(std::make_pair(m_Y - 1,m_X ));
    if ( newPos == '.' ){
        m_score+=10;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_Y--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
        m_collectibles--;
    }
    else if ( newPos == ' ' ){
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_Y--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    }
    else if ( newPos == 'o' ){
        m_score+=50;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_Y--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
        m_collectibles--;
        stun = true;
    }
    else if ( newPos == 'T'){
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_Y = m_map_Y-3;
        if ( m_Content[std::make_pair(m_Y,m_X)] == '.' || m_Content[std::make_pair(m_Y,m_X)] == 'o')
            m_collectibles--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    }
    else if ( newPos == 'B' ){
        m_score+=100;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_Y--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    }
    else if ( newPos == 'W' || newPos == 'Q' || newPos == 'R' || newPos == 'P' ) {
        m_Content[std::make_pair(m_Y, m_X)] = ' ';
        return 'l';
    }
    else if ( newPos == 'w' || newPos == 'q' || newPos == 'r' || newPos == 'p' ){
        m_score+=400;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_Y--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
        switch (newPos) {
            case 'w' :
                return 'w';
            case 'q':
                return 'q';
            case 'r':
                return 'r';
            case 'p':
                return 'p';
        }
    }
    else
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    if ( m_collectibles == 0)
        return 'v';
    return 'U';
}

char CPacman::MoveDown(std::map <std::pair<size_t,size_t>, char > & m_Content, bool & stun)
{
    char  newPos = m_Content.at(std::make_pair(m_Y + 1,m_X ));
    if ( newPos == '.' ){
        m_score+=10;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_Y++;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
        m_collectibles--;
    }
    else if ( newPos == ' ' ){
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_Y++;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    }
    else if ( newPos == 'o' ){
        m_score+=50;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_Y++;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
        m_collectibles--;
        stun = true;
    }
    else if ( newPos == 'T'){
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_Y = 2;
        if ( m_Content[std::make_pair(m_Y,m_X)] == '.' || m_Content[std::make_pair(m_Y,m_X)] == 'o')
            m_collectibles--;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    }
    else if ( newPos == 'B' ){
        m_score+=100;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_Y++;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    }
    else if ( newPos == 'W' || newPos == 'Q' || newPos == 'R' || newPos == 'P' ) {
        m_Content[std::make_pair(m_Y, m_X)] = ' ';
        return 'l';
    }
    else if ( newPos == 'w' || newPos == 'q' || newPos == 'r' || newPos == 'p' ){
        m_score+=400;
        m_Content[std::make_pair(m_Y,m_X)] = ' ';
        m_Y++;
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
        switch (newPos) {
            case 'w' :
                return 'w';
            case 'q':
                return 'q';
            case 'r':
                return 'r';
            case 'p':
                return 'p';
        }
    }
    else
        m_Content[std::make_pair(m_Y,m_X)] = 'C';
    if ( m_collectibles == 0)
        return 'v';
    return 'D';
}

size_t CPacman::GetScore() const
{
    return m_score;
}
size_t CPacman::GetColl()  const
{
    return m_collectibles;
}

size_t CPacman::GetX() const {
    return m_X;
}

size_t CPacman::GetY() const {
    return m_Y;
}

void CPacman::RespawnPac(std::map<std::pair<size_t, size_t>, char> &m_Content)
{

    m_Content[std::make_pair(m_spawn_Y,m_spawn_X)] = 'C';
    m_X = m_spawn_X;
    m_Y = m_spawn_Y;
}

void CPacman::decColl()
{ m_collectibles--; }

void CPacman::incScore(const size_t & incr )
{
    m_score+=incr;
}
