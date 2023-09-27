#include "../include/gameDef.hpp"
#include "../include/initialize.hpp"


std::string Game::windowTitle = "Brian's Hunt";

Utils::Size Game::windowSize = {
    .height = 720,
    .width = 517
};

Utils::Image Game::MainScreen {
    .surfaceSize = Game::windowSize,
    .walkAble = { {.x=0, .y=50},
        {.x=517, .y=720} }
};

Utils::Image Game::Background = {
    .imagePath = "resources/BackgroundFullBig.png",
};

Utils::Image Game::Character {
    .imagePath = "resources/AmyGoodSize.png",
    .surfaceSize = {100, 100}
};

Utils::Contributor Game::MJ {
    .name = "MJ",
    .whatTheyDid = "Programmed the game in C++"
};

Utils::Contributor Game::Sylar {
    .name = "Sylar Lund",
    .whatTheyDid = "Made ALL the art for this project"
};

