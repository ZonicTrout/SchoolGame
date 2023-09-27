#ifndef INITIALIZE_HPP
#define INITIALIZE_HPP
#include "gameDef.hpp"

namespace Game {
    // TODO convert the followinf to pointers so it is easier to free
    // them when Visual::CloseProgram() is called
    extern Utils::Image MainScreen;
    extern Utils::Image Background;

    extern std::string windowTitle;
    extern Utils::Size windowSize;

    extern Utils::Image Character;
    extern ::Character Player; 

    extern Utils::Contributor MJ;
    extern Utils::Contributor Sylar;
}
#endif 
