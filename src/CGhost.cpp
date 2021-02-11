/*
 * @author Šimon Matouš (matousi1)
 * on 25.05.2020
 */
#include <iostream>

#include "CGhost.h"

CGhost::CGhost (const size_t & door_x  , const size_t & door_y ,
                const size_t & map_x   , const size_t & map_y  ,
                const size_t & spawn_x , const size_t & spawn_y,
                const size_t & speed  )
                : m_door_X(door_x) , m_door_Y(door_y) , m_map_X(map_x), m_map_Y        (map_y),
                  m_X     (spawn_x), m_Y     (spawn_y), m_speed(speed), m_speedIterator(0)
{}


char CGhost::Strategy(const char &dir, std::map <std::pair<size_t,size_t>, char > & m_Content,const size_t & /* x */,const size_t & /* y */)
{
    if ( m_speedIterator == m_speed ) {
        char state, retVal;
        state = GetSkin();
        /** ghosts move the same direction as Pacman */
        if ( dir == 'R') {
            m_lastDir = 'R';
            retVal = NextStep(dir, state, m_Content);
        }
        else if ( dir == 'L') {
            m_lastDir = 'L';
            retVal = NextStep(dir, state, m_Content);
        }
        else if ( dir == 'U') {
            m_lastDir = 'U';
            retVal = NextStep(dir, state, m_Content);
        }
        else if ( dir == 'D') {
            m_lastDir = 'D';
            retVal = NextStep(dir, state, m_Content);
        }
        else
            retVal = NextStep(m_lastDir, state, m_Content);

        if (m_roundsLeftStunned > 0)
            m_roundsLeftStunned--;
        m_speedIterator = 0;
        return retVal;
    }
    else {
        m_speedIterator++;
        return 'D';
    }
}

