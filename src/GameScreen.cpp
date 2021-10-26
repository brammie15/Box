#include "Headers/GameScreen.h"

#include <debug.h>
#include <graphx.h>
#include <keypadc.h>
#include <tice.h>

#include "Headers/Box.h"
#include "Headers/Common.h"
#include "Headers/Levels.h"
#include "Headers/Player.h"
#include "Headers/Screen.h"

const uint8_t boxAmount = 2;

bool checkGoals(Object goal, Object box[boxAmount]) {
    //return (goal.pos.x == box[]pos.x && goal.pos.y == box->pos.y);
    //this fucntion causes a mem leak... don't use it
}
void loadLevel(Entitytypes level[5][5], Object &_playerObj, Object boxes[2], Object &_goalObj, Entitytypes board[5][5]) {
    for (uint8_t x = 0; x < 5; x++) {
        for (uint8_t y = 0; y < 5; y++) {
            switch (level[y][4 - x]) {  //inverted and -4 because otherwise is flipped and roated 90deg clockwise
                case empty:
                    board[x][y] = empty;
                    break;
                case player:
                    board[x][y] = player;
                    _playerObj.pos = Vector2{x, y};
                    break;
                case box:
                    board[x][y] = box;
                    if (boxes[0].pos.x == 6 && boxes[0].pos.y == 6) {
                        boxes[0].pos = Vector2{x, y};
                    } else {
                        boxes[1].pos = Vector2{x, y};
                    }
                    break;
                case wall:
                    board[x][y] = wall;
                    break;
                case goal:
                    board[x][y] = goal;
                    _goalObj.pos = Vector2{x, y};
                    break;
            }
        }
    }
}
void GameScreen::setup() {
    previousUp = false;
    previousDown = false;
    previousLeft = false;
    previousRight = false;
    loadLevel(levelDbg, playerObj, boxes, goalObj, board);
    board[playerObj.pos.x][playerObj.pos.y] = player;

    board[boxes[0].pos.x][boxes[0].pos.y] = box;
    board[boxes[1].pos.x][boxes[1].pos.y] = box;

    board[goalObj.pos.x][goalObj.pos.y] = goal;
    dbg_sprintf(dbgout,"Setup Done. \n");
    gfx_Begin();
}

void GameScreen::draw() {
    dbg_sprintf(dbgout,"DRAW INIT \n");
    kb_Scan();
    dbg_sprintf(dbgout,"Keyboard Scanned");

    // after updating the keypad, we check if the keys are pressed and if they were pressed before
    // if the key is pressed now *and* it was not pressed before, we move the PlayerObj
    if (kb_IsDown(kb_KeyUp) && !previousUp) {
        movePlayer(0, -1, playerObj, board, boxes);
    }
    if (kb_IsDown(kb_KeyDown) && !previousDown) {
        movePlayer(0, 1, playerObj, board, boxes);
    }
    if (kb_IsDown(kb_KeyLeft) && !previousLeft) {
        movePlayer(-1, 0, playerObj, board, boxes);
    }
    if (kb_IsDown(kb_KeyRight) && !previousRight) {
        movePlayer(1, 0, playerObj, board, boxes);
    }
    if (kb_IsDown(kb_KeyClear)) {
        isRunning = false;
    }
    dbg_sprintf(dbgout,"Input Checked");

//    if (checkGoals(goalObj, boxes)) {
//        //Load next level
//        currentLevel++;
//        switch (currentLevel) {
//            case 0:
//                loadLevel(level2, playerObj, boxes, goalObj, board);
//                break;
//            case 1:
//                //i guess make more levels
//                break;
//            default:
//                break;
//        }
//    }

    // finally, update the previousUp, previousDown, previousLeft, and previousRight variables.
    previousUp = kb_IsDown(kb_KeyUp);
    previousLeft = kb_IsDown(kb_KeyLeft);
    previousRight = kb_IsDown(kb_KeyRight);
    previousDown = kb_IsDown(kb_KeyDown);

    // Player = 1, box = 2 , wall = 3 , goal = 4
    gfx_SetDrawBuffer();
    // Rendering
    gfx_FillScreen(255);
     for (int x = 0; x < 5; x++) {
         for (int y = 0; y < 5; y++) {
             switch (board[x][y]) {
                 case player:
                     gfx_SetColor(7);
                     break;
                 case box:
                     gfx_SetColor(129);
                     break;
                 case wall:
                     gfx_SetColor(0);
                     break;
                 case goal:
                     gfx_SetColor(231);
                     break;
                 case Entitytypes::empty:
                     gfx_SetColor(255);
                 default:
                     break;
             }
             gfx_FillRectangle(x * 48 + 40, y * 48, 48, 48);
    }
    }

    //draw grid
    gfx_SetColor(0);
    for (uint32_t i = 0; i < SCREEN_HEIGHT; i += (SCREEN_HEIGHT / 5)) {
        gfx_HorizLine(40, i, SCREEN_WIDTH - 80);
    }
    for (uint32_t i = 40; i < SCREEN_WIDTH; i += (SCREEN_WIDTH - 80) / YSIZE) {  //starting at 40 for edges
        gfx_VertLine(i, 0, SCREEN_HEIGHT);
    }
    gfx_SwapDraw();
}
