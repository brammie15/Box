//#include <debug.h>
#include <graphx.h>
#include <keypadc.h>
#include <math.h>
#include <tice.h>

#include "Headers/Levels.h"
#include "Headers/box.h"
#include "Headers/common.h"
#include "Headers/gameScreen.h"
#include "Headers/player.h"
#include "Headers/screen.h"

// 320x240
// 40
int main(void) {
    GameScreen game;
    game.setup();
    do {
        game.draw();
    } while (!kb_IsDown(kb_KeyClear));

    return 0;
}