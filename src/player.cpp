#include "Headers/Player.h"

#include <tice.h>

#include "Headers/Box.h"
#include "Headers/Common.h"
void movePlayer(int16_t x, int16_t y, Object &p, Entitytypes board[5][5], Object boxes[2]) {
    if (board[p.pos.x + x][p.pos.y + y] == box) {  //box is in front
        //check witch box is in front
        int index;
        for (uint8_t i = 0; i < 2; i++) {
            if (boxes[i].pos.x == p.pos.x + x && boxes[i].pos.y == p.pos.y + y) {  //See if box in front of PlayerObj the box at that pos is.
                index = i;
            }
        }

        if (moveBox(x, y, boxes[index], board)) {
            board[p.pos.x][p.pos.y] = empty;
            p.pos.x += x;
            p.pos.y += y;

            // clamp the PlayerObj's position, so that they don't fall off the board
            p.pos.x = (p.pos.x > BOARD_SIZE - 1) ? (BOARD_SIZE - 1) : p.pos.x;
            p.pos.y = (p.pos.y > BOARD_SIZE - 1) ? (BOARD_SIZE - 1) : p.pos.y;
            p.pos.x = (p.pos.x < 0) ? 0 : p.pos.x;
            p.pos.y = (p.pos.y < 0) ? 0 : p.pos.y;

            board[p.pos.x][p.pos.y] = player;
        }
    } else if (board[p.pos.x + x][p.pos.y + y] != wall) {
        board[p.pos.x][p.pos.y] = empty;
        p.pos.x += x;
        p.pos.y += y;

        // clamp the PlayerObj's position, so that they don't fall off the board
        p.pos.x = (p.pos.x > BOARD_SIZE - 1) ? (BOARD_SIZE - 1) : p.pos.x;
        p.pos.y = (p.pos.y > BOARD_SIZE - 1) ? (BOARD_SIZE - 1) : p.pos.y;
        p.pos.x = (p.pos.x < 0) ? 0 : p.pos.x;
        p.pos.y = (p.pos.y < 0) ? 0 : p.pos.y;

        board[p.pos.x][p.pos.y] = player;
    }
}