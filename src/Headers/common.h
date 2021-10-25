#pragma once
// Player = 1, box = 2 , wall = 3 , goal = 4

enum Entitytypes {
    empty,
    player,
    box,
    wall,
    goal
};
struct Vector2 {
    int x = 0;
    int y = 0;
};
class Object {
   public:
    Vector2 pos;
};
#define BOARD_SIZE 5
const uint32_t XSIZE = 5;
const uint32_t YSIZE = 5;
const uint32_t SCREEN_WIDTH = 320;
const uint32_t SCREEN_HEIGHT = 240;