char CGhost::NextStep(const char &dir, const char & state, std::map <std::pair<size_t,size_t>, char > & m_Content )
{
    char behind;
    switch ( dir ) {
        case 'L':
            m_reverseDir = 'r';
            switch ( m_Content.at(std::make_pair(m_Y,m_X - 1 ) )) {
                case '.':
                case ' ':
                case 'o':
                case 'B':
                    m_Content[std::make_pair(m_Y,m_X)] = oldPos;
                    m_X--;
                    oldPos = m_Content[std::make_pair(m_Y,m_X)];
                    m_Content[std::make_pair(m_Y,m_X)] = state;
                    break;
                case 'T':
                    m_Content[std::make_pair(m_Y,m_X)] = oldPos;
                    m_X = m_map_X-3;
                    oldPos = m_Content[std::make_pair(m_Y,m_X)];
                    m_Content[std::make_pair(m_Y,m_X)] = state;
                    break;
                case 'C':
                    if (state == m_spooked) {
                        m_Content[std::make_pair(m_Y, m_X)] = oldPos;
                        DeActivate();
                        AddWait();
                        RLStoZero();
                    }
                    else {
                        m_Content[std::make_pair(m_Y, m_X)] = oldPos;
                        m_X--;
                        oldPos = ' ';
                        m_Content[std::make_pair(m_Y, m_X)] = state;
                        return 'l';
                    }
                    break;
                case 'Q':
                case 'W':
                case 'R':
                case 'P':
                case 'q':
                case 'w':
                case 'r':
                case 'p':
                    behind= m_Content.at(std::make_pair(m_Y,m_X+1 ) );
                    if ( behind == ' ' || behind == '.' || behind == 'B' || behind == 'o' ) {
                        m_Content[std::make_pair(m_Y, m_X)] = oldPos;
                        m_X++;
                        oldPos = m_Content[std::make_pair(m_Y, m_X)];
                        m_Content[std::make_pair(m_Y, m_X)] = state;
                        m_reverseDir = 'l';
                        break;
                    }
                    break;
                default:
                    m_Content[std::make_pair(m_Y,m_X)] = state;
                    break;
            }
            break;
        case 'R':
            m_reverseDir = 'l';
            switch ( m_Content.at(std::make_pair(m_Y,m_X + 1 ) )) {
                case '.':
                case ' ':
                case 'o':
                case 'B':
                    m_Content[std::make_pair(m_Y,m_X)] = oldPos;
                    m_X++;
                    oldPos = m_Content[std::make_pair(m_Y,m_X)];
                    m_Content[std::make_pair(m_Y,m_X)] = state ;
                    break;
                case 'T':
                    m_Content[std::make_pair(m_Y,m_X)] = oldPos;
                    m_X = 2;
                    oldPos = m_Content[std::make_pair(m_Y,m_X)];
                    m_Content[std::make_pair(m_Y,m_X)] = state;
                    break;
                case 'C':
                    if (state == m_spooked) {
                        m_Content[std::make_pair(m_Y, m_X)] = oldPos;
                        DeActivate();
                        AddWait();
                        RLStoZero();
                    }
                    else {
                        m_Content[std::make_pair(m_Y, m_X)] = oldPos;
                        m_X++;
                        oldPos = ' ';
                        m_Content[std::make_pair(m_Y, m_X)] = state;
                        return 'l';
                    }
                    break;
                case 'Q':
                case 'W':
                case 'R':
                case 'P':
                case 'q':
                case 'w':
                case 'r':
                case 'p':
                    behind= m_Content.at(std::make_pair(m_Y,m_X-1 ) );
                    if ( behind == ' ' || behind == '.' || behind == 'B' || behind == 'o' ) {
                        m_Content[std::make_pair(m_Y, m_X)] = oldPos;
                        m_X--;
                        oldPos = m_Content[std::make_pair(m_Y, m_X)];
                        m_Content[std::make_pair(m_Y, m_X)] = state;
                        m_reverseDir = 'r';
                        break;
                    }
                    break;
                default:
                    m_Content[std::make_pair(m_Y,m_X)] = state;
                    break;
            }
            break;
        case 'U':
            m_reverseDir = 'd';
            switch ( m_Content.at(std::make_pair(m_Y - 1 ,m_X ) )) {
                case '.':
                case ' ':
                case 'o':
                case 'B':
                    m_Content[std::make_pair(m_Y,m_X)] = oldPos;
                    m_Y--;
                    oldPos = m_Content[std::make_pair(m_Y,m_X)];
                    m_Content[std::make_pair(m_Y,m_X)] = state;
                    break;
                case 'T':
                    m_Content[std::make_pair(m_Y,m_X)] = oldPos;
                    m_Y = m_map_Y-3;
                    oldPos = m_Content[std::make_pair(m_Y,m_X)];
                    m_Content[std::make_pair(m_Y,m_X)] = state;
                    break;
                case 'C':
                    if (state == m_spooked) {
                        m_Content[std::make_pair(m_Y, m_X)] = oldPos;
                        DeActivate();
                        AddWait();
                        RLStoZero();
                    }
                    else {
                        m_Content[std::make_pair(m_Y, m_X)] = oldPos;
                        m_Y--;
                        oldPos = ' ';
                        m_Content[std::make_pair(m_Y, m_X)] = state;
                        return 'l';
                    }
                    break;
                case 'Q':
                case 'W':
                case 'R':
                case 'P':
                case 'q':
                case 'w':
                case 'r':
                case 'p':
                    behind= m_Content.at(std::make_pair(m_Y+1,m_X ) );
                    if ( behind == ' ' || behind == '.' || behind == 'B' || behind == 'o' ) {
                        m_Content[std::make_pair(m_Y, m_X)] = oldPos;
                        m_Y++;
                        oldPos = m_Content[std::make_pair(m_Y, m_X)];
                        m_Content[std::make_pair(m_Y, m_X)] = state;
                        m_reverseDir = 'u';
                        break;
                    }
                    break;
                default:
                    m_Content[std::make_pair(m_Y,m_X)] = state;
                    break;
            }
            break;
        case 'D':
            m_reverseDir = 'u';
            switch ( m_Content.at(std::make_pair(m_Y + 1 ,m_X ) )) {
                case '.':
                case ' ':
                case 'o':
                case 'B':
                    m_Content[std::make_pair(m_Y,m_X)] = oldPos;
                    m_Y++;
                    oldPos = m_Content[std::make_pair(m_Y,m_X)];
                    m_Content[std::make_pair(m_Y,m_X)] = state;
                    break;
                case 'T':
                    m_Content[std::make_pair(m_Y,m_X)] = oldPos;
                    m_Y = 2;
                    oldPos = m_Content[std::make_pair(m_Y,m_X)];
                    m_Content[std::make_pair(m_Y,m_X)] = state;
                    break;
                case 'C':
                    if (state == m_spooked) {
                        m_Content[std::make_pair(m_Y, m_X)] = oldPos;
                        DeActivate();
                        AddWait();
                        RLStoZero();
                    }
                    else {
                        m_Content[std::make_pair(m_Y, m_X)] = oldPos;
                        m_Y++;
                        oldPos = ' ';
                        m_Content[std::make_pair(m_Y, m_X)] = state;
                        return 'l';
                    }
                    break;
                case 'Q':
                case 'W':
                case 'R':
                case 'P':
                case 'q':
                case 'w':
                case 'r':
                case 'p':
                    behind= m_Content.at(std::make_pair(m_Y-1,m_X ) );
                    if ( behind == ' ' || behind == '.' || behind == 'B' || behind == 'o' ) {
                        m_Content[std::make_pair(m_Y, m_X)] = oldPos;
                        m_Y--;
                        oldPos = m_Content[std::make_pair(m_Y, m_X)];
                        m_Content[std::make_pair(m_Y, m_X)] = state;
                        m_reverseDir = 'd';
                        break;
                    }
                    break;
                default:
                    m_Content[std::make_pair(m_Y,m_X)] = state;
                    break;
            }
            break;
        default:
            m_Content[std::make_pair(m_Y,m_X)] = state;
            break;
    }
    return 'D';
}

