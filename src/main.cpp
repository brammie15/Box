//#include <debug.h>
#include <graphx.h>
#include <keypadc.h>
#include <math.h>
#include <tice.h>

#include "box.h"
#include "common.h"
#include "player.h"
// we store whether the key was previously pressed down. you'll see what we do with this.
bool previousUp = false;
bool previousDown = false;
bool previousLeft = false;
bool previousRight = false;

bool checkGoals(Object goal, Object box) {
    if (goal.pos.x == box.pos.x && goal.pos.y == box.pos.y) {
        return true;
    } else {
        return false;
    }
}

bool moveBox(int16_t x, int16_t y, Object &b, uint8_t board[5][5]) {
}

// 320x240
// 40
int main(void) {
    const uint32_t XSIZE = 5;
    const uint32_t YSIZE = 5;
    const uint32_t SCREEN_WIDTH = 320;
    const uint32_t SCREEN_HEIGHT = 240;
    //dbg_sprintf(dbgout, "Initialized some things...\n");
    uint8_t board[5][5];
    kb_key_t key;
    Object player;
    Object box;
    Object goal;
    box.pos = Vector2{2, 2};
    goal.pos = Vector2{4, 4};
    player.pos = Vector2{0, 0};
    board[player.pos.x][player.pos.y] = 1;
    board[box.pos.x][box.pos.y] = 2;
    board[goal.pos.x][goal.pos.y] = 4;
    gfx_Begin();
    do {
        kb_Scan();

        // after updating the keypad, we check if the keys are pressed and if they were pressed before
        // if the key is pressed now *and* it was not pressed before, we move the player
        // this is a messy way of doing this. Allegro's tutorials somewhere have a better solution.
        if (kb_IsDown(kb_KeyUp) && !previousUp) {
            movePlayer(0, -1, player, board, box);
        }
        if (kb_IsDown(kb_KeyDown) && !previousDown) {
            movePlayer(0, 1, player, board, box);
        }
        if (kb_IsDown(kb_KeyLeft) && !previousLeft) {
            movePlayer(-1, 0, player, board, box);
        }
        if (kb_IsDown(kb_KeyRight) && !previousRight) {
            movePlayer(1, 0, player, board, box);
        }
        //checkGoals(goal, box);

        // finally, update the previousUp, previousDown, previousLeft, and previousRight variables.
        previousUp = kb_IsDown(kb_KeyUp);
        previousLeft = kb_IsDown(kb_KeyLeft);
        previousRight = kb_IsDown(kb_KeyRight);
        previousDown = kb_IsDown(kb_KeyDown);

        // Player = 1, box = 2 , wall = 3 , goal = 4
        board[box.pos.x][box.pos.y] = 2;
        gfx_SetDrawBuffer();
        // Rendering
        gfx_FillScreen(255);
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                switch (board[x][y]) {
                    case 1:
                        gfx_SetColor(7);
                        gfx_FillRectangle(x * 48 + 40, y * 48, 48, 48);
                        break;
                    case 2:
                        gfx_SetColor(129);
                        gfx_FillRectangle(x * 48 + 40, y * 48, 48, 48);
                        break;
                    case 4:
                        gfx_SetColor(231);
                        gfx_FillRectangle(x * 48 + 40, y * 48, 48, 48);
                        break;
                    default:
                        // gfx_SetColor(184);
                        //gfx_FillCircle(x * 48 + 40 + 24, y * 48 + 24, 24);
                        break;
                }
            }
        }

        //draw grid
        gfx_SetColor(gfx_black);
        for (uint32_t i = 0; i < SCREEN_HEIGHT; i += (SCREEN_HEIGHT / 5)) {
            gfx_HorizLine(40, i, SCREEN_WIDTH - 80);
        }
        for (uint32_t i = 40; i < SCREEN_WIDTH; i += (SCREEN_WIDTH - 80) / YSIZE) {  //starting at 40 for edges
            gfx_VertLine(i, 0, SCREEN_HEIGHT);
        }
        gfx_SwapDraw();

    } while (!kb_IsDown(kb_KeyClear));
    gfx_End();
    return 0;
}