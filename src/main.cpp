//#include <debug.h>
#include <graphx.h>
#include <keypadc.h>
#include <math.h>
#include <tice.h>

#include "Headers/Box.h"
#include "Headers/Common.h"
#include "Headers/GameScreen.h"
#include "Headers/Levels.h"
#include "Headers/MainScreen.h"
#include "Headers/Player.h"

// 320x240
// 40
int main(void) {
    GameScreen game;
    MainScreen start;

    start.setup();
    while (!start.shouldStart) {
        start.draw();
    }
    if (start.shouldStart) {
        game.setup();
        do {
            game.draw();
        } while (!kb_IsDown(kb_KeyClear));
    }

    return 0;
}