#include "box.h"

#include "common.h"
#include "tice.h"
bool validPos(int8_t x, int8_t y) {
    if (x > BOARD_SIZE - 1 || x < 0 || y > BOARD_SIZE - 1 || y < 0) {
        return false;
    } else {
        //dbg_sprintf(dbgout, "ValidPos: x: %d, y: %d \n", x, y);
        return true;
    }
}

bool moveBox(int16_t x, int16_t y, Object &b, uint8_t board[5][5]) {
    //dbg_sprintf(dbgout, "MoveBox x: %d, y: %d \n", x, y);
    if (validPos(b.pos.x + x, b.pos.y + y)) {
        board[b.pos.x][b.pos.y] = 0;
        b.pos.x += x;
        b.pos.y += y;
        board[b.pos.x][b.pos.y] = 2;
        //dbg_sprintf(dbgout, "New position: x: %d y: %d \n", b.pos.x, b.pos.y);
        return true;
    } else {
        return false;
    }
}