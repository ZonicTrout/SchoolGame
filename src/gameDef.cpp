//
// GameDef.cpp
//
#include "../include/gameDef.hpp"
#include <SDL2/SDL_surface.h>

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
    .surfaceSize = Game::windowSize,
    .walkAble = { {.x=0, .y=150}, 
        {.x=517, .y=720} }
};

Utils::Image Game::Background {
    .imagePath = "resources/BackgroundFullBig.png",
};

Utils::Image Game::Character {
    .imagePath = "resources/BrianBigBlue.png"
};

Utils::Image::~Image() {
    if ( imageSurface != NULL ) {
        SDL_FreeSurface(imageSurface);
    }
    if ( window != NULL ) {
        SDL_DestroyWindow(window);
    }
}

::Character Game::Player( &Game::Character, &Game::MainScreen,
        {Game::windowSize.width / 2 ,Game::windowSize.height / 2}, 
        20);

Utils::Coordinates Character::getCenterOfSprite(void) {
    Utils::Coordinates center{0,0};
    Utils::Size halfSize { 
        .height = spriteInfo->surfaceSize.height/2,
        .width = spriteInfo->surfaceSize.height/2 
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

void Character::syncBottomCoords() {
    bottomCoords = { coords.x+mainWindow->surfaceSize.width,
        coords.y+mainWindow->surfaceSize.height };
}

void Character::syncTopCoords() {
    coords = { bottomCoords.x-mainWindow->surfaceSize.width,
        bottomCoords.y-mainWindow->surfaceSize.height };
}

void Character::MoveSpriteInBounds() {
    // Check if Character X Coord is less than the walkable minimum, and if so sets it
    // to the minimum
    
    // TODO 
    // There is a bug when X is changed and Y is not working properly
    
    if ( coords.x <= mainWindow->walkAble.topLeftCoords.x)  {
        coords.x = mainWindow->walkAble.topLeftCoords.x;
    }
    // Check if Character Y Coord is less than the walkable minimum, and if so sets it
    // to the minimum
    if ( coords.y <= mainWindow->walkAble.topLeftCoords.y)  {
        coords.y = mainWindow->walkAble.topLeftCoords.y;
    }
    syncBottomCoords();

    // Check if Character X Coord is greater than the maximum walkable X, and if so
    // sets it to the max
    if ( bottomCoords.x >= mainWindow->walkAble.bottomRightCoords.x ) {
        bottomCoords.x = mainWindow->walkAble.bottomRightCoords.x;
    }

    // Check if Character X Coord is greater than the maximum walkable X, and if so
    // sets it to the max
    if ( coords.y >= mainWindow->walkAble.bottomRightCoords.y ) {
        coords.y = mainWindow->walkAble.bottomRightCoords.y;
    }
    syncTopCoords();
}

void Character::MoveSprite(int increaseInX, int increaseInY) {
    // Check if both x and y are inside walkable Rectangle, and if not set it to
    // the max or minimum of the Rectangle
    coords.x += increaseInX;
    coords.y += increaseInY;
    
    syncBottomCoords();
    MoveSpriteInBounds();
}

void Character::drawSprite ( Utils::Image* MainWindowImage) {
    // I used this the Size params because I got seg faults from doing
    // surface->h
    spriteRect = {coords.x, coords.y, spriteInfo->surfaceSize.width,
        spriteInfo->surfaceSize.height};
    if ( spriteInfo->imageSurface == NULL ) {
        std::string exitMsg = "Forgot to set Character Surface";
        Utils::exitProgram(&exitMsg);
    }

    SDL_BlitSurface(spriteInfo->imageSurface, NULL, MainWindowImage->imageSurface,
            &spriteRect);
}

::Character::Character ( Utils::Image* characterInfo, 
        Utils::Image* mainWindowParam, Utils::Coordinates characterCoords,
        int movePixels) {
    spriteInfo = characterInfo;
    mainWindow = mainWindowParam;
    coords = characterCoords;
    bottomCoords = { coords.x+spriteInfo->surfaceSize.width,
        coords.y+spriteInfo->surfaceSize.height };
    pixelsPerMove = movePixels;
    // I used this the Size params because I got seg faults from doing
    // surface->h
    spriteRect = {coords.x, coords.y, spriteInfo->surfaceSize.width,
        spriteInfo->surfaceSize.height};

    characterName = "Mable";
    std::cout << "Hello There, " << characterName << "!" << std::endl;
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

// TODO 
// Have this check if wasd keys were pressed down, and if so change Character
// coords
void Visual::CheckKeyDown (SDL_Event* currentEvent, Character* characterToMove ) {
    if ( currentEvent->type == SDL_KEYDOWN ) {
        //Maye add variable to see that last pressed key?
        SDL_Keycode currentKey = currentEvent->key.keysym.sym;

        switch (currentKey) {
            case ( SDLK_w):
                // Do move logic for each case
                characterToMove->MoveSprite(0, -10);
                break;
            case (SDLK_a):
                characterToMove->MoveSprite(-10, 0);
                break;
            case (SDLK_s):
                characterToMove->MoveSprite(0, 10);
                break;
            case (SDLK_d):
                characterToMove->MoveSprite(10, 0);
                break;
            default:
                PASS;
                break;
        }
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
    ImageInfo->surfaceSize = { ImageInfo->imageSurface->h, ImageInfo->imageSurface->w }; 
    if (isBackground) {
        //Visual::StretchImage(&ImageInfo, &MainWindow->surfaceSize);
        std::cout << "T'is a background" << std::endl;
    }

    if (ImageInfo->imageSurface == NULL) {
        std::string exitMsg{"Surface could not be initialized"};
        Utils::exitProgram(&exitMsg);
    }
}
    
    void Visual::CloseProgram( void ) {
    // Removed because already done in Utils::Image structure
    //SDL_FreeSurface( *backgroundPicturePtr );
    //SDL_DestroyWindow( *mainWindowPtr );

    // Calls Destructors for Image Structures
    Game::MainScreen.~Image();
    Game::Background.~Image();
    Game::Character.~Image();

    SDL_Quit(); 
}


