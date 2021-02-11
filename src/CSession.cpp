/*
 * @author Šimon Matouš (matousi1)
 * on 20.05.2020
 */


#include "CSession.h"





void CSession::RestoreKeyboardBlocking(struct termios *initial_settings)
    /** SOURCE: https://gist.github.com/whyrusleeping/3983293 */
{
    tcsetattr(0, TCSANOW, initial_settings);
}

char CSession::GetcharAlt()
    /** SOURCE: https://gist.github.com/whyrusleeping/3983293 */
{
    char buff[2];
    int l = read(STDIN_FILENO,buff,1);
    if( l > 0 ) return buff[0];
    return ( EOF );
}

void CSession::SetKeyboardNonBlock(struct termios *initial_settings)
    /** SOURCE: https://gist.github.com/whyrusleeping/3983293 */
{

    struct termios new_settings;
    tcgetattr(0,initial_settings);

    new_settings = *initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 0;
    new_settings.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &new_settings);
}




CSession::CSession(const size_t & diff, const size_t & timer, const size_t & fruitTimer, const size_t & speed )
        :m_difficulity(diff) ,m_pac( CPacman(m_map.GetPacInLocX(), m_map.GetPacInLocY(),m_map.GetCollectibles(),
         m_map.GetWidth(),m_map.GetHeight()) ),m_lives(3), m_timer(timer),m_fruitTimer(fruitTimer), m_speed(speed)
{
    CreateGhosts(m_difficulity);
    char result;
    char PacMoving = 0;
    bool ending;
    bool vulnerable;
    bool fruitSpawned = false;
   while ( true ){
       PrintSession();

       vulnerable = false;
       result = 0;

       result = Turn(vulnerable,PacMoving);
       Vulnerable(vulnerable);

       if      ( result == 'q' )
           DeleteGhost(*m_Clyde);
       else if ( result == 'r' )
           DeleteGhost(*m_Blinky);
       else if ( result == 'w' )
           DeleteGhost(*m_Inky);
       else if ( result == 'p' )
           DeleteGhost(*m_Pinky);

       GhostManager(*m_Blinky, 10, result);
       GhostManager(*m_Clyde ,  9, result);
       GhostManager(*m_Inky  ,  8, result);
       GhostManager(*m_Pinky ,  7, result);

       FruitManager(fruitSpawned);

       ending = EndingManager(result,PacMoving);
       if ( ending == true )
           break;
       system("clear");
   }
}
char CSession::Turn(bool & vulnerable, char & PacMoving)
{
    char input;
    struct termios term_settings;
    SetKeyboardNonBlock(&term_settings);
    usleep(150000);
    input = GetcharAlt();
    RestoreKeyboardBlocking(&term_settings);
    if ( input == 27)
        exit(0);
    if  ( input == 97 || input == 65 || input == 100 || input == 68 || input == 119 || input == 87 || input == 115 || input == 83 ) {
        PacMoving = input;
        return PlayerMove(PacMoving, vulnerable);
    }
    else
        return PlayerMove(PacMoving,vulnerable);
}

void CSession::RespawnPac()
{
    if ( m_Blinky->GetState() == true )
        m_Blinky->DeSpawn(10,m_map.m_Content);
    else
        m_Blinky->AddCustomWait(10);
    if ( m_Clyde->GetState() == true )
        m_Clyde ->DeSpawn(40,m_map.m_Content);
    else
        m_Clyde->AddCustomWait(40);
    if ( m_Inky->GetState() == true )
        m_Inky->DeSpawn(70,m_map.m_Content);
    else
        m_Inky->AddCustomWait(70);
    if ( m_Pinky->GetState() == true )
        m_Pinky->DeSpawn(100,m_map.m_Content);
    else
        m_Pinky->AddCustomWait(100);
    m_pac.RespawnPac(m_map.m_Content);
}

