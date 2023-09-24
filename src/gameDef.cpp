//
// GameDef.cpp
//
#include "../include/gameDef.hpp"

void Utils::exitProgram(std::string* exitMsg, int exitCode) {
    std::cout << *exitMsg << " : "  << SDL_GetError() << std::endl; 
    exit(exitCode);
}


std::string Game::windowTitle = "Brian's Hunt";

Utils::Size Game::windowSize = {
    .height = 720,
    .width = 517 
};

Utils::Image Game::MainScreen {
    .surfaceSize = Game::windowSize
};

Utils::Image Game::Background {
    .imagePath = "resources/BackgroundBig.png"
};

Utils::Image Game::Character {
    .imagePath = "resources/Brian.png"
};

Utils::Coordinates Character::getCenterOfSprite(void) {
    Utils::Coordinates center{0,0};
    Utils::Size halfSize { 
        .height = spriteInfo.surfaceSize.height/2,
        .width = spriteInfo.surfaceSize.height/2 
    };
    center = {
        // Yes the swap between them is intentional. Remeber that the default
        // grid in SDL2 has a point of origin at the top left of the screen 
        // and as y increases, it goes down. X does the same as usual.
        .x = ( halfSize.width + coords.x ),
        .y = ( coords.y - halfSize.height ) 
    };
    return center;
}

Utils::Circle Character::getCollisionCircle() {
    Utils::Circle collisionCircle { {0, 0}, 0 };
    Utils::Coordinates center = getCenterOfSprite();
    collisionCircle = { 
        .centerPoint = center,
        // Takes the avergae of the x and y, and divideds it by 2
        .radius = ( (coords.x + coords.y) / 2 ) / 2
    };
    return collisionCircle;
}

void Character::MoveSprite(int increaseInX, int increaseInY) {
    coords.x += increaseInX;
    coords.y += increaseInY;
}

Visual::ScreenCoordPlane::ScreenCoordPlane ( Utils::Image* mainWindow ) {
    Utils::Size windowSize;
    SDL_GetWindowSize( mainWindow->window, &windowSize.width, 
            &windowSize.height);
    // X is at 0 because x works as usual and 
    logicalOrigin = {0, windowSize.height};
}

void Visual::InitScreen( Utils::Image* ImageInfo, 
        std::string* title, Utils::Size* windowSize)
{
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        std::string exitMsg{"Video Could not be initialized"};
        Utils::exitProgram(&exitMsg, 0);
    }
    ImageInfo->window = SDL_CreateWindow(title->c_str(), 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            windowSize->width, windowSize->height, SDL_WINDOW_SHOWN );

    if (ImageInfo->window== NULL) {
        std::string exitMsg{"Window could not be initialized"};
        Utils::exitProgram(&exitMsg);
    }
    ImageInfo->imageSurface = SDL_GetWindowSurface(
            ImageInfo->window);
}

void Visual::CheckQuit ( SDL_Event* currentEvent, bool* quit ) {
    if ( currentEvent->type == SDL_QUIT ) {
        *quit = true;
    }
}

void Visual::CheckKeyDown (SDL_Event* currentEvent ) {
    if ( currentEvent->type == SDL_KEYDOWN ) {
        std::cout << currentEvent->key.keysym.sym << std::endl; 
    }
    return;
}

// Decided to not use, easier to just scale the image in gimp
/*
void Visual::StretchImage(Utils::Image** ImageInfo, 
        Utils::Size* newSize) {
    SDL_Surface* bufferSurface{NULL};

    if ((*ImageInfo)->imageSurface == NULL) {
        std::string exitMsg{"Could not load image to be stretched"};
        Utils::exitProgram(&exitMsg);
    }
    // There is a height and width param aswell
    bufferSurface = zoomSurface( (*ImageInfo)->imageSurface,
           500, 500, 0 );

    if ( bufferSurface == NULL ) {
        std::string exitMsg{ "Could not stretch image" };
        Utils::exitProgram(&exitMsg);
    }
}
*/

// Include Surface for size
void Visual::LoadImageSurface( Utils::Image* ImageInfo, 
        bool isBackground, Utils::Image* MainWindow) {
    SDL_Surface* bufferSurface = NULL;
    bufferSurface = IMG_Load(ImageInfo->imagePath.c_str());
    if (bufferSurface == NULL) {
        std::string exitMsg{"Image could not be initialized"};
        Utils::exitProgram(&exitMsg);
    }
    
    ImageInfo->imageSurface = bufferSurface;
    
    if (isBackground) {
        //Visual::StretchImage(&ImageInfo, &MainWindow->surfaceSize);
        std::cout << "T'is a background" << std::endl;
    }

    if (ImageInfo->imageSurface == NULL) {
        std::string exitMsg{"Surface could not be initialized"};
        Utils::exitProgram(&exitMsg);
    }
}
    
    void Visual::CloseProgram(SDL_Window** mainWindowPtr, 
            SDL_Surface** backgroundPicturePtr) {
    SDL_FreeSurface( *backgroundPicturePtr );
    SDL_DestroyWindow( *mainWindowPtr );
    SDL_Quit(); 
}