char CGhost::GetSkin() const
{
    if ( m_roundsLeftStunned != 0)
        return m_spooked;
    else
        return m_normal;
}

void CGhost::AssignNewSpace(const char & newSpace, const size_t & y, const size_t & x)
{
    oldPos = newSpace;
    m_X = x;
    m_Y = y;
}

bool CGhost::GetState() const
{ return m_active; }

void CGhost::Activate()
{ m_active = true; }

void CGhost::DeActivate()
{ m_active = false; }

size_t CGhost::GetWait() const
{ return m_waitTillSpawn; }

void CGhost::SubtWait()
{ m_waitTillSpawn--; }

void CGhost::RLStoZero()
{ m_roundsLeftStunned=0; }

char CGhost::ScatterChase(const int & first, const int & second, const int & third, const int & fourth,
                          std::map<std::pair<size_t, size_t>, char> &m_Content, const size_t & TargetX,
                          const size_t & TargetY )
{
    char state,next;
    int holder = 214748364;
    state = GetSkin();

    size_t amtOfDir=0;
    bool L = false, R = false ,U = false, D = false;
    char right = m_Content.at(std::make_pair(m_Y,m_X+1 ));
    char left  = m_Content.at(std::make_pair(m_Y,m_X-1 ));
    char down  = m_Content.at(std::make_pair(m_Y+1,m_X ));
    char up    = m_Content.at(std::make_pair(m_Y-1,m_X ));


    if ( (right != 'X' && right != '=') || right == 'C' )
    { amtOfDir++; R = true; }
    if (( left != 'X' && left != '=') || left == 'C')
    { amtOfDir++; L = true; }
    if (( down != 'X' && down != '=') || down == 'C')
    { amtOfDir++; D = true; }
    if (( up != 'X' && up != '=') || up =='C')
    { amtOfDir++; U = true; }

    if ( amtOfDir == 1){
        if (R)
            return NextStep('R', state, m_Content);
        else if (L)
            return NextStep('L', state, m_Content);
        else if (U)
            return NextStep('U', state, m_Content);
        else if (D)
            return NextStep('D', state, m_Content);

    }
    if ( amtOfDir == 2){
        if (m_reverseDir == 'l' && R )
            return NextStep('R', state, m_Content);
        else if (m_reverseDir == 'r' && L )
            return NextStep('L', state, m_Content);
        else if (m_reverseDir == 'd' && U )
            return NextStep('U', state, m_Content);
        else if (m_reverseDir == 'u' && D )
            return NextStep('D', state, m_Content);

    }
    if ( amtOfDir > 1){
        Direction(R,L,U,D,first , TargetX, TargetY,next,holder);
        Direction(R,L,U,D,second, TargetX, TargetY,next,holder);
        Direction(R,L,U,D,third , TargetX, TargetY,next,holder);
        Direction(R,L,U,D,fourth, TargetX, TargetY,next,holder);
        return NextStep(next,state,m_Content);
    }
    return NextStep('U',state,m_Content);
}