void CSession::PrintSession() const
{
    std::cout << "Press [ESC] to exit" << std::endl;
    std::cout << std::endl << "              PACMAN              " << std::endl << std::endl;
    std::cout << " score : " << m_pac.GetScore() << std::endl;
    std::cout << " lives :";
    for (size_t i = 1 ; i <= m_lives ; i++)
        std::cout << " C";
    std::cout << std::endl << " time  : " << m_timer << std::endl;
    std::cout << std::endl;
    m_map.PrintMap();
    std::cout << " collectibles left: " << m_pac.GetColl() << std::endl;
}

void CSession::Won() const
{
    system("clear");
    PrintSession();
    std::cout << std::endl << "              VICTORY              " << std::endl;
}

void CSession::Lost() const
{
    system("clear");
    PrintSession();
    std::cout << std::endl << "              DEFEAT              " << std::endl;
}

void CSession::CreateGhosts(const size_t &diff)
{

    if (diff == 1 ){
       m_Clyde  = new COrangeGhostEasy (m_map.GetDoorLocX(), m_map.GetDoorLocY(), m_map.GetWidth(), m_map.GetHeight(), m_map.GetSpawnLocX(), m_map.GetSpawnLocY(),m_speed);
       m_Pinky  = new CPinkGhostEasy   (m_map.GetDoorLocX(), m_map.GetDoorLocY(), m_map.GetWidth(), m_map.GetHeight(), m_map.GetSpawnLocX(), m_map.GetSpawnLocY(),m_speed);
       m_Inky   = new CBlueGhostEasy   (m_map.GetDoorLocX(), m_map.GetDoorLocY(), m_map.GetWidth(), m_map.GetHeight(), m_map.GetSpawnLocX(), m_map.GetSpawnLocY(),m_speed);
       m_Blinky = new CRedGhostEasy    (m_map.GetDoorLocX(), m_map.GetDoorLocY(), m_map.GetWidth(), m_map.GetHeight(), m_map.GetSpawnLocX(), m_map.GetSpawnLocY(),m_speed);

    }
   else if ( diff == 2 ){
       m_Clyde  = new COrangeGhostMedium(m_map.GetDoorLocX(), m_map.GetDoorLocY(), m_map.GetWidth(), m_map.GetHeight(), m_map.GetSpawnLocX(), m_map.GetSpawnLocY(), m_speed);
       m_Pinky  = new CPinkGhostMedium  (m_map.GetDoorLocX(), m_map.GetDoorLocY(), m_map.GetWidth(), m_map.GetHeight(), m_map.GetSpawnLocX(), m_map.GetSpawnLocY(), m_speed);
       m_Inky   = new CBlueGhostMedium  (m_map.GetDoorLocX(), m_map.GetDoorLocY(), m_map.GetWidth(), m_map.GetHeight(), m_map.GetSpawnLocX(), m_map.GetSpawnLocY(), m_speed);
       m_Blinky = new CRedGhostMedium   (m_map.GetDoorLocX(), m_map.GetDoorLocY(), m_map.GetWidth(), m_map.GetHeight(), m_map.GetSpawnLocX(), m_map.GetSpawnLocY(), m_speed);
    }
   else {
        m_Clyde  = new COrangeGhostHard(m_map.GetDoorLocX(), m_map.GetDoorLocY(), m_map.GetWidth(), m_map.GetHeight(), m_map.GetSpawnLocX(), m_map.GetSpawnLocY(), m_speed);
        m_Pinky  = new CPinkGhostHard  (m_map.GetDoorLocX(), m_map.GetDoorLocY(), m_map.GetWidth(), m_map.GetHeight(), m_map.GetSpawnLocX(), m_map.GetSpawnLocY(), m_speed);
        m_Inky   = new CBlueGhostHard  (m_map.GetDoorLocX(), m_map.GetDoorLocY(), m_map.GetWidth(), m_map.GetHeight(), m_map.GetSpawnLocX(), m_map.GetSpawnLocY(), m_speed);
        m_Blinky = new CRedGhostHard   (m_map.GetDoorLocX(), m_map.GetDoorLocY(), m_map.GetWidth(), m_map.GetHeight(), m_map.GetSpawnLocX(), m_map.GetSpawnLocY(), m_speed);
   }
}

