//
// Main.cpp
//

#include "../include/gameDef.hpp"

int main( int argc, char* argv[] ) {
    for (int i=0; i<argc; i++) {
        std::cout << "Arg #" << argc << " is, '" << argv[i] << "' " 
                << std::endl; 
    }
    Visual::InitScreen(&Game::MainScreen, &Game::windowTitle, 
            &Game::windowSize);

    Visual::LoadImageSurface( &Game::Background, true, &Game::MainScreen );
    // Add multi threading/make each loop take 10ms to stop it from using
    // 100% of the CPU
    bool quit{false};
    SDL_Event currentEvent;
    while( !quit ){
        std::thread th1(usleep, 100000);
        while ( SDL_PollEvent( &currentEvent ) ) {
            Visual::CheckQuit( &currentEvent, &quit );
            Visual::CheckKeyDown( &currentEvent );
        }
        SDL_BlitSurface(Game::Background.imageSurface, NULL, 
                Game::MainScreen.imageSurface, NULL);
        SDL_UpdateWindowSurface(Game::MainScreen.window);
        th1.join();
    }
    Visual::CloseProgram(&Game::MainScreen.window, 
            &Game::MainScreen.imageSurface);
}
