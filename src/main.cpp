#include <graphx.h>
#include <keypadc.h>
#include <tice.h>
struct Vector2 {
    int x;
    int y;
};
class Object {
   public:
    Vector2 pos;
};

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

void movePlayer(int8_t x, int8_t y, Object &p, uint8_t board[5][5]) {
    board[p.pos.x][p.pos.y] = 0;
    p.pos.x += x;
    p.pos.y += y;
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

        key = kb_Data[7];

        if (key & kb_Down) {
            movePlayer(0, 1, player, board);
        }
        if (key & kb_Up) {
            movePlayer(0, -1, player, board);
        }
        if (key & kb_Left) {
            movePlayer(-1, 0, player, board);
        }
        if (key & kb_Right) {
            movePlayer(1, 0, player, board);
        }

        // switch (get) {
        //     case kb_Down:
        //         movePlayer(0, 1, player, board);
        //         break;
        //     case kb_Up:
        //         movePlayer(0, -1, player, board);
        //         break;
        //     case kb_Right:
        //         movePlayer(1, 0, player, board);
        //         break;
        //     case kb_Left:
        //         movePlayer(-1, 0, player, board);
        //         break;
        //     default:
        //         break;
        // }
        // prevKey = keyUp || keyDown || keyLeft || keyRight;

        // Player = 1, box = 2 , wall = 3

        gfx_SetDrawBuffer();
        // gfx_SwapDraw();
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
        gfx_SetColor(gfx_black);
        for (uint16_t i = 0; i < SCREEN_HEIGHT; i += (SCREEN_HEIGHT / 5)) {
            gfx_HorizLine(40, i, SCREEN_WIDTH - 80);
        }
        for (uint16_t i = 40; i < SCREEN_WIDTH; i += (SCREEN_WIDTH - 80) / YSIZE) {
            gfx_VertLine(i, 0, SCREEN_HEIGHT);
        }
        gfx_SwapDraw();

    } while (!kb_IsDown(kb_KeyClear));
    gfx_End();
    return 0;
}