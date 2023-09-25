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

    struct Coordinates {
        int x;
        int y;
    };

    // used for collision detection
    struct Circle {
        Utils::Coordinates centerPoint{0, 0};
        int radius{0};
    };
    struct Rectangle {
        Utils::Coordinates topLeftCoords;
        Utils::Coordinates bottomRightCoords;
    };
    
    struct Image {
        std::string imagePath;
        SDL_Surface* imageSurface{NULL};
        SDL_Window* window{NULL};
        Utils::Size surfaceSize{0, 0};
        Utils::Rectangle walkAble{  {0, 0}, {0, 0} };
       
        //TODO 
        // Need to fix first
        //~Image();
    };
}

class Character {
private:
    int pixelsPerMove{0};
protected:
public: Utils::Image* spriteInfo;
    Utils::Image* mainWindow;
    std::string characterName;
    SDL_Rect spriteRect;
    
    void MoveSpriteInTopLeftBounds();
    void MoveSpriteInBotomRightBounds();
    void MoveSpriteInBounds();
public:
   Utils::Coordinates coords{0, 0};
   Utils::Coordinates bottomCoords{0, 0};
   Utils::Coordinates getCenterOfSprite();
   Utils::Circle getCollisionCircle();
   
   void syncBottomCoords();
   void syncTopCoords();
   void drawSprite( Utils::Image* MainWindowImage);
   void MoveSprite(int increaseInX, int increaseInY);

   Character( Utils::Image* characterInfo, Utils::Image* mainWindowParam,
           Utils::Coordinates characterCoords = {0, 0}, 
           int movePixels = 20);
};

namespace Visual {
    // MUST have douboe pointer for passing pointers
    // The first "*" tells it what type to expect, the second tells it
    // that it is a pointer to the type it would expect
    void InitScreen(Utils::Image* ImageInfo, std::string* title, 
            Utils::Size* windowSize);
    void StretchImage( Utils::Image** ImageInfo, Utils::Size* newSize);
    void LoadImageSurface( Utils::Image* ImageInfo, bool isBackground=false );
    void CheckKeyDown( SDL_Event* currentEvent, Character* characterToMove );
    void CheckQuit( SDL_Event* currentEvent, bool* quit );
    void CloseProgram( void );

    struct ScreenCoordPlane {
        // The coordinate system will be like a Sector 1 coordinate plane,
        // with the point of origin being in the bottom left of the window
        Utils::Coordinates logicalOrigin{0, 0};
        ScreenCoordPlane( Utils::Image* mainWindow );

    };
}

namespace Game {
    // TODO convert the followinf to pointers so it is easier to free
    // them when Visual::CloseProgram() is called
    extern ::Utils::Image MainScreen;
    extern ::Utils::Image Background;

    extern ::std::string windowTitle;
    extern ::Utils::Size windowSize;

    extern ::Utils::Image Character;
    extern ::Character Player; 
}

#endif
