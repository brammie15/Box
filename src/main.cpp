//#include <debug.h>
#include <tice.h>

#include "Headers/Common.h"
#include "Headers/GameScreen.h"
#include "Headers/MainScreen.h"
#include "Headers/Screen.h"

// 320x240
int main(void) {
    GameScreen game;
    MainScreen start;

    start.setup();
    do {
        start.draw();
    } while (!start.shouldStart);

    game.setup();
     do {
         game.draw();
     } while (game.isRunning);

    return 0;
}