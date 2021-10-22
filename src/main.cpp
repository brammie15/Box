#include <graphx.h>
#include <keypadc.h>
#include <math.h>
#include <tice.h>

struct Vector2 {
    int x;
    int y;
};
class Object {
   public:
    Vector2 pos;
};

// we store whether the key was previously pressed down. you'll see what we do with this.
bool previousUp = false;
bool previousDown = false;
bool previousLeft = false;
bool previousRight = false;

uint8_t get_single_key_pressed(void) {
    static uint8_t last_key;
    uint8_t only_key = 0;
    kb_Scan();
    for (uint8_t key = 1, group = 7; group; --group) {
        for (uint8_t mask = 1; mask; mask <<= 1, ++key) {
            if (kb_Data[group] & mask) {
                if (only_key) {
                    last_key = 0;
                    return 0;
                } else {
                    only_key = key;
                }
            }
        }
    }
    if (only_key == last_key) {
        return 0;
    }
    last_key = only_key;
    return only_key;
}

#define BOARD_SIZE 5

void movePlayer(int16_t x, int16_t y, Object &p, uint8_t board[5][5]) {
    board[p.pos.x][p.pos.y] = 0;
    p.pos.x += x;
    p.pos.y += y;

    // clamp the player's position, so that they don't fall off the board
    p.pos.x = (p.pos.x > BOARD_SIZE - 1) ? (BOARD_SIZE - 1) : p.pos.x;
    p.pos.y = (p.pos.y > BOARD_SIZE - 1) ? (BOARD_SIZE - 1) : p.pos.y;
    p.pos.x = (p.pos.x < 0) ? 0 : p.pos.x;
    p.pos.y = (p.pos.y < 0) ? 0 : p.pos.y;

    board[p.pos.x][p.pos.y] = 1;
}

// 320x240
// 40
int main(void) {
    const uint16_t XSIZE = 5;
    const uint16_t YSIZE = 5;
    const uint16_t SCREEN_WIDTH = 320;
    const uint16_t SCREEN_HEIGHT = 240;

    uint8_t board[5][5];
    kb_key_t key;
    Object player;
    player.pos = Vector2{0, 0};
    board[player.pos.x][player.pos.y] = 1;
    gfx_Begin();
    do {
        kb_Scan();

        // after updating the keypad, we check if the keys are pressed and if they were pressed before
        // if the key is pressed now *and* it was not pressed before, we move the player
        // this is a messy way of doing this. Allegro's tutorials somewhere have a better solution.
        if (kb_IsDown(kb_KeyUp) && !previousUp) {
            movePlayer(0, -1, player, board);
        }
        if (kb_IsDown(kb_KeyDown) && !previousDown) {
            movePlayer(0, 1, player, board);
        }
        if (kb_IsDown(kb_KeyLeft) && !previousLeft) {
            movePlayer(-1, 0, player, board);
        }
        if (kb_IsDown(kb_KeyRight) && !previousRight) {
            movePlayer(1, 0, player, board);
        }

        // finally, update the previousUp, previousDown, previousLeft, and previousRight variables.
        previousUp = kb_IsDown(kb_KeyUp);
        previousLeft = kb_IsDown(kb_KeyLeft);
        previousRight = kb_IsDown(kb_KeyRight);
        previousDown = kb_IsDown(kb_KeyDown);

        // Player = 1, box = 2 , wall = 3

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
                    default:
                        gfx_SetColor(184);
                        gfx_FillCircle(x * 48 + 40 + 24, y * 48 + 24, 24);
                        break;
                }
            }
        }
        //draw grid
        gfx_SetColor(gfx_black);
        for (uint16_t i = 0; i < SCREEN_HEIGHT; i += (SCREEN_HEIGHT / 5)) {
            gfx_HorizLine(40, i, SCREEN_WIDTH - 80);
        }
        for (uint16_t i = 40; i < SCREEN_WIDTH; i += (SCREEN_WIDTH - 80) / YSIZE) {  //starting at 40 for edges
            gfx_VertLine(i, 0, SCREEN_HEIGHT);
        }
        gfx_SwapDraw();

    } while (!kb_IsDown(kb_KeyClear));
    gfx_End();
    return 0;
}