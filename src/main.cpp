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

    Visual::LoadImageSurface( &Game::Background, true,
            &Game::MainScreen );
    Visual::LoadImageSurface( &Game::Character );

    // Add multi threading/make each loop take 10ms to stop it from using
    // 100% of the CPU
    bool quit{false};
    SDL_Event currentEvent;
    while( !quit ){
        std::thread SleepThread(usleep, 1000000);
        while ( SDL_PollEvent( &currentEvent ) ) {
            Visual::CheckQuit( &currentEvent, &quit );
            Visual::CheckKeyDown( &currentEvent );
        }
        SDL_BlitSurface(Game::Background.imageSurface, NULL, 
                Game::MainScreen.imageSurface, NULL);
        Game::Player.drawSprite( &Game::MainScreen );
        SDL_UpdateWindowSurface(Game::MainScreen.window);
        std::cout << "Loop" << std::endl; 
            
        SleepThread.join();
    }
    Visual::CloseProgram(); 
}