void CSession::SpawnGhosts(CGhost &ghost, std::map <std::pair<size_t,size_t>, char > & m_Content)
{
    char newSpace = m_Content.at(std::make_pair(m_map.GetSpawnLocY(),m_map.GetSpawnLocX() ));
    if ( newSpace == '.' || newSpace == 'o' || newSpace == ' ' ) {
        ghost.AssignNewSpace(newSpace,m_map.GetSpawnLocY(),m_map.GetSpawnLocX());
        m_Content[std::make_pair(m_map.GetSpawnLocY(), m_map.GetSpawnLocX())] = ghost.GetSkin();
        ghost.Activate();
    }
}

CSession::~CSession()
{
    delete m_Pinky;
    delete m_Inky;
    delete m_Clyde;
    delete m_Blinky;
}

void CSession::Vulnerable(const bool &vul)
{
    if ( vul == true ) {
        if (m_Clyde->GetState() == true)
            m_Clyde->Stun();
        if (m_Blinky->GetState() == true)
            m_Blinky->Stun();
        if (m_Pinky->GetState() == true)
            m_Pinky->Stun();
        if (m_Inky->GetState() == true)
            m_Inky->Stun();
    }
}

void CSession::GhostManager(CGhost & ghost, const size_t &amt, char & result )
{
    if ( ( ( m_map.GetCollectibles()/10) * amt ) > m_pac.GetColl() ) {
        if (ghost.GetState() == false && ghost.GetWait() == 0 )
            SpawnGhosts(ghost, m_map.m_Content );
        else if ( ghost.GetState() == true ) {
            if (ghost.Strategy(result, m_map.m_Content, m_pac.GetX(), m_pac.GetY()) == 'l')
                result = 'l';
        }
        else
            ghost.SubtWait();
    }
}

void CSession::DeleteGhost(CGhost & ghost)
{
    char pos = ghost.GetOldPos();
    if ( pos == '.'){
        m_pac.decColl();
        m_pac.incScore(10);
    }
    else if ( pos == 'o'){
        m_pac.decColl();
        m_pac.incScore(50);
    }
    else if ( pos == 'B')
        m_pac.incScore(100);

    ghost.DeActivate();
    ghost.AddWait();
    ghost.RLStoZero();
}

size_t CSession::PlayerMove(const char & PacM, bool & vulnerable) {
    size_t result = 0;
    if ( PacM == 97 || PacM == 65)
        result = m_pac.MoveLeft(m_map.m_Content, vulnerable);
    else if ( PacM == 100 || PacM == 68)
        result = m_pac.MoveRight(m_map.m_Content, vulnerable);
    else if ( PacM == 119 || PacM == 87)
        result = m_pac.MoveUp(m_map.m_Content, vulnerable);
    else if ( PacM == 115 || PacM == 83)
        result = m_pac.MoveDown(m_map.m_Content, vulnerable);
    return result;
}

void CSession::FruitManager(bool & fruitSpawned)
{
    if (  fruitSpawned == false && m_map.GetBonusLocX() != 0 &&
          (((m_map.GetCollectibles()/10) * m_fruitTimer ) > m_pac.GetColl() ) && m_map.m_Content.at(std::make_pair(m_map.GetBonusLocY(), m_map.GetBonusLocX())) == ' '){
        m_map.m_Content[std::make_pair(m_map.GetBonusLocY(), m_map.GetBonusLocX())] = 'B';
        fruitSpawned = true;
    }
}

bool CSession::EndingManager(const char & result, char & PacMoving)
{
    if ( result == 'l' ) {
        if ( m_lives == 1 ) {
            m_lives--;
            Lost();
            std::cout << " You ran out of lives." << std::endl;
            return true;
        }
        else{
            PacMoving = 0;
            m_lives--;
            RespawnPac();
        }
    }
    else if ( result == 'v') {
        Won();
        return true;
    }
    if ( m_timer == 0){
        Lost();
        std::cout << " You ran out of time." << std::endl;
        return true;
    }
    m_timer--;
    return false;
}

