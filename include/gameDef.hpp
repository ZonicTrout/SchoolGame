// 
// GameDef.hpp
//

#include <iostream>
#include <unistd.h> 
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// I think I no longer need
//#include "SDL2_rotozoom.h"

#ifndef GAME_DEF_HPP
#define GAME_DEF_HPP

#define PASS /**/

namespace Utils {
    void exitProgram(std::string* exitMsg, int exitCode=0);
    std::string getFileExtention( std::string* fileName );
    
    struct Size{
        int height;
        int width;
    } ;
    struct RGB {
        int Red;
        int Green;
        int Blue;
    } ;
    struct Image {
        std::string imagePath;
        SDL_Surface* imageSurface{NULL};
        SDL_Window* window{NULL};
        Utils::Size surfaceSize{0, 0};
    };
}

namespace Game {
    extern Utils::Image MainScreen;
    extern Utils::Image Background;
    extern Utils::Image Character;

    extern std::string windowTitle;
    extern Utils::Size windowSize;
}

namespace Visual {
    // MUST have douboe pointer for passing pointers
    // The first "*" tells it what type to expect, the second tells it
    // that it is a pointer to the type it would expect
    void InitScreen(Utils::Image* ImageInfo, std::string* title, 
            Utils::Size* windowSize);
    void StretchImage( Utils::Image** ImageInfo, Utils::Size* newSize);
    void LoadImageSurface( Utils::Image* ImageInfo, bool isBackground=false,
           Utils::Image* MainWindow=NULL );
    void CheckKeyDown( SDL_Event* currentEvent );
    void CheckQuit( SDL_Event* currentEvent, bool* quit );
    void CloseProgram(SDL_Window** mainWindowPtr, 
            SDL_Surface** backgroundPicturePtr);
}



#endif
