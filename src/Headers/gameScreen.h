#pragma once
#include <keypadc.h>
#include <tice.h>

#include "Common.h"
#include "Screen.h"
class GameScreen : public Screen {
   public:
    uint8_t board[5][5];
    kb_key_t key;
    Object player;
    Object box;
    Object goal;
    bool previousUp;
    bool previousDown;
    bool previousLeft;
    bool previousRight;
    //bool checkGoals(Object goal, Object box);
};