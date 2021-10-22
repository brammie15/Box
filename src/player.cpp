#include "player.h"

#include <tice.h>

#include "box.h"
#include "common.h"
void movePlayer(int16_t x, int16_t y, Object &p, uint8_t board[5][5], Object &b) {
    if (board[p.pos.x + x][p.pos.y + y] == 2) {  //box is in front
        if (moveBox(x, y, b, board)) {
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
    } else {
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
}