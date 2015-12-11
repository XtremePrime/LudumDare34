#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <SFML/Audio.hpp>
#include "game.h"

int main(int argc, char** argv)
{
    Game game;
    game.run();

    return EXIT_SUCCESS;
}
