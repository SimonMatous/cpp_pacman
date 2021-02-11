/*
 * @author Šimon Matouš (matousi1)
 * on 24.05.2020
 */
#pragma once

#include <map>
#include <memory>


class CGhost
{
public:
           CGhost        () = default                                                                                                ;
   virtual ~CGhost       () = default                                                                                                ;
    /** assigns values based on difficulty and color */
           CGhost        (const size_t & door_x , const size_t & door_y , const size_t & map_x  , const size_t & map_y  ,
                          const size_t & spawn_x, const size_t & spawn_y, const size_t & speed )                                     ;
    char   GetSkin       ()                                                                                                     const;
    char   GetOldPos     ()                                                                                                     const;
    bool   GetState      ()                                                                                                     const;
    size_t GetWait       ()                                                                                                     const;
    void   AssignNewSpace(const char & newSpace, const size_t & y, const size_t & x)                                                 ;
    void   RLStoZero     ()                                                                                                          ;
    void   Activate      ()                                                                                                          ;
    void   DeActivate    ()                                                                                                          ;
    /** turns ghost off after pacman dies */
    void   DeSpawn       (const size_t & adder, std::map<std::pair<size_t, size_t>, char> & m_Content)                               ;
    void   AddCustomWait (const size_t & adder)                                                                                      ;
    void   SubtWait      ()                                                                                                          ;
    /** based on dir parameter and the new space the ghost is stepping on
     *  @returns 'l' if Pacman is killed
     *  else @returns 'D' */
    char   NextStep      (const char &dir, const char & state, std::map <std::pair<size_t,size_t>, char > & m_Content )              ;
    /** ghosts (medium/hard) use it to navigate through the maze
     *  based on the first 4 parameters chooses which path he favours when they are the same length
     *  @returns the result of NextStep(...) method (= either 'l' or 'D' )*/
    char   ScatterChase  (const int & first, const int & second, const int & third, const int & fourth,
                          std::map <std::pair<size_t,size_t>, char > & m_Content, const size_t & TargetX, const size_t & TargetY)    ;
    /** converts values from size_t to int
     *  @returns the length between two coordinates */
    int    Convertor     (const size_t & g_x, const size_t & g_y, const size_t & t_x, const size_t & t_y)                            ;
    /** measures the length between two coordinates and compares it to the shortest one found and picks the shorter */
    void   Direction     (const bool & R,const bool & L, const bool & U,const bool & D,const int & dir,
                          const size_t & t_x, const size_t & t_y, char & next, int & holder)                                         ;
    void   ChangeDir     ()                                                                                                          ;
    virtual void Stun    () = 0                                                                                                      ;
    virtual void AddWait () = 0                                                                                                      ;
    /** @easy strategy will be the same for every ghost, and that is once they leave their base, they will strart moving the same direction Pacman does
     *  @medium strategy will contain classic ghost strategies based on each individual ghosts character (will contain Chase, scatter and frightened mode)
     *  Pacman won't be able to completely eliminate the ghosts
     *  @hard strategy will contain classic ghost strategies based on each individual ghosts character but will only cointain Chase mode
     *  @returns 'l' if Pacman is killed
     *  else @returns 'D' */
    virtual char Strategy(const char & dir, std::map <std::pair<size_t,size_t>, char > & m_Content,const size_t & x,const size_t & y);

protected:
    bool   m_active           ;
    char   m_normal           ;
    char   m_spooked          ;
    char   oldPos             ;
    char   m_reverseDir       ;
    size_t m_waitTillSpawn    ;
    size_t m_roundsLeftStunned;
    size_t m_door_X           ;
    size_t m_door_Y           ;
    size_t m_map_X            ;
    size_t m_map_Y            ;
    size_t m_X                ;
    size_t m_Y                ;
    size_t m_speed            ;
    size_t m_speedIterator    ;
private:
    size_t m_lastDir = 'L'    ;
};