/*
 * @author Šimon Matouš (matousi1)
 * on 20.05.2020
 */

#pragma once

#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <utility>
#include <map>


class CMap
{
public:
    /** constructor takes care of the whole process of loading a map */
    CMap                  ()                                     ;
    /** @returns true if loaded character is correct
     *  @returns false if the character is incorrcet */
    bool   CheckChar      (const char & pendingChar)        const;
    /** checks if the whole map (text file) is correct */
    void   LoadMap        (const std::string & fileName)         ;
    void   PrintMap       ()                                const;
    /**  generates walls around the map to have less restrictions in map making */
    void   MakeFrame      ()                                     ;
    size_t GetHeight      ()                                const;
    size_t GetWidth       ()                                const;
    size_t GetCollectibles()                                const;
    size_t GetPacInLocX   ()                                const;
    size_t GetPacInLocY   ()                                const;
    size_t GetDoorLocX    ()                                const;
    size_t GetDoorLocY    ()                                const;
    size_t GetSpawnLocX   ()                                const;
    size_t GetSpawnLocY   ()                                const;
    size_t GetBonusLocX   ()                                const;
    size_t GetBonusLocY   ()                                const;
    std::map <std::pair<size_t,size_t>, char > m_Content         ;
private:
    size_t m_height              ;
    size_t m_width               ;
    size_t m_collectibles = 0    ;
    size_t m_PacInLocX           ;
    size_t m_PacInLocY           ;
    size_t m_DoorLocX            ;
    size_t m_DoorLocY            ;
    size_t m_SpawnLocX           ;
    size_t m_SpawnLocY           ;
    size_t m_BonusSLX            ;
    size_t m_BonusSLY            ;
    bool   loadingFailed  = false;
};