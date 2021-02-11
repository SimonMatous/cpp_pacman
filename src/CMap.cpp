/*
 * @author Šimon Matouš (matousi1)
 * on 20.05.2020
 */

#include "CMap.h"

void   CMap::PrintMap () const
{

    for (size_t height = 0 ; height < m_height; height++){
        for (size_t width = 0 ; width < m_width ; width++){
            std::cout << m_Content.at(std::make_pair(height, width));
        }
        std::cout << std::endl;
    }
}

CMap::CMap()
{
    std::string mapName;
    std::cout << std::endl << "              PACMAN              " << std::endl << std::endl;
    std::cout << std::endl << "   Load classic or custom map?    "<< std::endl << "(  classic  /  [filename]  )" << std::endl;
    while ( true ){
        std::cin >> mapName;
        if ( mapName == "exit")
            exit(0);
        LoadMap(mapName);
        if ( loadingFailed == true )
            loadingFailed = false;
        else {
            MakeFrame();
            break;
        }
    }
    system("clear");
}

bool CMap::CheckChar(const char & pendingChar) const
{
    return pendingChar == 'X' || pendingChar == '.' || pendingChar == 'o' || pendingChar == ' ' || pendingChar == 'T' ||
           pendingChar == 'B' || pendingChar == '=' || pendingChar == 'C' || pendingChar == 'W' || pendingChar == 'Q' ||
           pendingChar == 'R' || pendingChar == 'P';
}

void CMap::LoadMap(const std::string & mapName)
{
    m_BonusSLX = 0;
    std::ifstream inFile;
    std::string fileName ="examples/"+ mapName + ".txt";
    inFile.open(fileName);
    if (inFile.is_open() == false){
        std::cout << "File with this name does not exist, please choose a different map." << std::endl;
        loadingFailed = true;
        return;
    }
    char pendingChar;
    bool PacFound = false, DoorFound = false, BonusFound = false;
    size_t height = 1, width = 1;
    /** loop checks if map contains any invalid signs and if it contains all the essential ones */
    while ( inFile ){
        inFile.get(pendingChar);
        if ( pendingChar != '\n'){
            if ( pendingChar == '.'|| pendingChar == 'o')
                m_collectibles++;
            else if ( pendingChar == 'C'){
                m_PacInLocX = width;
                m_PacInLocY = height;
                PacFound = true;
            }
            else if ( pendingChar == '='){
                m_DoorLocX = width;
                m_DoorLocY = height;
                DoorFound = true;
            }
            else if ( pendingChar == 'B'){
                m_BonusSLX = width;
                m_BonusSLY = height;
                m_collectibles++;
                pendingChar = '.';
                BonusFound = true;
            }

            if  (CheckChar(pendingChar) == false){
                std::cout << "char:"<<  "\n"  << pendingChar  << "M"  <<  "\n"<<  "\n";
                std::cout << "Map contains invalid signs, please choose a different map." << std::endl;
                loadingFailed = true;
                return;
            }
            m_Content.insert(std::make_pair(std::make_pair(height, width), pendingChar));
            width++;
        }
        else{
            if ( height == 1)
                m_width = width;
            if ( width != m_width && (inFile.eof() != true)){
                std::cout << "All lines in the map must be the same length, please choose a different map." << std::endl;
                loadingFailed = true;
                return;
            }
            height++;
            width = 1;
        }
        m_height = height-1;
    }
    bool SpawnFound = false;

    if (m_Content.at(std::make_pair(m_DoorLocY - 1, m_DoorLocX)) == '.' || m_Content.at(std::make_pair(m_DoorLocY - 1, m_DoorLocX)) == 'o') {
        m_SpawnLocX = m_DoorLocX;
        m_SpawnLocY = m_DoorLocY-1;
        SpawnFound = true;
    }
    else if (m_Content.at(std::make_pair(m_DoorLocY + 1, m_DoorLocX)) == '.' || m_Content.at(std::make_pair(m_DoorLocY + 1, m_DoorLocX)) == 'o' ) {
        m_SpawnLocX = m_DoorLocX;
        m_SpawnLocY = m_DoorLocY+1;
        SpawnFound = true;
    }
    else if (m_Content.at(std::make_pair(m_DoorLocY, m_DoorLocX - 1)) == '.' || m_Content.at(std::make_pair(m_DoorLocY, m_DoorLocX - 1)) == 'o' ) {
        m_SpawnLocX = m_DoorLocX-1;
        m_SpawnLocY = m_DoorLocY;
        SpawnFound = true;
    }
    else if (m_Content.at(std::make_pair(m_DoorLocY, m_DoorLocX + 1)) == '.' || m_Content.at(std::make_pair(m_DoorLocY, m_DoorLocX + 1)) == 'o' ) {
        m_SpawnLocX = m_DoorLocX+1;
        m_SpawnLocY = m_DoorLocY;
        SpawnFound = true;
    }

    if ( PacFound == false || DoorFound == false || BonusFound == false ){
        std::cout << "Essential signs missing, please choose a different map.(door / Pacman Spawn / bonus)" << std::endl;
        loadingFailed = true;
        return;
    }
    if ( SpawnFound == false ){
        std::cout << "Door is incorrectly located, please choose a different map." << std::endl;
        loadingFailed = true;
        return;
    }

}

void CMap::MakeFrame()
{
    for (size_t width = 0 ; width < m_width ; width++){
        m_Content.insert(std::make_pair(std::make_pair(0, width), 'X'));
        m_Content.insert(std::make_pair(std::make_pair(m_height, width), 'X'));
    }
    for (size_t height = 0 ; height < m_height; height++){
        m_Content.insert(std::make_pair(std::make_pair(height, 0), 'X'));
        m_Content.insert(std::make_pair(std::make_pair(height, m_width), 'X'));
    }
    m_Content.insert(std::make_pair(std::make_pair(m_height, m_width), 'X'));
    m_height++;
    m_width++;
}
size_t CMap::GetHeight () const
{
    return m_height;
}
size_t CMap::GetWidth () const
{
    return m_width;
}
size_t CMap::GetCollectibles() const
{
    return m_collectibles;
}
size_t CMap::GetPacInLocX()const
{
    return m_PacInLocX;
}
size_t CMap::GetPacInLocY()const
{
    return m_PacInLocY;
}
size_t CMap::GetDoorLocX() const
{
    return m_DoorLocX;
}
size_t CMap::GetDoorLocY() const
{
    return m_DoorLocY;
}
size_t CMap::GetSpawnLocX()const
{
    return m_SpawnLocX;
}
size_t CMap::GetSpawnLocY()const
{
    return m_SpawnLocY;
}
size_t CMap::GetBonusLocX()const
{
    return m_BonusSLX;
}
size_t CMap::GetBonusLocY()const
{
    return m_BonusSLY;
}