int CGhost::Convertor(const size_t &g_x, const size_t &g_y, const size_t &t_x, const size_t &t_y)
{
    int convertVal1,convertVal2, temp, temp2 ;
    convertVal1 = static_cast<int>(g_x);
    convertVal2 = static_cast<int>(t_x);
    temp2 = convertVal1 - convertVal2;
    if (temp2 < 0)
        temp2 = temp2 * (-1);
    convertVal1 = static_cast<int>(g_y);
    convertVal2 = static_cast<int>(t_y);
    temp = convertVal1 - convertVal2;
    if (temp < 0)
        temp = temp * (-1);
    return (temp2 + temp);
}

void CGhost::Direction(const bool & R,const bool & L, const bool & U,const bool & D, const int & dir, const size_t &t_x, const size_t &t_y, char & next, int & holder)
{
    int temp2;
    if ( (dir == 1 ) && R && (m_reverseDir != 'r') ){
        temp2 = Convertor(m_X+1,m_Y,t_x,t_y);
        if ( temp2 < holder ) {
            holder = temp2;
            next = 'R';
        }
    }
    else if((dir == 2 ) && L && (m_reverseDir != 'l') ){
        temp2=Convertor(m_X-1,m_Y,t_x,t_y);
        if ( temp2 < holder ) {
            holder = temp2;
            next = 'L';
        }
    }
    else if ((dir == 3 ) && U && (m_reverseDir != 'u') ){
        temp2= Convertor(m_X,m_Y-1,t_x,t_y);
        if ( temp2 < holder ) {
            holder = temp2;
            next = 'U';
        }
    }
    else if((dir == 4 ) && D && (m_reverseDir != 'd') ) {
        temp2 = Convertor(m_X,m_Y+1,t_x,t_y);
        if (temp2 < holder) {
            holder = temp2;
            next = 'D';
        }
    }
}

void CGhost::ChangeDir()
{
    if (m_reverseDir == 'r')
        m_reverseDir = 'l';
    else if ( m_reverseDir == 'l')
        m_reverseDir = 'r';
    else if ( m_reverseDir == 'd')
        m_reverseDir = 'u';
    else
        m_reverseDir = 'd';
}


void CGhost::DeSpawn(const size_t & adder, std::map<std::pair<size_t, size_t>, char> & m_Content)
{
    m_active = false;
    m_Content[std::make_pair(m_Y,m_X)] = oldPos;
    m_waitTillSpawn = adder;
    m_roundsLeftStunned = 0;
}

char CGhost::GetOldPos() const
{ return oldPos; }

void CGhost::AddCustomWait(const size_t & adder)
{
    m_waitTillSpawn = adder;
}


