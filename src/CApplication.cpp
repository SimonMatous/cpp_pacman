/*
 * @author Šimon Matouš (matousi1)
 * on 20.05.2020
 */




#include "CApplication.h"

CApplication::CApplication()
{
    system("clear");
    while ( true ){
        RegisterInput();
        system("clear");
        RunApplication();
        system("clear");
        if ( m_playAgain == "no" )
            break;
        system("clear");
    }
}
void CApplication::RegisterInput()
{
    std::string config;
    bool loadingFailed = true;
    std::cout << std::endl << "              PACMAN              " << std::endl << std::endl;
    std::cout << "select difficulity: " << std::endl;
    std::cout << "  easy" << std::endl << "  medium" << std::endl << "  hard" << std::endl << std::endl << "  or choose a custom difficulity file" << std::endl << std::endl;
    while( true ){
        /** timer = 0 - whatever
         *  fruit = 1 - 10
         *  diff  = 1 - 3
         *  speed = 0 - whatever */
        std::cin >> config;
        if ( config == "exit")
            exit(0);
        /** easy/medium/hard difficulties are not files so that the user couldn't alter them
         *  the user can add his own custom config folder */
        if ( config == "easy"){
            m_timer = 1500;
            m_fruit = 8;
            m_diff  = 1;
            m_speed = 2;
            break;
        }
        else if ( config == "medium"){
            m_timer = 800;
            m_fruit = 7;
            m_diff  = 2;
            m_speed = 1;
            break;
        }
        else if ( config == "hard"){
            m_timer = 500;
            m_fruit = 5;
            m_diff  = 3;
            m_speed = 0;
            break;
        }
        LoadConfig(config,loadingFailed);

        if ( loadingFailed == false )
            break;

        std::cout << "Values in config file have to be:" << std::endl << "timer = 0 - whatever" << std::endl << "fruit = 1 - 10"
                                                         << std::endl << "diff  = 1 - 3 " << std::endl << "speed = 0 - whatever" << std::endl;
    }
    system("clear");


}

void CApplication::RunApplication() {
    CSession session = CSession(m_diff,m_timer,m_fruit, m_speed);
    std::cout << "Play again? " << std::endl << "   yes  " << std::endl << "   no  " << std::endl;
    while (true) {
        std::cin >> m_playAgain;
        if ((m_playAgain == "yes") || (m_playAgain == "no"))
            break;
        std::cout << "Please enter yes or no" << std::endl;
    }
}

void CApplication::LoadConfig(const std::string & config, bool & loadingFailed)
{
  int timer = -1,  fruit = -1, diff = -1,  speed = -1 ;
    std::ifstream inFile;
    std::string fileName ="src/diff/"+ config + ".txt";
    inFile.open(fileName);

    if (inFile.is_open() == false){
        std::cout << "File with this name does not exist, please choose a different one." << std::endl;
        return;
    }
    inFile >> timer >> fruit >> diff >> speed;

    if ( timer < 0){
        std::cout << "File has a wrong format or value/s." << std::endl;
        std::cout << "timer (has to be) > 0" <<std::endl;
        return;
    }
    if ( fruit < 1 || fruit > 10 ){
        std::cout << "File has a wrong format or value/s." << std::endl;
        std::cout << "1 > fruit (has to be) < 10" <<std::endl;

        return;
    }
    if ( diff < 1 || diff > 3){
        std::cout << "File has a wrong format or value/s." << std::endl;
        std::cout << "1 > diff (has to be) < 3" <<std::endl;

        return;
    }
    if ( speed < 0 ){
        std::cout << "File has a wrong format or value/s." << std::endl;
        std::cout << "speed (has to be) > 0" <<std::endl;

        return;
    }
    m_timer = timer;
    m_fruit = fruit;
    m_diff  = diff;
    m_speed = speed;
    loadingFailed = false;
    return;


}
