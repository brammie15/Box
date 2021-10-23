#pragma once
struct Vector2 {
    int x;
    int y;
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